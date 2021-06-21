#pragma once

#include "PathMgr.h"
#include "global.h"
#include "resptr.h"
#include "Texture.h"
#include "Sound.h"

#include "Mesh.h"
#include "Prefab.h"

class CMesh;
class CPrefab;
class CMeshInfo;
class CGameObject;
class CMaterial;
class CSound;

class CResMgr
{
	SINGLE(CResMgr);
	
private:
	map<wstring, CResPtr<CMesh>>		m_mapMesh;
	map<wstring, CResPtr<CTexture>>		m_mapTex;
	map<wstring, CResPtr<CMaterial>>	m_mapMat;
	map<wstring, CResPtr<CPrefab>>		m_mapPrefab;
	map<wstring, CResPtr<CSound>>		m_mapSound;

	vector<CResPtr<CRes>>			    m_vecCloneRes;

	bool								m_bChange;

public:
	void init();
	void ReleaseSound();
	void ReleasePrefab();
	void Release();

public:
	int AddMesh(const wstring& _strKey, CMesh* _pMesh);
	int AddPrefab(const wstring& _strKey, CGameObject* _pPrefab);
	int AddChildPrefab(CGameObject* _pChildObj, CPrefab* _pParentPrefab);
	int AddMtrl(const wstring& _strKey, CMaterial* _pMtrl);
	void AddCloneRes(CRes* _pRes) { m_vecCloneRes.push_back(_pRes); }

	CPrefab* SubPrefab(const wstring& _strKey);

	map<wstring, CResPtr<CMesh>>& GetMeshMap()       { return m_mapMesh; }
	map<wstring, CResPtr<CTexture>>& GetTextureMap() { return m_mapTex; }
	map<wstring, CResPtr<CPrefab>>& GetPrefabMap()   { return m_mapPrefab; }
	map<wstring, CResPtr<CMaterial>>& GetMtrlMap()   { return m_mapMat; }
	map<wstring, CResPtr<CSound>>& GetSoundMap()     { return m_mapSound; }
	vector<CResPtr<CRes>>& GetCloneMap()             { return m_vecCloneRes; }

private:
	CMesh*    FindMesh(const wstring& _strKey);
	CTexture* FindTexture(const wstring& _strKey);
	CPrefab*  FindPrefab(const wstring& _strKey);

	void CreateDefaultMesh();
	void CreateDefaultMaterial();
	void InitFMOD();

public:
	CMaterial* FindMaterial(const wstring& _strKey);
	CSound*	  FindSound(const wstring& _strKey);

public:
	bool IsChange() { return m_bChange; }
	void SetChange(bool _bChange) { m_bChange = _bChange; }

private:
	void SaveResource(FILE* _pFile);
	void LoadResource(FILE* _pFile);

public:
	template<typename T>
	CRes* Load(const wstring& _strKey, const wstring& _strFilePath = L"");

	friend class CListDlg;
	friend class CSaveLoadMgr;
};

template<typename T>
inline CRes * CResMgr::Load(const wstring & _strKey, const wstring & _strFilePath)
{
	m_bChange = true;

	const type_info& info = typeid(T);

	if (&info == &typeid(CMesh))
	{
		return (CRes*)FindMesh(_strKey);
	}
	else if (&info == &typeid(CTexture))
	{
		CTexture* pTex = FindTexture(_strKey);

		if (NULL != pTex)
			return pTex;

		wstring strFullPath = CPathMgr::GetResPath();
		strFullPath += _strFilePath;

		pTex = CTexture::Create(strFullPath);

		if (NULL == pTex)
			return NULL;

		pTex->SetKey(_strKey);
		pTex->SetPath(_strFilePath);
		m_mapTex.insert(make_pair(_strKey, pTex));

		return (CRes*)pTex;
	}
	else if (&info == &typeid(CPrefab))
	{
		return (CRes*)FindPrefab(_strKey);
	}
	else if (&info == &typeid(CSound))
	{
		CSound* pSound = FindSound(_strKey);

		if (NULL != pSound)
			return pSound;

		wstring strFullPath = CPathMgr::GetResPath();
		strFullPath += _strFilePath;

		pSound = CSound::Create(strFullPath);

		if (NULL == pSound)
			return NULL;

		pSound->SetKey(_strKey);
		pSound->SetPath(_strFilePath);
		m_mapSound.insert(make_pair(_strKey, pSound));

		return (CRes*)pSound;
	}

	return NULL;
}
