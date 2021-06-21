#include "Camera.h"

#include "Transform.h"
#include "Layer.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "GameObject.h"

#include "InstancingBuffer.h"
#include "MeshRender.h"
#include "Animator.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Device.h"

CCamera::CCamera()
	: m_bPerspective(false)
	, m_fFOV(XM_PI / 4.f)
	, m_fWidth(WINSIZE_X)
	, m_fHeight(WINSIZE_Y)
	, m_fScale(1.f)
	, m_fNear(1.f)
	, m_fFar(1000.f)
	, m_iLayerCheck(0)
{
}

CCamera::~CCamera()
{
	Safe_Delete_Map(m_mapInstGroup);
}

int CCamera::update()
{
	return RET_SUCCESS;
}

int CCamera::finalupdate()
{
	// View 변환행렬 구하기
	m_matView = XMMatrixIdentity();

	//Vec3 vPos = Transform()->GetLocalPos();
	Vec3 vPos = Transform()->GetWorldPos();
	m_matView._41 = -vPos.x; m_matView._42 = -vPos.y; m_matView._43 = -vPos.z;

	// 투영행렬 구하기
	if (m_bPerspective)
	{
		m_matProj = XMMatrixPerspectiveFovLH(m_fFOV, (float)WINSIZE_X / (float)WINSIZE_Y
			, m_fNear, m_fFar);
	}
	else
	{
		m_matProj = XMMatrixOrthographicLH(m_fWidth * m_fScale, m_fHeight * m_fScale, m_fNear, m_fFar);
		//m_matProj = XMMatrixOrthographicOffCenterLH(-m_fWidth * m_fScale / 2.f, m_fWidth * m_fScale / 2.f, -m_fHeight * m_fScale / 2.f, m_fHeight * m_fScale / 2.f, m_fNear, m_fFar);
	}

	UpdateInstancing();

	return RET_SUCCESS;
}

void CCamera::UpdateInstancing()
{
	for (auto& pair : m_mapInstGroup)
	{
		pair.second->clear();
	}

	uInstID uID = {};

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CLayer*>& vecLayer = pCurScene->GetVecLayer();

	for (UINT i = 0; i < vecLayer.size(); ++i)
	{
		if (NULL == vecLayer[i])
			continue;

		list<CGameObject*>& listObj = vecLayer[i]->GetObjList();
		for (auto& pObj : listObj)
		{
			uID.IllD = pObj->GetInstID();
			if (0 == uID.IllD)
				continue;

			// 카메라 절두체 컬링

			map<ULONG64, vector<CGameObject*>*>::iterator iter = m_mapInstGroup.find(uID.IllD);
			if (iter == m_mapInstGroup.end())
			{
				vector<CGameObject*>* pVec = new vector<CGameObject*>;
				pVec->push_back(pObj);
				m_mapInstGroup.insert(make_pair(uID.IllD, pVec));
			}
			else
				iter->second->push_back(pObj);
		}
	}
}

void CCamera::Reset()
{
	m_mapInstGroup.clear();
}

void CCamera::render()
{
	m_vecSingleObj.clear();

	tInstancingData tInstData = {};

	for (auto& pair : m_mapInstGroup)
	{
		CMesh* pMesh = pair.second->front()->MeshRender()->GetMesh();
		CMaterial* pMtrl = pair.second->front()->MeshRender()->GetSharedMaterial();

		// 그룹 오브젝트가 없거나, 쉐이더가 없는 경우
		if (pair.second->empty() || NULL == pMtrl->GetShader())
			continue;

		CInstancingBuffer::GetInst()->Clear();

		for (UINT i = 0; i < pair.second->size(); ++i)
		{
			if (pair.second->at(i)->Animator())
			{
				m_vecSingleObj.push_back(pair.second->at(i));
				continue;
			}

			tInstData.matWorld = pair.second->at(i)->Transform()->GetWorldMat();
			tInstData.matWV = tInstData.matWorld * m_matView;
			tInstData.matWVP = tInstData.matWV * m_matProj;

			CInstancingBuffer::GetInst()->AddInstancingData(tInstData);
		}

		CInstancingBuffer::GetInst()->SetData();

		pMtrl->UpdateDataInstancing();
		pMesh->SetLayout(pMtrl->GetShader()->GetVSInstBlob());
		pMesh->UpdateDataInstancing();

		CDevice::GetInst()->SetRasterizer(RASTERIZE_TYPE::RT_NONE);
		CAnimator::Disable();
		pMesh->renderInstancing();
	}

	// 개별 랜더링
	for (auto& pObj : m_vecSingleObj)
	{
		pObj->render();
	}
}

void CCamera::render(CLayer * _pLayer, list<CGameObject*>& _listObj)
{
	int iIdx = _pLayer->GetLayerIdx();

	if (m_iLayerCheck & (1 << iIdx))
	{
		_pLayer->render(_listObj);
	}
}

void CCamera::render(CLayer * _pLayer)
{
	int iIdx = _pLayer->GetLayerIdx();

	if (m_iLayerCheck & (1 << iIdx))
	{
		_pLayer->render();
	}
}


void CCamera::SetPos(Vec3& _vec3)
{
	Transform()->SetLocalPos(_vec3);
}

void CCamera::LayerRenderCheck(const wstring& _strLayerName)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->FindLayer(_strLayerName);

	if (NULL == pLayer)
		assert(NULL);

	int iIdx = pLayer->GetLayerIdx();

	UINT iCompare = 1 << iIdx;

	if (m_iLayerCheck & iCompare)
	{
		m_iLayerCheck &= ~iCompare;
	}
	else
	{
		m_iLayerCheck |= iCompare;
	}
}

void CCamera::Save(FILE * _pFile)
{
	UINT iType = (UINT)COMPONENT_TYPE::CAMERA;
	fwrite(&iType, sizeof(UINT), 1, _pFile);

	fwrite(&m_bPerspective, 1, 1, _pFile);
	fwrite(&m_fFOV, sizeof(float), 1, _pFile);
	fwrite(&m_fWidth, sizeof(float), 1, _pFile);
	fwrite(&m_fHeight, sizeof(float), 1, _pFile);
	fwrite(&m_fScale, sizeof(float), 1, _pFile);
	fwrite(&m_fNear, sizeof(float), 1, _pFile);
	fwrite(&m_fFar, sizeof(float), 1, _pFile);
	fwrite(&m_iLayerCheck, sizeof(UINT), 1, _pFile);
}

void CCamera::Load(FILE * _pFile)
{
	fread(&m_bPerspective, 1, 1, _pFile);
	fread(&m_fFOV, sizeof(float), 1, _pFile);
	fread(&m_fWidth, sizeof(float), 1, _pFile);
	fread(&m_fHeight, sizeof(float), 1, _pFile);
	fread(&m_fScale, sizeof(float), 1, _pFile);
	fread(&m_fNear, sizeof(float), 1, _pFile);
	fread(&m_fFar, sizeof(float), 1, _pFile);
	fread(&m_iLayerCheck, sizeof(UINT), 1, _pFile);
}