#include "stdafx.h"
#include "ShortcutSlot.h"

#include "DefineCode\ItemScript.h"
#include "..\External\ScriptMgr\View\MouseScript.h"

#include "DeleteEndAnim.h"

CShortcutSlot::CShortcutSlot()
	: m_pShortcutWindow(NULL)
	, m_iIndex(0)
	, m_vPos{}
	, m_vScale{}
	, m_bColl(false)
	, m_pItemScript(NULL)
	, m_pTempObj(NULL)
{
}


CShortcutSlot::~CShortcutSlot()
{
}

void CShortcutSlot::start()
{
	m_pEffectPrefab = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Effect_Blood(Prefab)");
}

int CShortcutSlot::update()
{
	if (m_bColl == true)
	{
		CGameObject* pMouseDragObj = CMouseScript::GetThis()->GetDragObj();
		if (pMouseDragObj != NULL)
		{
			if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN, KEY_STATE::STATE_TAB))
			{
				// 2���� �б�(�����۽�ũ��Ʈ / ��ų��ũ��Ʈ)
				CItemScript* pItemScript;
				pItemScript = pMouseDragObj->Script<CItemScript>();
				if (pItemScript != NULL)
				{
					bool bPush = PushItem(pItemScript);
					if (bPush == true)
					{
						// ... Temp�� �޾ƿԱ⶧���� 
						// CMouseScript::GetThis()->SetDragObj(NULL);  ����
					}
				}
			}
		}
	}


	return RET_SUCCESS;
}

bool CShortcutSlot::IsEmpty()
{
	bool bEmpty = (NULL == m_pItemScript) ? true : false;

	return bEmpty;
}

/*
�Լ���  : Push(CScript * _pScript)
�뵵    : ������(��ų)�� �ְԵǸ� ������ ��ũ��Ʈ�� ���͸���� MESH�� �����ͼ� �״�� ������ �ְ� ��ũ��Ʈ�� �����ʴ´�.
			//�� �ش� ��ũ��Ʈ�� �׼��� �����ϱ� ���� ������ �Ǹ� �� ��ũ��Ʈ�� ACTION ���ɿ��θ� ��� ������Ʈ���ִ� �뵵�θ� ���
*/
bool CShortcutSlot::PushItem(CItemScript * _pItemScript)
{
	vector<CShortcutSlot*>::iterator iter = m_pShortcutWindow->GetSlots().begin();
	const auto vecNull = m_pShortcutWindow->GetSlots().end();
	for (; iter != vecNull; ++iter)
	{
		if (_pItemScript != NULL && (*iter)->m_pItemScript == _pItemScript)
		{
			CDestroyMgr::GetInst()->AddGameObject((*iter)->m_pTempObj);
			(*iter)->m_pTempObj = NULL;
			(*iter)->m_pItemScript = NULL;
		}
	}

	CGameObject* pScriptObj = _pItemScript->GetGameObject();
	// mtrl �� mesh�� �и� �ִٰ� ����.
	CMesh*		 pMesh = pScriptObj->MeshRender()->GetMesh();
	CMaterial*   pMtrl = pScriptObj->MeshRender()->GetSharedMaterial();
	wstring strTempTag = wstring(pScriptObj->GetTag() + L"(shortcut)" + to_wstring(m_iIndex));

	m_pTempObj = new CGameObject;
	m_pTempObj->SetTag(strTempTag);
	m_pTempObj->AddComponent<CTransform>(new CTransform);
	m_pTempObj->AddComponent<CMeshRender>(new CMeshRender);

	m_pTempObj->MeshRender()->SetMesh(pMesh);
	m_pTempObj->MeshRender()->SetMaterial(pMtrl);

	m_pTempObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
	m_pTempObj->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));

	CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Default")->AddGameObject(m_pTempObj);
	GetGameObject()->AddChildObj(m_pTempObj);

	m_pItemScript = _pItemScript;

	return true;
}

CGameObject * CShortcutSlot::Create()
{
	CPrefab* pShortcutObj = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Shortcut_Slot(Prefab)");

	CGameObject* pClone = Instantiate(pShortcutObj, m_vPos);
	pClone->AddComponent<CScript>(this);

	return pClone;
}

bool CShortcutSlot::Action(CScript* _pScript)
{
	if (NULL == m_pItemScript) return false;

	m_pItemScript->Action(_pScript);
	CreateEffectToSlot();

	return true;
}

void CShortcutSlot::CreateEffectToSlot()
{
	CGameObject* pEffectClone = Instantiate(m_pEffectPrefab, Vec3(0.f, 0.f, 0.f));
	CDeleteEndAnim* pDeleteEndAnim = new CDeleteEndAnim;
	pDeleteEndAnim->SetCount(0, 1);
	pEffectClone->AddComponent<CScript>(pDeleteEndAnim);
	GetGameObject()->AddChildObj(pEffectClone);
	pEffectClone->awake();
	pEffectClone->start();
}

void CShortcutSlot::SetLocalPos(const Vec3 & _vPos)
{
	m_vPos = _vPos;
}

void CShortcutSlot::OnCollisionEnter(CCollider * _pOther)
{
	int iFindKey = _pOther->GetGameObject()->GetTag().find(L"Mouse");
	if (iFindKey > -1)
	{
		m_bColl = true;
	}
}

void CShortcutSlot::OnCollision(CCollider * _pOther)
{
	int iFindKey = _pOther->GetGameObject()->GetTag().find(L"Mouse");
	if (iFindKey > -1)
	{
		m_bColl = true;
	}
}

void CShortcutSlot::OnCollisionExit(CCollider * _pOther)
{
	m_bColl = false;
}
