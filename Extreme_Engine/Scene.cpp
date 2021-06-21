#include "Scene.h"

#include "Layer.h"
#include "GameObject.h"
#include "Camera.h"
#include "Transform.h"

CScene::CScene()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_setLayerIdx.insert(i);
	}
	const string const asd[] = { {"안녕","반가워"} };

	m_vecLayer.resize(MAX_LAYER);
}

CScene::~CScene()
{
	Safe_Delete_Vec(m_vecLayer);
}

void CScene::awake()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_vecLayer[i])
			m_vecLayer[i]->awake();
	}
}

void CScene::start()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_vecLayer[i])
			m_vecLayer[i]->start();
	}
}

int CScene::update()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_vecLayer[i])
			m_vecLayer[i]->update();
	}
	return RET_SUCCESS;
}

int CScene::lateupdate()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_vecLayer[i])
			m_vecLayer[i]->lateupdate();
	}
	return RET_SUCCESS;
}

int CScene::finalupdate()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_vecLayer[i])
			m_vecLayer[i]->finalupdate();
	}
	return RET_SUCCESS;
}

void CScene::render()
{
	// Camera Layer 를 얻어온다.
	CLayer* pCamLayer = FindLayer(L"Camera");

	//CCamera* pCamCom = pCamLayer->FindWithTag(L"MainCamera")->Camera();
	//g_Transform.matProj = XMMatrixTranspose(pCamCom->GetProjMat());
	//g_Transform.matView = XMMatrixTranspose(pCamCom->GetViewMat());

	//for (int i = 0; i < MAX_LAYER; ++i)
	//{
	//	if (NULL != m_vecLayer[i])
	//	{
	//		pCamCom->render(m_vecLayer[i]);
	//	}

	//}
	list<CGameObject*>& listObj = pCamLayer->GetObjList();
	list<CGameObject*>::iterator iter = listObj.begin();

	for (; iter != listObj.end(); ++iter)
	{
		CCamera* pCamCom = (*iter)->Camera();
		if (NULL == pCamCom) return;
		g_Transform.matProj = XMMatrixTranspose(pCamCom->GetProjMat());
		g_Transform.matView = XMMatrixTranspose(pCamCom->GetViewMat());

		
		list<CGameObject*> pListObject;
		for (int i = 0; i < MAX_LAYER; ++i)
		{
			/*if (NULL != m_vecLayer[i])
			{
				pCamCom->render(m_vecLayer[i]);
			}*/
			if (NULL != m_vecLayer[i])
			{
				pCamCom->render(m_vecLayer[i], pListObject);
			}
		}
		// 임시 작업
		pListObject.sort([](CGameObject* _pLeft, CGameObject* _pRight)
		{
			return _pLeft->Transform()->GetWorldPos().z > _pRight->Transform()->GetWorldPos().z;
		}
		);

		list<CGameObject*>::iterator iter = pListObject.begin();
		for (; iter != pListObject.end(); ++iter)
		{
			(*iter)->render();
		}

		//

	}
}

void CScene::render(CGameObject * _pCameObj)
{
	CCamera* pCamCom = _pCameObj->Camera();
	if (NULL == pCamCom) return;
	g_Transform.matProj = XMMatrixTranspose(pCamCom->GetProjMat());
	g_Transform.matView = XMMatrixTranspose(pCamCom->GetViewMat());

	for (int i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_vecLayer[i])
		{
			pCamCom->render(m_vecLayer[i]);
		}
	}
}

bool CScene::Save(const wstring & _strPath)
{
	return false;
}

bool CScene::Load(const wstring & _strPath)
{
	return false;
}

int CScene::AddLayer(const wstring & _strLayerName)
{
	CLayer* pLayer = FindLayer(_strLayerName);

	if (NULL != pLayer)
		return RET_FAILED;

	pLayer = new CLayer;
	UINT iLayerIdx = GetLayerIdx();

	pLayer->SetLayerIdx(iLayerIdx);
	pLayer->SetLayerName(_strLayerName);

	m_mapLayer.insert(make_pair(_strLayerName, pLayer));
	m_vecLayer[iLayerIdx] = pLayer;

	return RET_SUCCESS;
}

int CScene::AddLayer(CLayer * _pLayer)
{
	if (FindLayer(_pLayer->GetLayerName()))
		assert(NULL);

	UINT iLayerIdx = _pLayer->GetLayerIdx();
	if (NULL != m_vecLayer[iLayerIdx])
		return RET_FAILED;

	set<UINT>::iterator iter = m_setLayerIdx.find(iLayerIdx);
	if (m_setLayerIdx.end() != iter)
		m_setLayerIdx.erase(iter);

	m_mapLayer.insert(make_pair(_pLayer->GetLayerName(), _pLayer));
	m_vecLayer[iLayerIdx] = _pLayer;

	return 0;
}

CLayer * CScene::FindLayer(const wstring & _strLayerName)
{
	map<wstring, CLayer*>::iterator iter = m_mapLayer.find(_strLayerName);
	if (iter == m_mapLayer.end())
		return NULL;

	return iter->second;
}

CGameObject * CScene::FindObject(Vec2& _vWindowPos, Vec2& _vResolution)
{
	Vec2 vWorldPos = Get2DWorldPosFromWindowPos(_vWindowPos, _vResolution);

	for (UINT i = 0; i < m_vecLayer.size(); ++i)
	{
		if (NULL == m_vecLayer[i])
			continue;

		CGameObject* pTarget = m_vecLayer[i]->FindObject(vWorldPos);
		if (NULL != pTarget)
			return pTarget;
	}

	return NULL;
}

int CScene::ChangeLayer(const wstring & _strLayerName, CGameObject*	_pObj)
{
	if (NULL == _pObj) return RET_FAILED;
	CLayer* pLayer = FindLayer(_strLayerName);
	if (NULL == pLayer) return RET_FAILED;

	pLayer->AddGameObject(_pObj);

	return RET_SUCCESS;
}


void CScene::GetAllParentObjects(list<CGameObject*>& _listObj)
{
	UINT vecSize = m_vecLayer.size();
	for (UINT i = 0; i < vecSize; ++i)
	{
		if (NULL == m_vecLayer[i])
			continue;

		list<CGameObject*>& listParentObj = m_vecLayer[i]->GetParentObjList();
		_listObj.insert(_listObj.end(), listParentObj.begin(), listParentObj.end());
	}
}

void CScene::DeleteLayer(const wstring & _strKey)
{
	map<wstring, CLayer*>::iterator iter = m_mapLayer.find(_strKey);
	if (iter == m_mapLayer.end())
		return;

	if (false == iter->second->IsEmpty())
	{
		MessageBox(NULL, L"레이어에 게임오브젝트가 들어있습니다!", L"레이어 경고", MB_OK);
		return;
	}
	
	m_setLayerIdx.insert(iter->second->GetLayerIdx());
	m_vecLayer[iter->second->GetLayerIdx()] = NULL;
	SAFE_DELETE(iter->second);
	m_mapLayer.erase(iter);
}

void CScene::EraseParentObjToLayer(const wstring& _strLayerName, CGameObject* _pParentObj)
{
	map<wstring, CLayer*>::iterator iter = m_mapLayer.find(_strLayerName);
	if (iter == m_mapLayer.end())
		return;

	CLayer* pLayer = iter->second;
	pLayer->EraseParentThisObj(_pParentObj);
}

void CScene::GetLayers(vector<tLayerInfo>& _vecOutLayer)
{
	map<wstring, CLayer*>::iterator iter = m_mapLayer.begin();

	for (; iter != m_mapLayer.end(); ++iter)
	{
		_vecOutLayer.push_back(tLayerInfo{ iter->first, iter->second });
	}
}

UINT CScene::GetLayerIdx()
{
	if (m_setLayerIdx.empty())
		assert(NULL);

	UINT iLayerIdx = *(m_setLayerIdx.begin());
	m_setLayerIdx.erase(m_setLayerIdx.begin());
	return iLayerIdx;
}

Vec2 CScene::Get2DWorldPosFromWindowPos(Vec2& _vWindowPos, Vec2& _vResolution)
{
	Vec2 vRatio;
	vRatio.x = WINSIZE_X / _vResolution.x;
	vRatio.y = WINSIZE_Y / _vResolution.y;

	Vec2 vWindowPos = Vec2(_vWindowPos.x * vRatio.x, _vWindowPos.y * vRatio.y);

	Vec2 vWorldPos;
	vWorldPos.x = vWindowPos.x - (WINSIZE_X / 2.f);
	vWorldPos.y = (WINSIZE_Y / 2.f) - vWindowPos.y;

	CLayer* pCamLayer = FindLayer(L"Camera");
	CGameObject* pCamObj = pCamLayer->FindObjectByTag(L"MainCamera");
	if (NULL == pCamObj) return Vec2();

	float fScale = pCamObj->Camera()->GetScale();

	vWorldPos = Vec2(vWorldPos.x * fScale + pCamObj->Transform()->GetWorldPos().x
		, vWorldPos.y * fScale + pCamObj->Transform()->GetWorldPos().y);

	return vWorldPos;
}
