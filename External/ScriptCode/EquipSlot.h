#pragma once
#include "Script.h"
#include "DefineCode\\DefineScript.h"

class CEquipmentWindow;
class CInventory;
class CItemScript;
class CEquipSlot :
	public CScript
{
private:
	CInventory* m_pInven;
	CEquipmentWindow* m_pEquipment;
	UINT m_iSlotType;

	Vec3 m_vPos;
	Vec3 m_vScale;

	CItemScript* m_pEquipItemScript;

private:
	bool m_bColl;
	int  m_iClickCount;
	bool m_bDoubleClicked;
	float m_fDoubleClickedMinTime;
	float m_fDoubleClickedTime;

public:
	bool IsEmpty();
	void SetSlotType(UINT _iSlotType) { m_iSlotType = _iSlotType; }
	CItemScript* GetItemScript() { return m_pEquipItemScript; }
	bool EquipItem(CItemScript* _pItemScript);
	void PopItemScript();

	void SetEquipment(CEquipmentWindow* _pEquipment) { m_pEquipment = _pEquipment; }
	void SetPos(const Vec3& _vPos) { m_vPos = _vPos; }
	void SetScale(const Vec3& _vScale) { m_vScale = _vScale; }

public:
	CGameObject* Create();


protected:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther) override;
	virtual void OnCollisionExit(CCollider* _pOther) override;

protected:
	virtual void start() override;
	virtual int update() override;

public:
	virtual CEquipSlot* Clone() override { return new CEquipSlot(*this); }

public:
	CEquipSlot();
	~CEquipSlot();
};

