#pragma once
#include "Script.h"

class CMouseScript;
class CSlot;
class CItemScript;
class CInventory :
	public CScript
{
private:
	wstring				m_strName;
	Vec2				m_vPos;
	Vec2				m_vSize;

	Vec3				m_vSlotStartPos;
	Vec3				m_vSlotScale;
	UINT				m_iSlotCount;
	vector<CSlot*>		m_vecSlot;

	bool				m_bOpen;

	CSlot*				m_pFocusSlot;
	bool				m_bColl;

	CMouseScript*		m_pMouseMgr;

private:
	CMaterial*			m_pBackMtrl;
	CMaterial*			m_pTapMtrl;
	CMaterial*			m_pTitleMtrl;
	CMaterial*			m_pExitMtrl;

private:
	tDrawStringInfo     m_tTitleText;
	Vec2				m_vTitleTextOffset;

private:
	bool IsIndex(UINT _index);
	bool IsEmpty(UINT _index);
	void SetSlotPos(UINT _index, const Vec2& _vPos);
	void SetSlotSize(UINT _index, const Vec2& _vSize);

	void ChangeInventoryMtrl();
	void CreateSlots();
	Vec3 InitSlotPos(UINT _index);

	bool HasFocusSlotItem();
	bool HasDragItem();

public:
	void Init(const wstring& _strName, UINT _iSlotCount);
	UINT GetSlotIndex(const Vec2& _vPos);
	bool PushItem(CItemScript* _pItemScript);
	bool PopItem(CItemScript* _pItemScript);

	float Distance(const Vec2& _vSrcPos, const Vec2& _vDestPos);
	void SetFocusSlot(CSlot* _pSlot);

public:
	bool IsOpen() const { return m_bOpen; }

private:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther) override;
	virtual void OnCollisionExit(CCollider* _pOther) override;

public:
	virtual void awake() override;
	virtual void start() override;
	virtual int update() override;
	virtual int lateupdate() override;

public:
	virtual CInventory* Clone() override { return new CInventory(*this); }

public:
	CInventory();
	virtual ~CInventory();

	friend class CSlot;
};

