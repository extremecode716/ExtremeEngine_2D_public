#pragma once
#include "Script.h"
#include "DefineScript.h"

// ½ºÅ³
#include "DefineCode\Skill.h"

class CItemScript :
	public CScript
{
protected:
	UINT				m_iIdx;
	wstring				m_strType;
	UINT				m_iType;
	wstring				m_strName;
	CTransform*			m_pTransform;
	int					m_iSlot;

	CMaterial*			m_pItemMtrl;
	CTexture*			m_pItemTex;

	CSkill*			    m_pSkill;

public:
	const UINT GetIDx() const { return m_iIdx; }
	const wstring& GetStrType() const { return m_strType; }
	const wstring& GetStrName() const { return m_strName; }
	const UINT GetType() const { return m_iType; }
	int GetSlot() const { return m_iSlot; }
	CMaterial* GetItemMtrl() const { return m_pItemMtrl; }
	CTexture* GetItemTex() const { return m_pItemTex; }

public:
	void SetSlot(int _islot) { m_iSlot = _islot; }
	void SetItemMtrl(CMaterial* _pItemMtrl);
	void SetItemTex(CTexture* _pItemTex);
	void SetSkill(CSkill* _pSkill) { m_pSkill = _pSkill; }

public:
	virtual bool Action(CScript* _pScript);

private:
	void SetObjPos(const Vec3& _vPos);
	void SetObjScale(const Vec3& _vScale);

public:
	virtual void start() override;
	virtual int update() override;

public:
	virtual CItemScript* Clone() override { return NULL; }

public:
	CItemScript();
	virtual ~CItemScript();
};

