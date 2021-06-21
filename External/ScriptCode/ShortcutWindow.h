#pragma once
#include "Script.h"

class CShortcutSlot;
class CShortcutWindow :
	public CScript
{
private:
	CScript*	m_pPlayerScript;
	wstring m_strName;
	Vec3	m_vPos;
	Vec3	m_vScale;
	UINT    m_iVecSize;

	vector<CShortcutSlot*> m_vecSlot;
	vector<Vec3>		   m_vecSlotOffset;

private:
	void InitShortcutSlotOffset();
	void CreateShortcutSlot();
	vector<CShortcutSlot*>& GetSlots() { return m_vecSlot; }

protected:
	virtual void start() override;
	virtual int update() override;

public:
	virtual CShortcutWindow* Clone() override { return new CShortcutWindow(*this); }

public:
	CShortcutWindow();
	virtual ~CShortcutWindow();

	friend class CShortcutSlot;
};

