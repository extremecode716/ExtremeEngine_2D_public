#pragma once
#include "Script.h"

#include "Inventory.h"

class CUIMgr :
	public CScript
{
	Vec2  m_vPos;
	CGameObject* m_pPlayerObj;


	bool				m_bText;
	wstring				m_strJopKey;
	wstring				m_strJopText;
	tDrawStringInfo     m_tJopText;
	Vec2				m_vJopTextOffset;

	CGameObject*		m_pCamera;
	Vec2				m_vCameraPos;

	CInventory*			m_pInventory;

private:
	bool IsInvenOpen();

public:
	virtual void awake() override;
	virtual int update() override;

public:
	virtual CUIMgr* Clone() override { return new CUIMgr(*this); }

public:
	CUIMgr();
	virtual ~CUIMgr();

	friend class CPlayerScript;
};

