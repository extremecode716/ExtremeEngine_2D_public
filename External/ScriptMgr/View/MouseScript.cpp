#include "stdafx.h"
#include "MouseScript.h"

#include "MediatorMgr.h"
#include "..\External\DefineCode\MessageColleaque.h"
#include "..\External\DefineCode\FindMessage.h"
#include "TileMgrScript.h"

CMouseScript::CMouseScript()
	: m_pScene(NULL)
	, m_vOffset{ 13.f, 25.f }
	, m_vMousePos{ -1000.f, -1000.f }
	, m_vMouseObjPos{ 0.f, 0.f }
	, m_vObjSize{ 100.f, 100.f, 100.f }
	, m_bColl(false)
	, m_pDragObj(NULL)
	, m_pTileMgrScript(NULL)
	, m_pFocuseTileObj(NULL)
	, m_pFocsueMtrl(NULL)
{
}

CMouseScript::~CMouseScript()
{
	SAFE_DELETE(m_pFocsueMtrl);
}

void CMouseScript::SetObjSize(const Vec3 & _vec)
{
	m_vObjSize = _vec;
}

bool CMouseScript::SetDragObj(CGameObject * _pDragObj)
{
	//if (NULL != m_pDragObj) return false;

	m_pDragObj = _pDragObj;

	return true;
}

void CMouseScript::start()
{
	////////////////
	// Dont Destory
	///////////////
	static bool bDont = false;
	if (bDont == true) return;
	CSceneMgr::GetInst()->DontDestroyOnLoad(GetGameObject());
	bDont = true;

	m_pScene = CSceneMgr::GetInst()->GetCurScene();

	// Mediator
	m_pMediator = CMediatorMgr::GetInst();
	m_pCollq_Mouse = CMessageColleaque::Create(m_pMediator, L"MouseObj", this);

	// 포커스 타일
	CPrefab* pFocuseTilePrefab = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"FocuseTile(Prefab)");
	m_pFocuseTileObj = Instantiate(pFocuseTilePrefab, Vec3(0.f, 0.f, 95.f));
	m_pTileMgrScript = CTileMgrScript::GetThis();
	if (NULL != m_pTileMgrScript)
	{
		m_pFocsueMtrl = m_pFocuseTileObj->MeshRender()->GetMaterial();
		Vec2 vScale = m_pTileMgrScript->GetSize();
		m_pFocuseTileObj->Transform()->SetLocal2DScale(vScale);
		CTexture* pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"FocuseTileTex");
		m_pFocsueMtrl->SetData(SHADER_PARAM::SP_TEX_0, &pTex);
		m_pFocuseTileObj->start();
	}
	m_pFocuseTileObj->SetActive(false);
}

int CMouseScript::update()
{
	m_pScene = CSceneMgr::GetInst()->GetCurScene();
	m_vMousePos = CKeyMgr::GetInst()->GetMousePos();
	RECT rt = {};
	GetWindowRect(CKeyMgr::GetInst()->GethWnd(), &rt);
	m_vMousePos = m_pScene->Get2DWorldPosFromWindowPos(m_vMousePos, Vec2((float)(rt.right - rt.left), (float)(rt.bottom - rt.top)));
	m_vMouseObjPos.x = m_vMousePos.x + m_vOffset.x;
	m_vMouseObjPos.y = m_vMousePos.y - m_vOffset.y;

	Transform()->SetLocalPos(Vec3(m_vMouseObjPos.x, m_vMouseObjPos.y, 1.f));
	Transform()->SetLocalScale(m_vObjSize);

	if (false == m_bColl)
	{
		if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN, KEY_STATE::STATE_TAB))
		{
			CMessage* pMsg = new CFindMessage(L"Astar", m_vMousePos);
			m_pCollq_Mouse->SendData(L"Player", pMsg);
		}

		//if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN, KEY_STATE::STATE_TAB))
		//{
		//	CMessage* pMsg = new CFindMessage(L"Ground", m_vMousePos);
		//	m_pCollq_Mouse->SendData(L"Player", pMsg);
		//}

		if (!Animator()->IsPlayAnimation(L"BasicMouse"))
			Animator()->PlayAnimation(L"BasicMouse");

		// 포커스 Tile
		Vec2 vTilePos{};
		m_pTileMgrScript = CTileMgrScript::GetThis();
		if (NULL != m_pTileMgrScript)
		{
			bool IsTile = m_pTileMgrScript->IsMoveToPos(m_vMouseObjPos, vTilePos);
			if (true == IsTile)
			{
				m_pFocuseTileObj->Transform()->SetLocal2DScale(m_pTileMgrScript->GetSize());
				m_pFocuseTileObj->Transform()->SetLocal2DPos(vTilePos);
				m_pFocuseTileObj->SetActive(true);
			}
			else
			{
				m_pFocuseTileObj->SetActive(false);
			}
		}
	}
	m_bColl = false;

	return RET_SUCCESS;
}

void CMouseScript::OnCollision(CCollider * _pOther)
{
	m_bColl = true;

	bool bType = false;
	int iType;

	if (false == bType)
	{
		iType = _pOther->GetGameObject()->GetTag().find(L"Portal");
		if (iType > -1)
		{
			if (!Animator()->IsPlayAnimation(L"DoorMouse"))
				Animator()->PlayAnimation(L"DoorMouse");
			bType = true;
		}
	}

	if (false == bType)
	{
		iType = _pOther->GetGameObject()->GetTag().find(L"Monster");
		if (iType > -1)
		{
			if (!Animator()->IsPlayAnimation(L"AttackMouse"))
				Animator()->PlayAnimation(L"AttackMouse");
			bType = true;
		}
	}

	if (false == bType)
	{
		iType = _pOther->GetGameObject()->GetTag().find(L"Inven_Slot");
		if (iType > -1)
		{
			if (!Animator()->IsPlayAnimation(L"PickUpMouse"))
				Animator()->PlayAnimation(L"PickUpMouse");
			bType = true;
		}
	}

	// 게임오브젝트 이름으로 전송 Collq 도 일치 시킬 것.
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN, KEY_STATE::STATE_TAB))
	{
		CGameObject* pObj = _pOther->GetGameObject();
		wstring strTag = pObj->GetTag();
		Vec2 vPos2D = pObj->Transform()->GetLocal2DPos();
		CMessage* pMsg = new CFindMessage(strTag, vPos2D, pObj);

		m_pCollq_Mouse->SendData(L"Player", pMsg);
	}
}

void CMouseScript::OnCollisionExit(CCollider * _pOther)
{
	m_bColl = false;
	if (!Animator()->IsPlayAnimation(L"BasicMouse"))
		Animator()->PlayAnimation(L"BasicMouse");

}
