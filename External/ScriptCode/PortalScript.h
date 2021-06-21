#pragma once
#include "Script.h"

class CPortalScript :
	public CScript
{
private:
	// 이동할 키- SceneTable과 연동
	wstring m_strSceneKey;
	Vec3 m_vSpawnPos;
	Vec2 m_vPos;
	Vec2 m_vScale;

private:
	bool				m_bText;
	wstring				m_strTitleKey;
	wstring				m_strTitleText;
	tDrawStringInfo     m_tTitleText;
	Vec2				m_vTitleTextOffset;

	CGameObject*		m_pCamera;
	Vec2				m_vCameraPos;

private:
	void SoundEffectPlay();

public:
	void SetScenKey(const wstring& _strKey) { m_strSceneKey = _strKey; }
	void SetSpawnPos(const Vec3& _vSpawnPos) { m_vSpawnPos = _vSpawnPos; }
	void SetTitleText(const wstring& _strTitleKey, const wstring& _strTitleText);


public:
	virtual void start() override;
	virtual int update() override;

private:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollisionExit(CCollider* _pOther) override;

public:
	virtual CPortalScript* Clone() override { return new CPortalScript(*this); }

public:
	CPortalScript();
	virtual ~CPortalScript();
};

