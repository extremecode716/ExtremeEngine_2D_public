#include "stdafx.h"
#include "PortalScript.h"
#include "..\External\ScriptMgr\View\SceneTable.h"

#include "PlayerScript.h"
#include "Camera.h"

CPortalScript::CPortalScript()
	: m_vPos{}
	, m_vScale{}
	, m_vSpawnPos{}
	, m_bText(false)
	, m_pCamera(NULL)
{
}


CPortalScript::~CPortalScript()
{
	if (true == m_bText)
	{
		CFontEngine::GetInst()->eraseText(m_tTitleText.GetKey());
	}
}

void CPortalScript::SoundEffectPlay()
{
	CSound* pSound = CResMgr::GetInst()->FindSound(L"ef_portal");
	if (NULL != pSound)
	{
		pSound->Play(1);
	}
}

void CPortalScript::SetTitleText(const wstring & _strTitleKey, const wstring & _strTitleText)
{
	m_strTitleKey = _strTitleKey;
	m_strTitleText = _strTitleText;
}

void CPortalScript::start()
{
	// Text
	if (m_strTitleKey != L"")
	{
		m_vPos = Transform()->GetLocal2DPos();
		m_tTitleText.SetDrawInfo(m_strTitleKey, false, m_strTitleText, 50.f, 0, 0, 0xff000000);
		bool bInsert = CFontEngine::GetInst()->InsertText(m_tTitleText.GetKey(), m_tTitleText);

		UINT iTextSize = m_strTitleText.length();
		m_vTitleTextOffset = Vec2(-25.f * iTextSize, 200.f);
		m_bText = true;
		m_pCamera = NULL;
	}
}

int CPortalScript::update()
{
	if (m_bText == false) return RET_FAILED;

	if (m_pCamera == NULL)
	{
		m_pCamera = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Camera")->FindWithTag(L"MainCamera");
	}
	if (m_pCamera != NULL)
	{
		m_tTitleText.SetShow(true);
		m_vPos = Transform()->GetLocal2DPos();
		m_vCameraPos = m_pCamera->Transform()->GetLocal2DPos();
		m_vPos = m_vPos + m_vTitleTextOffset;
		m_tTitleText.SetPos(m_vPos, m_vCameraPos);
		CFontEngine::GetInst()->ChangeText(m_tTitleText.GetKey(), m_tTitleText);
	}

	return RET_SUCCESS;
}

void CPortalScript::OnCollisionEnter(CCollider * _pOther)
{

	if (_pOther->GetGameObject()->GetTag() == L"Player")
	{
		CPlayerScript* pPlayerScript = _pOther->GetGameObject()->Script<CPlayerScript>();
		if (NULL != pPlayerScript)
		{
			pPlayerScript->Reset();
			/*Safe_Delete_Stack(_pOther->GetGameObject()->Script<CPlayerScript>()->GetStackPath());*/
			_pOther->GetGameObject()->Transform()->SetLocalPos(m_vSpawnPos);
			CSceneTable::GetThis()->ChangeScene(m_strSceneKey);
			SoundEffectPlay();
		}
	}
}

void CPortalScript::OnCollisionExit(CCollider * _pOther)
{
}

