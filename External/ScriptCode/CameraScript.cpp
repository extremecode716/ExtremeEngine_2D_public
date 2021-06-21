#include "stdafx.h"
#include "CameraScript.h"


CCameraScript::CCameraScript()
	: m_fScale(1.f)
	, m_pTargetObj(NULL)
{
}

CCameraScript::~CCameraScript()
{
}

void CCameraScript::start()
{
	////////////////
	// Dont Destory
	///////////////
	static bool bDont = false;
	if (bDont == true) return;
	CSceneMgr::GetInst()->DontDestroyOnLoad(GetGameObject());
	bDont = true;

	CLayer* pCamLayer = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Player");
	m_pTargetObj = pCamLayer->FindObjectByTag(L"Player");
	if (NULL != m_pTargetObj)
	{
		//...
	}

	Camera()->SetAllLayerRenderCheck();

	//Camera()->LayerRenderCheck(L"Portal");
	//Camera()->LayerRenderCheck(L"Player");
	//Camera()->LayerRenderCheck(L"Tile");
}

int CCameraScript::update()
{
	if (NULL == m_pTargetObj)
	{
		CLayer* pCamLayer = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Player");
		m_pTargetObj = pCamLayer->FindObjectByTag(L"Player");
		if (NULL == m_pTargetObj)
			return RET_FAILED;
	}

	Vec3 vTargetPos = m_pTargetObj->Transform()->GetLocalPos();
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_PAGEUP, KEY_STATE::STATE_HOLD))
	{
		m_fScale += DT();
		Camera()->SetScale(m_fScale);
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_PAGEDOWN, KEY_STATE::STATE_HOLD))
	{
		m_fScale -= DT();
		Camera()->SetScale(m_fScale);
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_T, KEY_STATE::STATE_HOLD))
	{
		//CTileMgrScript* pScript = CTileMgrScript::GetInst();
	}

	//if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_ALT, KEY_STATE::STATE_TAB))
	//{
	//	struct PIXEL {
	//		BYTE r, g, b, a;
	//	};
	//	CTexture* pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Test");
	//	PIXEL* pPixel = (PIXEL*)pTex->GetPixel();

	//	UINT iWidth = pTex->GetWidth();
	//	UINT iHeight = pTex->GetHeight();

	//	for (UINT i = 0; i < iHeight / 2; ++i)
	//	{
	//		for (UINT j = 0; j < iWidth; ++j)
	//		{
	//			pPixel[i * iWidth + j] = PIXEL{ 0, 0, 0, 0 };
	//		}
	//	}

	//	pTex->ResetImage();
	//}

	Camera()->SetPos(Vec3(vTargetPos.x, vTargetPos.y, -1.f));

	return RET_SUCCESS;
}
