#pragma once
#include "Script.h"

class CInventory;
class CEquipmentWindow;
class CItemScript;
class CSlot : 
	public CScript
{
private:
	UINT m_iIndex;
	UINT m_iQuantity;

	Vec2 m_vPos;
	Vec2 m_vSize;

	CItemScript*	  m_pItemScript;

	CInventory*		  m_pInven;
	CEquipmentWindow* m_pEquipment;
	
private:
	bool m_bColl;
	int  m_iClickCount;
	bool m_bDoubleClicked;
	float m_fDoubleClickedMinTime;
	float m_fDoubleClickedTime;

public:
	void SetSlotIndex(UINT _index) { m_iIndex = _index; }
	void SetInventory(CInventory* _pInven) { m_pInven = _pInven; }
	bool IsEmpty();
	void PushItemScript(CItemScript* _pItemScript);
	void PopItemScript(UINT _iCount = 1);

	CItemScript* GetItemScript() { return m_pItemScript; }

	Vec2 GetPos() const { return m_vPos; }
	Vec2 GetSize() const { return m_vSize; }
	void SetPos(const Vec2& _vPos);
	void SetSize(const Vec2& _vSize);

	CGameObject* Create(const Vec3& _vPos, const Vec3& _vScale);

private:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther) override;
	virtual void OnCollisionExit(CCollider* _pOther) override;

public:
	virtual void start() override;
	virtual int update() override;

public:
	virtual CSlot* Clone() override { return new CSlot(*this); }

public:
	CSlot();
	virtual ~CSlot();
};
