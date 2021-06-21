#pragma once
#include "Script.h"

enum class BULLET_STATE
{
	STATE_NONE,
	STATE_START,
	STATE_UPDATE,
	STATE_DELETE,
	STATE_END
};

class CBulletScript :
	public CScript
{
protected:
	UINT				m_Idx;
	wstring				m_strName;
	CGameObject*		m_pOwnerObj;
	CTransform*			m_pTransform;
	BULLET_STATE	    m_eState;

	Vec3				m_vStartPos;
	Vec3				m_vStartRot;
	float				m_fElapsedTimeAfterFire;
	float				m_fDeleteTime;

	//°ø°Ý·Â
	float				m_fAttack;

public:
	virtual void start() override = 0;
	virtual int update() override = 0;

public:
	virtual void SetOwerObj(CGameObject* _Obj) { m_pOwnerObj = _Obj; }
	virtual void SetStartPos(const Vec3& _vecPos){ m_vStartPos = _vecPos; }
	virtual void SetStartRot(const Vec3& _vecRot){ m_vStartRot = _vecRot; }
	virtual void SetAttack(float _fAttack) { m_fAttack = _fAttack; }
	virtual void SetDeleteTime(float _fDeleteTime) { m_fDeleteTime = _fDeleteTime; }
	virtual CGameObject* GetOwerObj() { return m_pOwnerObj; }
	virtual float GetAttack() const { return m_fAttack; }

public:
	virtual CBulletScript* Clone() override = 0;

public:
	CBulletScript();
	virtual	~CBulletScript();
};

