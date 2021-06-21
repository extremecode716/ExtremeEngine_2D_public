#pragma once
#include "Script.h"

#include "..\ScriptMgr\View\MediatorMgr.h"
#include "..\DefineCode\MessageColleaque.h"

class CGameObject;
class CTileMgrScript;

enum class RESPAWN_STATE
{
	STATE_NONE,
	STATE_START,
	STATE_RESPAWN,
	STATE_IDLE,
	STATE_STOP,
	STATE_END
};

class CRespawnScript :
	public CScript
{
private:
	wstring				m_strRespawnCollq;
	CMediatorMgr*		m_pMediator;
	CColleaque*			m_pCollq_Respawn;

	RESPAWN_STATE		m_eState;
	CTransform*			m_pTransform;

	float				m_fTempTime;
	float				m_fRespawnDelayTime;
	bool				m_isActive;

	// 현재 생성된 몬스터 수
	int					m_iCount;
	// 최대로 생성할 몬스터 수
	int					m_iMaxCount;


private:
	list<CGameObject*>  m_listRepawnObj;
	CGameObject*		m_pRecentlyObj; // 최근 생성된 오브젝트
	CTileMgrScript*     m_pTileMgr;		

private:
	void SetCollqName(const wstring& _strCollq) { m_strRespawnCollq = _strCollq; }

public:
	void SetRespawnDelayTime(float _fTime) { m_fRespawnDelayTime = _fTime; }

public:
	void push_backRepawnObj(CGameObject* _pObj);
	void SetMaxCount(int _imaxCount) { m_iMaxCount = _imaxCount; }
	CGameObject* Create(const wstring& _strTag);

private:
	virtual void GetMessageData(CMessage* _pData) override;

public:
	virtual void start() override;
	virtual int update() override;

public:
	virtual CRespawnScript* Clone() override { return new CRespawnScript(*this); }

public:
	CRespawnScript();
	virtual ~CRespawnScript();
};

