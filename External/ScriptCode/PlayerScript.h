#pragma once
#include "Script.h"

#include "DefineCode\DefineScript.h"
#include "..\DefineCode\StateMgr.h"
#include "WeaponScript.h"

#include "..\ScriptMgr\View\MediatorMgr.h"
#include "..\DefineCode\MessageColleaque.h"
#include "..\DefineCode\FindMessage.h"
#include "..\DefineCode\AttackMessage.h"
#include "..\DefineCode\PathFindingMessage.h"
#include "..\DefineCode\DieMessage.h"
#include "..\External\ScriptMgr\View\TileMgrScript.h"

enum class PLAYER_STATE
{
	STATE_NONE,
	STATE_START,
	STATE_IDLE,
	STATE_MOVE,
	STATE_FIRE,
	STATE_RELOAD,
	STATE_HIT,
	STATE_DIE,
	STATE_END
};

enum class PLAYER_MOVE_STATE
{
	STATE_MOVE_NONE,
	STATE_MOVE_DOWN,
	STATE_MOVE_UP,
	STATE_MOVE_LEFT,
	STATE_MOVE_RIGHT,
	STATE_MOVE_LOWERLEFT,
	STATE_MOVE_UPPERLEFT,
	STATE_MOVE_LOWERRIGHT,
	STATE_MOVE_UPPERRIGHT,
	STATE_MOVE_END
};

class CMediatorMgr;
class CColleaque;

class CUIMgr;
class CGaugeScript;
class CPlayerScript :
	public CScript
{
private:
	PLAYER_STATE				m_eState;
	CTransform*					m_pTransform;
	wstring						m_strCollqName;
	CStateMgr*					m_pStateMgr;

	float						m_fSurvivalTime;
	float						m_fTempTime;
	float						m_fMoveSpeed;
	float						m_fRotSpeed;

	tStatus						m_tStatus; // 스탯

	CMediatorMgr*				m_pMediator;
	CColleaque*					m_pCollq_Player;

	bool						m_bMove;
	DIRECTION_8					m_ePreDir;
	DIRECTION_8					m_eDir;
	Vec3					    m_vPrePos;
	Vec3		                m_vCurPos;
	Vec2						m_vMousePos;

	CFindMessage*				m_pFindMsg;
	CGameObject*				m_pMonster;

private:
	// 장비 착용
	CGameObject*				m_pWeaponObj;
	CGameObject*				m_pHeadObj;

	// UIMgr
	CUIMgr*						m_pUIMgr;
	CGaugeScript*				m_pHPScript;
	CGaugeScript*				m_pSPScript;

private:
	CTileMgrScript*				m_pTileMgrScript;
	stack<tPathNode*>			m_stackPath;

private:
	CPrefab* m_pEffect_Critical;
	CPrefab* m_pEffect_Damage;
	CMaterial*	m_pMtrl;

	// 임시 공격력
	int						m_iMinDamage;
	int						m_iMaxDamage;

protected:
	void    InputKey();

public:
	void Recovery(const wstring& _strType, int _iRecovery);

public:
	float	GetMoveSpeed() const { return m_fMoveSpeed; }
	const wstring& GetCollqName() const { return m_strCollqName; }
	stack<tPathNode*>& GetStackPath() { return m_stackPath; }
	CUIMgr*	GetUIMgr() const { return m_pUIMgr; }
	CColleaque* GetCollq() const { return m_pCollq_Player; }
	void Reset();

private:
	bool IsMove();
	float DistanceToPos(const Vec2& _vPos);
	float GetAngleToPos(const Vec2& _vPos);
	float GetMoveAngle();
	DIRECTION_8 GetDirectionToPos(const Vec2& _vPos);
	DIRECTION_8 GetDir() const { return m_eDir; }
	DIRECTION_8 GetPreDirection() const { return m_ePreDir; }
	CTileMgrScript* GetTileMgr() const { return m_pTileMgrScript; }
	void DirUpdate();

public:
	bool MoveToPos(const Vec2& _vecPos);
	void SoundEffectPlay(const int _idx);

public:
	bool ChangeState(const wstring& _strKey);
	void StateExecute();

public:
	virtual void start() override;
	virtual int update() override;

public:
	virtual void GetMessageData(CMessage* _pData) override;

public:
	virtual CPlayerScript* Clone() override { return new CPlayerScript(*this); }

public:
	CPlayerScript();
	virtual ~CPlayerScript();

	friend class CPlayerAttackState;
	friend class CPlayerDieState;
	friend class CPlayerIdleState;
	friend class CPlayerMoveState;
	friend class CPlayerPickUpState;
	friend class CPlayerStadingState;

};

