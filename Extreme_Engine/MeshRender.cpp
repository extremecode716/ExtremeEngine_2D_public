#include "MeshRender.h"

#include "Mesh.h"
#include "Material.h"

#include "GameObject.h"
#include "Transform.h"
#include "Animator.h"

#include "Device.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Camera.h"

#include "Shader.h"
#include "console.h"


CMeshRender::CMeshRender()
	: m_eRT(RASTERIZE_TYPE::RT_NONE)
	, m_pMesh(NULL)
	, m_pMtrl(NULL)
	, m_bEnable(true)
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::render()
{
	if (m_pMtrl == NULL || m_pMesh == NULL || !m_pMtrl->GetShader() || false == m_bEnable)
		return;
	
	// Transform 정보 update
	Transform()->UpdateData();

	m_pMtrl->UpdateData();

	m_pMesh->SetLayout(m_pMtrl->GetShader()->GetVSBlob());
	m_pMesh->UpdateData();

	CDevice::GetInst()->SetRasterizer(m_eRT);

	if (Animator())
	{
		Animator()->UpdateData();
	}
	else
	{
		CAnimator::Disable();
	}

	m_pMesh->render();


//#ifdef  _DEBUG

	if (NULL != Collider())
		Collider()->render();

//#endif //  _DEBUG

}

CMaterial * CMeshRender::GetMaterial()
{
	if (NULL == m_pMtrl)
		return NULL;

	m_pMtrl = m_pMtrl->Clone();

	//CResMgr::GetInst()->AddCloneRes(m_pMtrl);

	return m_pMtrl;
}

ULONG64 CMeshRender::GetInstID()
{
	if (m_pMesh == NULL || m_pMtrl == NULL)
		return 0;

	uInstID id;
	id.iMesh = m_pMesh->GetResID();
	id.iMtrl = m_pMtrl->GetResID();

	return id.IllD;
}

void CMeshRender::Save(FILE * _pFile)
{
	UINT iType = (UINT)COMPONENT_TYPE::MESHRENDER;
	fwrite(&iType, sizeof(UINT), 1, _pFile);

	// Mesh 정보
	// Mesh 의 키값
	// Mesh 의 상대경로 저장
	SaveResourceKey(m_pMesh.GetTarget(), _pFile);

	// Material 정보 저장
	SaveResourceKey(m_pMtrl.GetTarget(), _pFile);

	// RS Type
	fwrite(&m_eRT, sizeof(UINT), 1, _pFile);
}

void CMeshRender::Load(FILE * _pFile)
{
	wstring strKey;

	strKey = LoadResourceKey(_pFile);
	m_pMesh = (CMesh*)CResMgr::GetInst()->Load<CMesh>(strKey);

	strKey = LoadResourceKey(_pFile);
	m_pMtrl = CResMgr::GetInst()->FindMaterial(strKey);

	fread(&m_eRT, sizeof(UINT), 1, _pFile);
}
