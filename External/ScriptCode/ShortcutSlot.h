#pragma once
#include "Script.h"
#include "ShortcutWindow.h"

class CItemScript;
class CShortcutSlot :
	public CScript
{
private:
	// 생성시 반드시 초기화 const &로 쓰고싶지만 스크립트 생성자는 통일성을 위해서 복사생성자를 만들면 안되기 때문에 할 수 없이 포인터를 사용한다.
	CShortcutWindow* m_pShortcutWindow;
	void SetShortcutWindow(CShortcutWindow* _pShortcutWindow) { m_pShortcutWindow = _pShortcutWindow; }

	UINT m_iIndex;
	Vec3  m_vPos;
	Vec3  m_vScale;
	bool	m_bColl;

	// 스킬 발동용으로 설계.
	// 날라가도 상관없다 참조형으로 만 쓸것이다.
	CItemScript*	m_pItemScript;
	// 껍데기 Obj
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

