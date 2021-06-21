#pragma once
#include "Script.h"
#include "DefineCode\DefineScript.h"

class CMouseScript;
class CEquipSlot;
class CInventory;
class CItemScript;
class CEquipmentWindow :
	public CScript
{
private:
	wstring m_strName;
	Vec2	m_vPos;
	Vec2	m_vScale;

	Vec3    m_vSlotScale;

	CInventory* m_pInven;

	// ÀåºñÄ­
	CEquipSlot* m_pHead1;
	CEquipSlot* m_pHead2;
	CEquipSlot* m_pHead3;
	CEquipSlot* m_pBody;
	CEquipSlot* m_pR_Hand;
	CEquipSlot* m_pL_Hand;
	CEquipSlot* m_pRobe;
	CEquipSlot* m_pShoes;
	CEquipSlot* m_pAcc1;
	CEquipSlot* m_pAcc2;

	CEquipSlot* m_pFocusSlot;

	bool m_bOpen;
	bool m_bColl;

	CMouseScript* m_pMouseMgr;

private:
	CMaterial* m_pBackMtrl;

private:
	tDrawStringInfo     m_tTitleText;
	Vec2				m_vTitleTextOffset;

private:
	void InitEquip();
	void CreateEquipSlots();
	bool IsEquip(CItemScript* _pItemScript);
	void ChangeEquipMtrl();

	bool HasFocusSlotItem();
	bool HasDragItem();
	float Distance(const Vec2& _vSrcPos, const Vec2& _vDestPos);

public:
	bool EquipItem(CItemScript* _pItemScript);
	void SetFocusSlot(CEquipSlot* _pSlot);

public:
	virtual void awake() override;
	virtual void start() override;
	virtual int update() override;
	virtual int lateupdate() override;

private:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther) override;
	virtual void OnCollisionExit(CCollider* _pOther) override;

public:
	virtual CEquipmentWindow* Clone() override { return new CEquipmentWindow(*this); }

public:
	CEquipmentWindow();
	virtual ~CEquipmentWindow();

	friend class CEquipSlot;
};

