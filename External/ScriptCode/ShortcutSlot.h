#pragma once
#include "Script.h"
#include "ShortcutWindow.h"

class CItemScript;
class CShortcutSlot :
	public CScript
{
private:
	// ������ �ݵ�� �ʱ�ȭ const &�� ��������� ��ũ��Ʈ �����ڴ� ���ϼ��� ���ؼ� ��������ڸ� ����� �ȵǱ� ������ �� �� ���� �����͸� ����Ѵ�.
	CShortcutWindow* m_pShortcutWindow;
	void SetShortcutWindow(CShortcutWindow* _pShortcutWindow) { m_pShortcutWindow = _pShortcutWindow; }

	UINT m_iIndex;
	Vec3  m_vPos;
	Vec3  m_vScale;
	bool	m_bColl;

	// ��ų �ߵ������� ����.
	// ���󰡵� ������� ���������� �� �����̴�.
	CItemScript*	m_pItemScript;
	// ������ Obj
	CGameObject*	m_pTempObj; 

	CResPtr<CPrefab> m_pEffectPrefab;

public:
	CItemScript* GetItemScript() const { return m_pItemScript; }
	void CreateEffectToSlot();

public:
	void SetIndex(UINT _iIndex) { m_iIndex = _iIndex; }
	void SetLocalPos(const Vec3& _vPos);

public:
	bool IsEmpty();
	bool PushItem(CItemScript* _pItemScript);
	CGameObject* Create();
	bool Action(CScript* _pScript);

private:
	virtual void start() override;
	virtual int update() override;

private:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther) override;
	virtual void OnCollisionExit(CCollider* _pOther) override;

public:
	virtual CShortcutSlot* Clone() override { return new CShortcutSlot(*this); }

public:
	CShortcutSlot();
	virtual ~CShortcutSlot();

	friend class CShortcutWindow;
};

