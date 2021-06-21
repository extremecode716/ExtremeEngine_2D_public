#include "ResMgr.h"

#include "ShaderMgr.h"

#include "Prefab.h"
#include "Mesh.h"
#include "Material.h"
#include "GameObject.h"


CResMgr::CResMgr() 
	: m_bChange(false)
{
}

CResMgr::~CResMgr()
{
	////ReleaseSound();
	//Safe_Delete_Map_Res(m_mapMesh);
	//Safe_Delete_Map_Res(m_mapTex);
	////Safe_Delete_Map_Res(m_mapPrefab);
	//Safe_Delete_Map_Res(m_mapMat);
	//Safe_Delete_Vec_Res(m_vecCloneRes);
}

void CResMgr::ReleasePrefab()
{
	Safe_Delete_Map_Res(m_mapPrefab);
}

void CResMgr::Release()
{
	//ReleaseSound();
	Safe_Delete_Map_Res(m_mapMesh);
	Safe_Delete_Map_Res(m_mapTex);
	//Safe_Delete_Map_Res(m_mapPrefab);
	Safe_Delete_Map_Res(m_mapMat);
	Safe_Delete_Vec_Res(m_vecCloneRes);

	ReleaseSound();
}

void CResMgr::init()
{
	CreateDefaultMesh();
	CreateDefaultMaterial();
	InitFMOD();
}

void CResMgr::ReleaseSound()
{
	Safe_Delete_Map_Res(m_mapSound);
	CSound::g_pSystem->release();
	CSound::g_pSystem->close();
}


// 자식 prefab 추가 할것 수정 요망
int CResMgr::AddPrefab(const wstring & _strKey, CGameObject * _pPrefabObj)
{
	CPrefab* pPrefab = FindPrefab(_strKey);
	
	if (NULL != pPrefab)
	{
		SAFE_DELETE(_pPrefabObj);  // ★ 중복 검사 후 삭제
		return RET_FAILED;
	}
	_pPrefabObj->SetParentObj(NULL);
	pPrefab = new CPrefab(_pPrefabObj);
	pPrefab->SetKey(_strKey);
	m_mapPrefab.insert(make_pair(_strKey, pPrefab));

	/////////////수정
	m_bChange = true;

	return 0;
}

int CResMgr::AddChildPrefab(CGameObject * _pChildObj, CPrefab * _pParentPrefab)
{

	return 0;
}



int CResMgr::AddMtrl(const wstring & _strKey, CMaterial * _pMtrl)
{
	CMaterial* pMtrl = FindMaterial(_strKey);

	if (NULL != pMtrl)
		return RET_FAILED;

	_pMtrl->SetKey(_strKey);
	m_mapMat.insert(make_pair(_strKey, _pMtrl));
	m_bChange = true;

	return 0;
}


CPrefab * CResMgr::SubPrefab(const wstring & _strKey)
{
	map<wstring, CResPtr<CPrefab>>::iterator iter = m_mapPrefab.find(_strKey);

	if (iter == m_mapPrefab.end())
		return NULL;

	CPrefab* pPrefab = iter->second;
	iter = m_mapPrefab.erase(iter);
	return pPrefab;
}

CMaterial * CResMgr::FindMaterial(const wstring & _strKey)
{
	map<wstring, CResPtr<CMaterial>>::iterator iter = m_mapMat.find(_strKey);

	if (iter == m_mapMat.end())
		return NULL;

	return iter->second;
}

int CResMgr::AddMesh(const wstring& _strKey, CMesh * _pMesh)
{
	CMesh* pMesh = FindMesh(_strKey);

	if (NULL != pMesh)
	{
		return RET_FAILED;
	}
	_pMesh->SetKey(_strKey);
	m_mapMesh.insert(make_pair(_strKey, _pMesh));
	m_bChange = true;

	return RET_SUCCESS;
}

CMesh * CResMgr::FindMesh(const wstring & _strKey)
{
	map<wstring, CResPtr<CMesh>>::iterator iter = m_mapMesh.find(_strKey);

	if (iter == m_mapMesh.end())
		return NULL;

	return iter->second;
}

CTexture * CResMgr::FindTexture(const wstring & _strKey)
{
	map<wstring, CResPtr<CTexture>>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
		return NULL;

	return iter->second;
}

CPrefab * CResMgr::FindPrefab(const wstring & _strKey)
{
	map<wstring, CResPtr<CPrefab>>::iterator iter = m_mapPrefab.find(_strKey);

	if (iter == m_mapPrefab.end())
		return NULL;

	return iter->second;
}

CSound * CResMgr::FindSound(const wstring & _strKey)
{
	map<wstring, CResPtr<CSound>>::iterator iter = m_mapSound.find(_strKey);

	if (iter == m_mapSound.end())
		return NULL;

	return iter->second;
}

void CResMgr::CreateDefaultMesh()
{
	//=====================
	// Create Rect Mesh
	//=====================
	vector<VTX> vecVtx; VTX v;
	vector<WORD> vecIdx;

	v.vPos = Vec3(-0.5f, -0.5f, 0.f);
	v.vUV = Vec2(0.f, 1.f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(-0.5f, 0.5f, 0.f);
	v.vUV = Vec2(0.f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, 0.5f, 0.f);
	v.vUV = Vec2(1.f, 0.f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, -0.5f, 0.f);
	v.vUV = Vec2(1.f, 1.f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	vecVtx.push_back(v);

	vecIdx.push_back(0); vecIdx.push_back(1); vecIdx.push_back(3);
	vecIdx.push_back(1); vecIdx.push_back(2); vecIdx.push_back(3);

	CResPtr<CMesh> pMesh = CMesh::Create(vecVtx.size(), sizeof(VTX), D3D11_USAGE_DEFAULT, &vecVtx[0]
		, vecIdx.size(), INDEX16::size(), D3D11_USAGE_DEFAULT, INDEX16::format(), &vecIdx[0]);

	pMesh->AddLayoutDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0);
	pMesh->AddLayoutDesc("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0);
	pMesh->AddLayoutDesc("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);

	/*인스턴싱 데이터는 슬롯이 다르다*/
	pMesh->AddLayoutDesc("WORLD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WORLD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WORLD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WORLD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);

	pMesh->AddLayoutDesc("WV", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WV", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WV", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WV", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);

	pMesh->AddLayoutDesc("WVP", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WVP", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WVP", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WVP", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);

	AddMesh(L"RectMesh", pMesh);

	//==========================
	// Create Collider Rect Mesh
	//==========================
	vecIdx.clear();

	vecIdx.push_back(0); vecIdx.push_back(1); vecIdx.push_back(2);
	vecIdx.push_back(3); vecIdx.push_back(0);

	pMesh = CMesh::Create(vecVtx.size(), sizeof(VTX), D3D11_USAGE_DEFAULT
		, &vecVtx[0], vecIdx.size(), INDEX16::size()
		, D3D11_USAGE_DEFAULT, INDEX16::format(), &vecIdx[0]
		, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	pMesh->AddLayoutDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0);
	pMesh->AddLayoutDesc("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0);
	pMesh->AddLayoutDesc("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);

	/*인스턴싱 데이터는 슬롯이 다르다*/
	pMesh->AddLayoutDesc("WORLD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WORLD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WORLD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WORLD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);

	pMesh->AddLayoutDesc("WV", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WV", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WV", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WV", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);

	pMesh->AddLayoutDesc("WVP", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WVP", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WVP", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	pMesh->AddLayoutDesc("WVP", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);

	AddMesh(L"ColliderRectMesh", pMesh);
}

void CResMgr::CreateDefaultMaterial()
{
	CMaterial* pMtrl = new CMaterial;

	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"ColorShader"));
	AddMtrl(L"Default", pMtrl);

	//===================
	// Collider Material
	//===================
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"ColliderShader"));
	AddMtrl(L"ColliderMaterial", pMtrl);


}

void CResMgr::InitFMOD()
{
	FMOD::System_Create(&CSound::g_pSystem);

	if (NULL == CSound::g_pSystem)
		assert(NULL);

	CSound::g_pSystem->init(64, FMOD_DEFAULT, NULL);
}

#include "DebugMgr.h"
void CResMgr::SaveResource(FILE * _pFile)
{
#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"===Resource Save Start===");
#endif
	// Mesh
	UINT iCount = m_mapMesh.size();
	fwrite(&iCount, sizeof(UINT), 1, _pFile);

#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"-Mesh Count-");
	CDebugMgr::GetInst()->Log(iCount);
#endif

	for (auto& pair : m_mapMesh)
	{
		// ref count 저장
		int iRefCount = pair.second->GetRefCnt();
		fwrite(&iRefCount, sizeof(int), 1, _pFile);
#ifdef SAVELOAD_DEBUG
		CDebugMgr::GetInst()->Log(L"-Mesh Map Ref Count-");
		CDebugMgr::GetInst()->Log(iRefCount);
#endif

		if (1 < iRefCount)
			pair.second->Save(_pFile);
	}

	// Texture
	iCount = m_mapTex.size();
	fwrite(&iCount, sizeof(UINT), 1, _pFile);
#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"-Texture Count-");
	CDebugMgr::GetInst()->Log(iCount);
#endif

	for (auto& pair : m_mapTex)
	{
		// ref count 저장
		int iRefCount = pair.second->GetRefCnt();
		fwrite(&iRefCount, sizeof(int), 1, _pFile);
#ifdef SAVELOAD_DEBUG
		CDebugMgr::GetInst()->Log(L"-Texture Map Ref Count-");
		CDebugMgr::GetInst()->Log(iRefCount);
#endif
		if (1 < iRefCount)
			pair.second->Save(_pFile);
	}

	// Material
	iCount = m_mapMat.size();
	fwrite(&iCount, sizeof(UINT), 1, _pFile);
#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"-Material Count-");
	CDebugMgr::GetInst()->Log(iCount);
#endif
	for (auto& pair : m_mapMat)
	{
		// ref count 저장
		int iRefCount = pair.second->GetRefCnt();
		fwrite(&iRefCount, sizeof(int), 1, _pFile);
#ifdef SAVELOAD_DEBUG
		CDebugMgr::GetInst()->Log(L"-Material Map Ref Count-");
		CDebugMgr::GetInst()->Log(iRefCount);
#endif
		if (1 < iRefCount)
			pair.second->Save(_pFile);
	}

	//// Sound
	//iCount = m_mapSound.size();
	//fwrite(&iCount, sizeof(UINT), 1, _pFile);

	//for (auto& pair : m_mapSound)
	//{
	//	// ref count 저장
	//	int iRefCount = pair.second->GetRefCnt();
	//	fwrite(&iRefCount, sizeof(int), 1, _pFile);

	//	if (1 < iRefCount)
	//	{
	//		pair.second->Save(_pFile);
	//	}
	//}

#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"===Resource Save End===");
#endif
}

void CResMgr::LoadResource(FILE * _pFile)
{
	wstring strKey;
	wstring strPath;

	// Mesh
	UINT iCount = 0;
	fread(&iCount, sizeof(UINT), 1, _pFile);
	for (UINT i = 0; i < iCount; ++i)
	{
		int iRefCount = 0;
		fread(&iRefCount, sizeof(int), 1, _pFile);

		if (1 < iRefCount)
		{
			strKey = LoadWString(_pFile);
			strPath = LoadWString(_pFile);
			Load<CMesh>(strKey, strPath);
		}
	}

	// Texture
	iCount = 0;
	fread(&iCount, sizeof(UINT), 1, _pFile);
	for (UINT i = 0; i < iCount; ++i)
	{
		int iRefCount = 0;
		fread(&iRefCount, sizeof(int), 1, _pFile);

		if (1 < iRefCount)
		{
			strKey = LoadWString(_pFile);
			strPath = LoadWString(_pFile);
			Load<CTexture>(strKey, strPath);
		}
	}

	// Material
	iCount = 0;
	fread(&iCount, sizeof(UINT), 1, _pFile);
	for (UINT i = 0; i < iCount; ++i)
	{
		int iRefCount = 0;
		fread(&iRefCount, sizeof(int), 1, _pFile);

		if (1 < iRefCount)
		{
			strKey = LoadWString(_pFile);
			strPath = LoadWString(_pFile);

			CMaterial* pMtrl = FindMaterial(strKey);
			if (NULL == pMtrl)
			{
				pMtrl = new CMaterial;
				AddMtrl(strKey, pMtrl);
			}

			pMtrl->LoadShaderParam(_pFile);
		}
	}

	//// Sound
	//iCount = 0;
	//fread(&iCount, sizeof(UINT), 1, _pFile);

	//for (UINT i = 0; i < iCount; ++i)
	//{
	//	int iRefCount = 0;
	//	fread(&iRefCount, sizeof(int), 1, _pFile);

	//	if (1 < iRefCount)
	//	{
	//		strKey = LoadWString(_pFile);
	//		strPath = LoadWString(_pFile);
	//		Load<CSound>(strKey, strPath);
	//	}
	//}
}
