#pragma once
#include "Script.h"
class CGaugeScript :
	public CScript
{
	int m_iMaxGauge;
	int m_iGauge;

	Vec2 m_vScale;
	Vec2 m_vPos;

	Vec4 m_vColor;
	CMaterial* m_pMtrl;
	CTexture* m_pTex;


	bool				m_bText;
	wstring				m_strGaugeKey;
	wstring				m_strGaugeText;
	tDrawStringInfo     m_tGaugeText;
	Vec2				m_vGaugeTextOffset;

	CGameObject*		m_pCamera;
	Vec2				m_vCameraPos;

public:
	void SetGauge(int _iMaxGauge, int _iGauge);
	void SetGaugeText(const wstring& _strKey, const Vec2& _vOffset);

public:
	void SetMtrl(CMaterial* _pMtrl);
	void SetTex(CTexture* _pTex);
	void SetColor(const Vec4& _vColor);

public:
	virtual void start() override;
	virtual int update() override;

public:
	virtual CGaugeScript* Clone() override { return new CGaugeScript(*this); }

public:
	CGaugeScript();
	virtual ~CGaugeScript();
};

