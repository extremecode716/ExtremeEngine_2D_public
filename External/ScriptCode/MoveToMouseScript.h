#pragma once
#include "Script.h"
class CMoveToMouseScript :
	public CScript
{
private:
	CGameObject* m_pParentObj;
	wstring		 m_strParentName;
	CGameObject* m_pMouseObj;
	bool		m_bCollMouse;
	bool        m_bClicked;

	Vec3		m_vOffsetPos;

private:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther) override;
	virtual void OnCollisionExit(CCollider* _pOther) override;

public:
	void SetOffsetPos(const Vec3& _vPos);
	void SetParentName(const wstring& _strName);

public:
	virtual void start() override;
	virtual int update() override;

public:
	virtual CMoveToMouseScript* Clone() override { return new CMoveToMouseScript(*this); }

public:
	CMoveToMouseScript();
	virtual ~CMoveToMouseScript();
};

