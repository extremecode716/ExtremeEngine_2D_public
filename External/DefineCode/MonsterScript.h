#pragma once
#include "Script.h"

#include "DefineScript.h"
#include "StateMgr.h"
#include "..\External\ScriptMgr\View\MonsterTable.h"

#include "..\ScriptMgr\View\MediatorMgr.h"
#include "..\DefineCode\MessageColleaque.h"

#include "..\ScriptMgr\View\TileMgrScript.h"
#include "..\DefineCode\PathFindingMessage.h"

class CMediatorMgr;
class CColleaque;
class CTileMgrScript;

class CMonsterScript :
	public CScript
{
protected:
	bool				m_bDie;
	CStateMgr*			m_pStateMgr;
	CMediatorMgr*		m_pMediator;
	CColleaque*         m_pCollq_Monster;
	CTransform*			m_pTransform;
	wstring				m_strCollqName;

	MONSTER_AGGRESSIVE_TYPE  m_eAggressiveType;
	tStatus				m_tStatus; // 스탯

	float				m_fSurvivalTime;
	float				m_fTempTime;
	float				m_fMoveSpeed;
	float				m_fRotSpeed;

	bool				m_bMove;
	DIRECTION_8		    m_eDir;
	DIRECTION_8			m_ePreDir;
	Vec3		        m_vPrePos;
	Vec3		        m_vCurPos;

	CTileMgrScript*		m_pTileMgr;
	stack<tPathNode*>	m_stackPath;
	float				m_fSearchTime;
	float				m_fSearchTempTime;
	float				m_iSearchMaxX;
	float				m_iSearchMaxY;
	bool				m_IsMove;
	float				m_fPivot;

	// 임시 공격력
	int					m_iMinDamage;
	int					m_iMaxDamage;
	bool				m_bHit;
	float				m_fAttackRange;
	CGameObject*		m_pAttackerObj; // 몬스터를 공격하는 Obj

	// 리스폰 됬을 경우 리스폰 된 곳의 이름을 정해준다.
	wstring				m_strRespawnCollqName;

protected:
	CPrefab*			m_pEffect_Damage;

protected:
	float Lerp(const float _a, const float _b, float _t);
	void SetSearchTime(float _fTime) { m_fSearchTime = _fTime; }
	void SetSearchMaxPos(float _iX, float _iY);

public:
	bool ChangeState(const wstring& _strKey);
	void DirUpdate();
	int SearchPathUpdate(int _iSearchX, int _iSearchY, CGameObject* _pSearchObj = NULL);
	bool MoveToPos(const Vec2& _vecPos);
	float DistanceToPos(const Vec2& _vPos);
	virtual void Reset();
	virtual void SoundEffectPlay(const int _idx) {};

public:
	void SetRespawnCollqName(const wstring& _strCollqName) { m_strRespawnCollqName = _strCollqName; }
	void SetCollqName(const wstring& _strCollqName) { m_strCollqName = _strCollqName; }
	void SetAggressiveType(MONSTER_AGGRESSIVE_TYPE _eType) { m_eAggressiveType = _eType; }
	void SetSpeed(float _fSpeed) { m_fMoveSpeed = _fSpeed; }
	void ResetAttackerObj() { m_pAttackerObj = NULL; }

public:
	bool IsDie() const { return m_bDie; }
	const wstring& GetCollqName() const { return m_pCollq_Monster->GetName(); }
	MONSTER_AGGRESSIVE_TYPE GetAggressiveType() const { return m_eAggressiveType; }
	float GetMoveAngle();
	DIRECTION_8 GetDirection();
	tStatus& GetStatus() { return m_tStatus; }
	const wstring& GetRespawnCollqName() const { return m_strRespawnCollqName; }
	float GetMoveSpeed() const { return m_fMoveSpeed; }
	DIRECTION_8 GetDir() const { return m_eDir; }
	DIRECTION_8 GetPreDirection() const { return m_ePreDir; }
	stack<tPathNode*>& GetStackPath() { return m_stackPath; }
	CTileMgrScript* GetTileMgr() { return m_pTileMgr; }
	CGameObject* GetAttackerObj() const { return m_pAttackerObj; }
	CColleaque* GetCollq() const { return m_pCollq_Monster; }
	CPrefab* GetEffectDamage() const { return m_pEffect_Damage; }
	bool IsHit() const { return m_bHit; }
	bool IsMove();
	float GetPivot() const { return m_fPivot; }
	int GetMinDamage() const { return m_iMinDamage; }
	int GetMaxDamage() const { return m_iMaxDamage; }

public:
	virtual void start() override;
	virtual int update() override = 0 ;

public:
	virtual void GetMessageData(CMessage* _pData) override;

public:
	virtual CMonsterScript* Clone() override = 0;

public:
	CMonsterScript();
	virtual ~CMonsterScript();
};
