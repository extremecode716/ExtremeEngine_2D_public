#pragma once
#include "..\SingletonScript.h"

class CMediatorMgr;
class CColleaque;
class CTileMgrScript;
class CMouseScript :
	public CSingletonScript<CMouseScript>
{
private:
	CScene*		    m_pScene;
	Vec2		    m_vOffset;
	Vec2            m_vMousePos;
	Vec2			m_vMouseObjPos;
	Vec3	        m_vObjSize;

	bool			m_bColl;

private:
	CMediatorMgr*   m_pMediator;
	CColleaque*		m_pCollq_Mouse;

private:
	CGameObject*    m_pDragObj;

	CTileMgrScript* m_pTileMgrScript;
	CGameObject*	m_pFocuseTileObj;
	CMaterial*		m_pFocsueMtrl;

public:
	const Vec2& GetMousePos() const { return m_vMousePos; }
	CGameObject* GetDragObj() { return m_pDragObj; }

public:
	void SetObjSize(const Vec3& _vec);
	bool SetDragObj(CGameObject* _pDragObj);

protected:
	virtual void OnCollision(CCollider* _pOther) override;
	virtual void OnCollisionExit(CCollider* _pOther) override;

public:
	virtual void start() override;
	virtual int update() override;

public:
	virtual CMouseScript* Clone() override { return new CMouseScript(*this); }
public:
	CMouseScript();
	virtual ~CMouseScript();
};

