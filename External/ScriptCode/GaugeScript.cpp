#include "stdafx.h"
#include "GaugeScript.h"

CGaugeScript::CGaugeScript()
	: m_iMaxGauge(1)
	, m_iGauge(1)
	, m_pMtrl(NULL)
	, m_pTex(NULL)
	, m_bText(false)
	, m_pCamera(NULL)
{
}


CGaugeScript::~CGaugeScript()
{
	SAFE_DELETE(m_pMtrl);

	if (true == m_bText)
	{
		CFontEngine::GetInst()->eraseText(m_tGaugeText.GetKey());
	}
}

void CGaugeScript::SetGauge(int _iMaxGauge, int _iGauge)
{
	m_iMaxGauge = _iMaxGauge;
	m_iGauge = _iGauge;

	float fPercent = (m_iGauge / (float)m_iMaxGauge);
	fPercent = (fPercent < 0) ? 0 : fPercent;
	Vec4 vHPSplit = { 0.f, 0.f, fPercent, 1.f };
	m_pMtrl->SetData(SHADER_PARAM::SP_VEC4_0, &vHPSplit);
}

void CGaugeScript::SetGaugeText(const wstring & _strKey, const Vec2& _vOffset)
{
	m_strGaugeKey = _strKey;
	m_vGaugeTextOffset = _vOffset;

	m_tGaugeText.SetDrawInfo(m_strGaugeKey, false, m_strGaugeText, 20.f, 0, 0, 0xff000000);
	CFontEngine::GetInst()->InsertText(m_tGaugeText.GetKey(), m_tGaugeText);
	m_bText = true;
	m_pCamera = NULL;
}

void CGaugeScript::SetMtrl(CMaterial * _pMtrl)
{
	m_pMtrl = _pMtrl;
	MeshRender()->SetMaterial(m_pMtrl);
}

void CGaugeScript::SetTex(CTexture * _pTex)
{
	if (NULL == m_pMtrl) return;
	m_pTex = _pTex;
	m_pMtrl->SetData(SHADER_PARAM::SP_TEX_0, &m_pTex);
}

void CGaugeScript::SetColor(const Vec4 & _vColor)
{
	if (NULL == m_pMtrl) return;
	m_vColor = _vColor;
	m_pMtrl->SetData(SHADER_PARAM::SP_VEC4_1, &m_vColor);
	int iColorOn = 1;
	m_pMtrl->SetData(SHADER_PARAM::SP_INT_0, &iColorOn);
}

void CGaugeScript::start()
{
}

int CGaugeScript::update()
{
	if (false == m_bText) return RET_FAILED;
	if (m_pCamera == NULL)
	{
		m_pCamera = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Camera")->FindWithTag(L"MainCamera");
	}
	if (m_pCamera != NULL)
	{
		m_tGaugeText.SetShow(true);
		m_vPos = Transform()->GetWorld2DPos();
		m_vCameraPos = m_pCamera->Transform()->GetLocal2DPos();
		m_tGaugeText.strText = wstring(m_strGaugeKey + L" : " + to_wstring(m_iGauge) + L" / " + to_wstring(m_iMaxGauge));
		UINT istrLenght = m_tGaugeText.strText.length();
		Vec2 vOffset = Vec2(m_vGaugeTextOffset.x - istrLenght * 5.f, m_vGaugeTextOffset.y + 10.f);
		m_vPos = m_vPos + vOffset;
		m_tGaugeText.SetPos(m_vPos, m_vCameraPos);
		CFontEngine::GetInst()->ChangeText(m_tGaugeText.GetKey(), m_tGaugeText);
	}

	return RET_SUCCESS;
}
