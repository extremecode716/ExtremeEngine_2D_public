#pragma once

#include "global.h"

//////////////////////////
// 임시 사용할 스크립트들
//////////////////////////
//#include "PlayerScript.h" 
//#include "MonsterScript.h"
//#include "BasicBulletScript.h"
//#include "ParabolaBulletScript.h"
//#include "MissileBulletScript.h"
//#include "RevolveBulletScript.h"
//#include "RespawnScript.h"
//#include "RevolveItemScript.h"

enum class SCENE_STATE
{
	NONE,
	PLAY,
	PAUSE,
	STOP,
	END
};


class CScene;
class CGameObject;

class CSceneMgr
{
	SINGLE(CSceneMgr);

private:
	CScene*		        m_pCurScene;
	CScene*		        m_pPrevScene;
	CScene*				m_pNextScene;

	bool		        m_bUpdateEvent;
	SCENE_STATE			m_eState;
	CGameObject*		m_pToolCam;

	// DontDestoryOnLoad - Parent;
	map<wstring, CGameObject*>  m_mapDontDestoryObj;
	
	map<wstring, CGameObject*> m_mapCurDontDetoryObj;

private:
	void CreateTestScene();
	void CreateGameObject();
	void CreateMaterial();
	void MoveObjectsNextScene(CScene* _pNextScene);

public:
	void init();
	int progress();
	void render();

public:
	CScene* GetCurScene() { return m_pCurScene; }
	SCENE_STATE GetState() { return m_eState; }
	const map<wstring, CGameObject*>& GetDontDestroyObjs();

	void SetToolCam(CGameObject* _pCamObj) { m_pToolCam = _pCamObj; }

	bool IsPlayMode() { return (SCENE_STATE::PLAY == m_eState) ? true : false; }
	void ChangeScene(CScene* _pNextScene, bool bScript = false);
	void ChagneState(SCENE_STATE _eState);
	void DontDestroyOnLoad(CGameObject* _pObj);

#ifdef _EXTREME_TOOL
	void SetUpdateCheck(bool _bCheck) { m_bUpdateEvent = _bCheck; }
	bool GetUpdateCheck() { return m_bUpdateEvent; }
#endif
};

