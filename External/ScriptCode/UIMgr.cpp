#include "stdafx.h"
#include "UIMgr.h"
#include "GaugeScript.h"


CUIMgr::CUIMgr()
	: m_pPlayerObj(NULL)
	, m_vPos{}
	, m_pCamera(NULL)
	, m_vJopTextOffset{}
	, m_pInventory(NULL)
{
}

CUIMgr::~CUIMgr()
{
}

bool CUIMgr::IsInvenOpen()
{
	if (NULL == m_pInventory) return false;

	return 	m_pInventory->IsOpen();
}

void CUIMgr::awake()
{
	////////////////
	// Dont Destory
	///////////////
	static bool bDont = false;
	if (bDont == true) return;
	CSceneMgr::GetInst()->DontDestroyOnLoad(GetGameObject());
	bDont = true;

	m_pPlayerObj = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Player")->FindWithTag(L"Player");

	m_pInventory = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Default")->FindWithTag(L"Inventory")->Script<CInventory>();

	// Setting HPScript
	CGaugeScript* pHPScript = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Default")->FindWithTag(L"UI_HP")->Script<CGaugeScript>();
	CMaterial* pMtrl = CResMgr::GetInst()->FindMaterial(L"SpliteMtrl");
	pMtrl = pMtrl->Clone();
	pHPScript->SetMtrl(pMtrl);
	CTexture* pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"UI_HpbarTex");
	pHPScript->SetTex(pTex);
	pHPScript->SetColor(Vec4(1.f, 0.f, 0.f, 1.f));


	// Setting SPScript

	CGaugeScript* pSPScript = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Default")->FindWithTag(L"UI_SP")->Script<CGaugeScript>();
	pMtrl = CResMgr::GetInst()->FindMaterial(L"SpliteMtrl");
	pMtrl = pMtrl->Clone();
	pSPScript->SetMtrl(pMtrl);
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"UI_HpbarTex");
	pSPScript->SetTex(pTex);
	pSPScript->SetColor(Vec4(0.18f, 0.41f, 1.f, 1.f));

	// Text
	m_strJopKey = L"Jop";
	m_strJopText = L"Extreme Dealer";
	m_tJopText.SetDrawInfo(m_strJopKey, false, m_strJopText, 25.f, 0, 0, 0xff000000);
	UINT iIDLength = m_strJopText.length();
	CFontEngine::GetInst()->InsertText(m_tJopText.GetKey(), m_tJopText);
	m_vJopTextOffset = Vec2(-6.0f * iIDLength, 150.f);
	m_bText = true;
}

int CUIMgr::update()
{
	if (NULL == m_pPlayerObj) return RET_FAILED;

	m_vPos = m_pPlayerObj->Transform()->GetLocal2DPos();

	if (true == m_bText)
	{
		if (m_pCamera == NULL)
		{
			m_pCamera = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Camera")->FindWithTag(L"MainCamera");
		}
		if (m_pCamera != NULL)
		{
			m_tJopText.SetShow(true);
			m_vCameraPos = m_pCamera->Transform()->GetLocal2DPos();
			Vec2 vOffsetPos = m_vPos + m_vJopTextOffset;
			m_tJopText.SetPos(vOffsetPos, m_vCameraPos);
			CFontEngine::GetInst()->ChangeText(m_tJopText.GetKey(), m_tJopText);

		}
	}

	Transform()->SetLocal2DPos(m_vPos);

	return RET_SUCCESS;
}
