#include "stdafx.h"
#include "ShortcutWindow.h"
#include "ShortcutSlot.h"
#include "PlayerScript.h"


CShortcutWindow::CShortcutWindow()
	: m_pPlayerScript(NULL)
	, m_vPos{}
	, m_vScale{}
	, m_iVecSize(10)
{
}


CShortcutWindow::~CShortcutWindow()
{
}

void CShortcutWindow::start()
{
	// 너무 높은 의존도... 일단 사용
	m_pPlayerScript = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Player")->FindWithTag(L"Player")->Script<CPlayerScript>();
	m_strName = L"PlayerShortcut";
	m_vPos = Transform()->GetLocalPos();
	m_vScale = Transform()->GetLocalScale();

	m_vecSlot.resize(m_iVecSize);
	m_vecSlotOffset.resize(m_iVecSize);

	InitShortcutSlotOffset();
	CreateShortcutSlot();
}

int CShortcutWindow::update()
{
	// 메세지 형식으로 플레이어한테 액션을 보낼까....?
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_1, KEY_STATE::STATE_TAB))
	{
		m_vecSlot[0]->Action(m_pPlayerScript);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_2, KEY_STATE::STATE_TAB))
	{
		m_vecSlot[1]->Action(m_pPlayerScript);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_3, KEY_STATE::STATE_TAB))
	{
		m_vecSlot[2]->Action(m_pPlayerScript);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_4, KEY_STATE::STATE_TAB))
	{
		m_vecSlot[3]->Action(m_pPlayerScript);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_5, KEY_STATE::STATE_TAB))
	{
		m_vecSlot[4]->Action(m_pPlayerScript);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_6, KEY_STATE::STATE_TAB))
	{
		m_vecSlot[5]->Action(m_pPlayerScript);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_7, KEY_STATE::STATE_TAB))
	{
		m_vecSlot[6]->Action(m_pPlayerScript);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_8, KEY_STATE::STATE_TAB))
	{
		m_vecSlot[7]->Action(m_pPlayerScript);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_9, KEY_STATE::STATE_TAB))
	{
		m_vecSlot[8]->Action(m_pPlayerScript);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_0, KEY_STATE::STATE_TAB))
	{
		m_vecSlot[9]->Action(m_pPlayerScript);
	}


	return RET_SUCCESS;
}

void CShortcutWindow::InitShortcutSlotOffset()
{
	// m_iVecSize 개수 만큼 - 10개 0~9
	Vec3 vSlotOffset = Vec3(-260.f, 0.f, 19.f);
	m_vecSlotOffset[0] = vSlotOffset;

	vSlotOffset = Vec3(-203.f, 0.f, 19.f);
	m_vecSlotOffset[1] = vSlotOffset;

	vSlotOffset = Vec3(-146.f, 0.f, 19.f);
	m_vecSlotOffset[2] = vSlotOffset;

	vSlotOffset = Vec3(-89.f, 0.f, 19.f);
	m_vecSlotOffset[3] = vSlotOffset;

	vSlotOffset = Vec3(-30.f, 0.f, 19.f);
	m_vecSlotOffset[4] = vSlotOffset;

	vSlotOffset = Vec3(29.f, 0.f, 19.f);
	m_vecSlotOffset[5] = vSlotOffset;

	vSlotOffset = Vec3(86.f, 0.f, 19.f);
	m_vecSlotOffset[6] = vSlotOffset;

	vSlotOffset = Vec3(145.f, 0.f, 19.f);
	m_vecSlotOffset[7] = vSlotOffset;

	vSlotOffset = Vec3(203.f, 0.f, 19.f);
	m_vecSlotOffset[8] = vSlotOffset;

	vSlotOffset = Vec3(259.f, 0.f, 19.f);
	m_vecSlotOffset[9] = vSlotOffset;

}

void CShortcutWindow::CreateShortcutSlot()
{
	CGameObject* pShortcutObj;
	for (UINT i = 0; i < m_iVecSize; ++i)
	{
		CShortcutSlot* pShortcutSlot = new CShortcutSlot();
		pShortcutSlot->SetShortcutWindow(this);
		pShortcutSlot->SetIndex(i);
		pShortcutSlot->SetLocalPos(m_vecSlotOffset[i]);
		pShortcutObj = pShortcutSlot->Create();
		GetGameObject()->AddChildObj(pShortcutObj);
		pShortcutObj->awake();
		pShortcutObj->start();
		m_vecSlot[i] = pShortcutSlot;
	}
}
