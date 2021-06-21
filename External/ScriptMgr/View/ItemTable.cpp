#include "stdafx.h"
#include "ItemTable.h"
#include "DefineCode\DefineScript.h"

#include "..\External\ScriptCode\WeaponScript.h"
#include "..\External\ScriptCode\ArmorScript.h"
#include "..\External\ScriptCode\AccessoriesScript.h"
#include "..\External\ScriptCode\ETCItemScript.h"
#include "..\External\ScriptCode\ComsumptionItemScript.h"

// ��ų Table
#include "SkillTable.h"

CItemTable::CItemTable()
{
}


CItemTable::~CItemTable()
{
	Safe_Delete_Map(m_mapItemTable);
	Safe_Delete_List(m_listMtrl);
}

void CItemTable::InitItemTable()
{
	////////////////
	// Dont Destory
	///////////////
	static bool bDont = false;
	if (bDont == true) return;
	CSceneMgr::GetInst()->DontDestroyOnLoad(GetGameObject());
	bDont = true;

	CMaterial* pMtrl = CResMgr::GetInst()->FindMaterial(L"ItemMtrl");
	tStatus tStatus;
	CSkill* pSkill;

	//================
	// ��伮�ܰ� - ����
	CTexture* pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��伮�ܰ�Tex");
	int iIdex = 1;
	CItemScript* pItemScript = new CWeaponScript;
	((CWeaponScript*)pItemScript)->SetWeaponInfo(iIdex, L"�ٰŸ�����", ((UINT)ITEM_TYPE::EQUIP_RHAND_TYPE | (UINT)ITEM_TYPE::EQUIP_LHAND_TYPE), L"��伮�ܰ�", 100, 10, 1.f);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"��伮�ܰ�", pItemScript));
	m_listMtrl.push_back(pMtrl);
	//================
	// �Ӹ��� - �Ӹ�1
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�Ӹ���Tex");
	++iIdex;
	pItemScript = new CArmorScript;
	((CArmorScript*)pItemScript)->SetArmorInfo(iIdex, L"����1", ((UINT)ITEM_TYPE::EQUIP_HEAD1_TYPE), L"�Ӹ���", 5);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"�Ӹ���", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// ���ô޸��ư��� - ��Ÿ
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"���ô޸��ư���Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"��Ÿ", ((UINT)ITEM_TYPE::ETC_TYPE), L"���ô޸��ư���");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"���ô޸��ư���", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// ���� - ���� Ȱ
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"����Tex");
	++iIdex;
	pItemScript = new CWeaponScript;
	((CWeaponScript*)pItemScript)->SetWeaponInfo(iIdex, L"���Ÿ�����", ((UINT)ITEM_TYPE::EQUIP_RHAND_TYPE | (UINT)ITEM_TYPE::EQUIP_LHAND_TYPE), L"����", 600, 10, 1.f);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"����", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// �������� - �Һ� ����
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��������Tex");
	++iIdex;
	pItemScript = new CComsumptionItemScript;
	tStatus.SetStatus(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
	((CComsumptionItemScript*)pItemScript)->SetComsumptionInfo(iIdex, L"�Һ񹰾�", ((UINT)ITEM_TYPE::COMSUMPTION_TYPE), L"��������", tStatus, 30, 0);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	// ��ų�߰�
	pSkill = CSkillTable::GetThis()->FindSkill(L"Skill_SPRecovery");
	if (NULL != pSkill)
	{
		pItemScript->SetSkill(pSkill);
	}
	m_mapItemTable.insert(make_pair(L"��������", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// ��ö - ��Ÿ
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��öTex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"��Ÿ������", ((UINT)ITEM_TYPE::ETC_TYPE), L"��ö");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"��ö", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// ��öȭ�� - �Һ� ȭ��
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��öȭ��Tex");
	++iIdex;
	pItemScript = new CComsumptionItemScript;
	tStatus.SetStatus(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0);
	((CComsumptionItemScript*)pItemScript)->SetComsumptionInfo(iIdex, L"�Һ������", ((UINT)ITEM_TYPE::COMSUMPTION_TYPE), L"��öȭ��", tStatus, 1, 0);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"��öȭ��", pItemScript));
	m_listMtrl.push_back(pMtrl);


	//================
	// ��ȭŬ�� - �Ǽ����� ���� (��ų! �ڷ���Ʈ)
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��ȭŬ��Tex");
	++iIdex;
	pItemScript = new CAccessoriesScript;
	((CAccessoriesScript*)pItemScript)->SetAccInfo(iIdex, L"�Ǽ�����", ((UINT)ITEM_TYPE::EQUIP_ACC1_TYPE | (UINT)ITEM_TYPE::EQUIP_ACC2_TYPE), L"��ȭŬ��", 1,1);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	// ��ų�߰�
	pSkill = CSkillTable::GetThis()->FindSkill(L"Skill_Teleport");
	if (NULL != pSkill)
	{
		pItemScript->SetSkill(pSkill);
	}
	m_mapItemTable.insert(make_pair(L"��ȭŬ��", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// �ű� - ���� Ȱ
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�ű�Tex");
	++iIdex;
	pItemScript = new CWeaponScript;
	((CWeaponScript*)pItemScript)->SetWeaponInfo(iIdex, L"���Ÿ�����", ((UINT)ITEM_TYPE::EQUIP_LHAND_TYPE | (UINT)ITEM_TYPE::EQUIP_RHAND_TYPE), L"�ű�", 600.f, 10, 1);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"�ű�", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// ��� - �Һ� ���
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"���Tex");
	++iIdex;
	pItemScript = new CComsumptionItemScript;
	tStatus.SetStatus(0, 0, 0, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	((CComsumptionItemScript*)pItemScript)->SetComsumptionInfo(iIdex, L"�Һ������", ((UINT)ITEM_TYPE::COMSUMPTION_TYPE), L"���", tStatus, 0, 0);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"���", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// �������������� - ��Ÿ ��ȭ
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��������������Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"��ȭ������", ((UINT)ITEM_TYPE::ETC_TYPE), L"��������������");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"��������������", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// ��е�ī���� - ��Ÿ ��ȭ
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��е�ī����Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"��ȭ������", ((UINT)ITEM_TYPE::ETC_TYPE), L"��е�ī����");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"��е�ī����", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// ���߹ٴ� - ��Ÿ
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"���߹ٴ�Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"��ȭ������", ((UINT)ITEM_TYPE::ETC_TYPE), L"���߹ٴ�");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"���߹ٴ�", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// ��ȭ - ��Ÿ
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��ȭTex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"��Ÿ������", ((UINT)ITEM_TYPE::ETC_TYPE), L"��ȭ");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"��ȭ", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// �ɹ���  - �Ǽ����� ����
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�ɹ���Tex");
	++iIdex;
	pItemScript = new CAccessoriesScript;
	((CAccessoriesScript*)pItemScript)->SetAccInfo(iIdex, L"�Ǽ�����", ((UINT)ITEM_TYPE::EQUIP_ACC1_TYPE | (UINT)ITEM_TYPE::EQUIP_ACC2_TYPE), L"�ɹ���", 1, 1);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"�ɹ���", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// ���������Ѿ�ü  - ��Ÿ
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"���������Ѿ�üTex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"��Ÿ������", ((UINT)ITEM_TYPE::ETC_TYPE), L"���������Ѿ�ü");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"���������Ѿ�ü", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// �����ǳ���  - �Һ������
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�����ǳ���Tex");
	++iIdex;
	pItemScript = new CComsumptionItemScript;
	tStatus.SetStatus(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	((CComsumptionItemScript*)pItemScript)->SetComsumptionInfo(iIdex, L"�Һ������", ((UINT)ITEM_TYPE::COMSUMPTION_TYPE), L"�����ǳ���",tStatus, 0, 0);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"�����ǳ���", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// �������  - �Һ������ (��ų! hp ȸ��)
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�������Tex");
	++iIdex;
	pItemScript = new CComsumptionItemScript;
	tStatus.SetStatus(0, 0, 0, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	((CComsumptionItemScript*)pItemScript)->SetComsumptionInfo(iIdex, L"�Һ������", ((UINT)ITEM_TYPE::COMSUMPTION_TYPE), L"�������", tStatus, 0, 0);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	// ��ų�߰�
	pSkill = CSkillTable::GetThis()->FindSkill(L"Skill_HPRecovery");
	if (NULL != pSkill)
	{
		pItemScript->SetSkill(pSkill);
	}
	m_mapItemTable.insert(make_pair(L"�������", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// �������ǻ�  - ��Ÿ������
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�������ǻ�Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"��Ÿ������", ((UINT)ITEM_TYPE::ETC_TYPE), L"�������ǻ�");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"�������ǻ�", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// ��ƺ��罺����  - �� ������ (��ų! ����̵�)
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��ƺ��罺����Tex");
	++iIdex;
	pItemScript = new CArmorScript;
	((CArmorScript*)pItemScript)->SetArmorInfo(iIdex, L"��������", ((UINT)ITEM_TYPE::EQUIP_SHOES_TYPE), L"��ƺ��罺����", 10);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	// ��ų�߰�
	pSkill = CSkillTable::GetThis()->FindSkill(L"Skill_Tornado");
	if (NULL != pSkill)
	{
		pItemScript->SetSkill(pSkill);
	}
	m_mapItemTable.insert(make_pair(L"��ƺ��罺����", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// ��ƺ��罺�Ƹ�  - �� ������ (��ų! ���׿�)
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��ƺ��罺�Ƹ�Tex");
	++iIdex;
	pItemScript = new CArmorScript;
	((CArmorScript*)pItemScript)->SetArmorInfo(iIdex, L"��������", ((UINT)ITEM_TYPE::EQUIP_BODY_TYPE), L"��ƺ��罺�Ƹ�", 15);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	// ��ų�߰�
	pSkill = CSkillTable::GetThis()->FindSkill(L"Skill_Meteor");
	if (NULL != pSkill)
	{
		pItemScript->SetSkill(pSkill);
	}
	m_mapItemTable.insert(make_pair(L"��ƺ��罺�Ƹ�", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// ����  - �� ������
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"����Tex");
	++iIdex;
	pItemScript = new CArmorScript;
	((CArmorScript*)pItemScript)->SetArmorInfo(iIdex, L"��������", ((UINT)ITEM_TYPE::EQUIP_ROBE_TYPE), L"����", 5);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"����", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// ���÷�  - �� ������
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"���÷�Tex");
	++iIdex;
	pItemScript = new CArmorScript;
	((CArmorScript*)pItemScript)->SetArmorInfo(iIdex, L"��������", ((UINT)ITEM_TYPE::EQUIP_ROBE_TYPE), L"���÷�", 3);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"���÷�", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// �̽�ƽ������  - ��Ÿ ������
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�̽�ƽ������Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"��Ÿ������", ((UINT)ITEM_TYPE::ETC_TYPE), L"�̽�ƽ������");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"�̽�ƽ������", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// ��������  - ��Ÿ ������
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��������Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"��Ÿ������", ((UINT)ITEM_TYPE::ETC_TYPE), L"��������");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"��������", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// �̸�����ī��  - ��Ÿ ������
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�̸�����ī��Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"��Ÿ������", ((UINT)ITEM_TYPE::ETC_TYPE), L"�̸�����ī��");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"�̸�����ī��", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// �̼���������  - �Һ� ������
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�̼���������Tex");
	++iIdex;
	pItemScript = new CComsumptionItemScript;
	tStatus.SetStatus(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 0);
	((CComsumptionItemScript*)pItemScript)->SetComsumptionInfo(iIdex, L"�Һ������", ((UINT)ITEM_TYPE::COMSUMPTION_TYPE), L"�̼���������", tStatus, 30, 0);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"�̼���������", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// ������Ű  - �Һ� ������
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"������ŰTex");
	++iIdex;
	pItemScript = new CComsumptionItemScript;
	tStatus.SetStatus(0, 50, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 100, 0);
	((CComsumptionItemScript*)pItemScript)->SetComsumptionInfo(iIdex, L"�Һ������", ((UINT)ITEM_TYPE::COMSUMPTION_TYPE), L"������Ű", tStatus, 30, 0);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"������Ű", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// �Ͼ�����  - �Һ� ������
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�Ͼ�����Tex");
	++iIdex;
	pItemScript = new CComsumptionItemScript;
	tStatus.SetStatus(0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	((CComsumptionItemScript*)pItemScript)->SetComsumptionInfo(iIdex, L"�Һ������", ((UINT)ITEM_TYPE::COMSUMPTION_TYPE), L"�Ͼ�����", tStatus, 0, 0);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"�Ͼ�����", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// ��ȸŻ  - �� ������
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��ȸŻTex");
	++iIdex;
	pItemScript = new CArmorScript;
	((CArmorScript*)pItemScript)->SetArmorInfo(iIdex, L"����", ((UINT)ITEM_TYPE::EQUIP_HEAD2_TYPE), L"��ȸŻ", 5);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"��ȸŻ", pItemScript));
	m_listMtrl.push_back(pMtrl);


	//================
	// �ĵ�  - �� ������
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�ĵ�Tex");
	++iIdex;
	pItemScript = new CArmorScript;
	((CArmorScript*)pItemScript)->SetArmorInfo(iIdex, L"����1", ((UINT)ITEM_TYPE::EQUIP_HEAD1_TYPE), L"�ĵ�", 3);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"�ĵ�", pItemScript));
	m_listMtrl.push_back(pMtrl);

}

CItemScript * CItemTable::FindItem(const wstring & _strName)
{
	map<wstring, CItemScript*>::iterator iter = m_mapItemTable.find(_strName);
	if (iter == m_mapItemTable.end())
		return NULL;
	return iter->second;
}

CItemScript* CItemTable::CreateItem(const wstring & _strName)
{
	CItemScript* pItemScript = FindItem(_strName);
	if (NULL == pItemScript) return NULL;

	pItemScript = pItemScript->Clone();

	CGameObject* pItemObj = new CGameObject;
	pItemObj->SetTag(_strName);
	pItemObj->AddComponent<CTransform>(new CTransform);
	pItemObj->AddComponent<CMeshRender>(new CMeshRender);
	pItemObj->AddComponent<CScript>(pItemScript);

	pItemObj->MeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pItemObj->MeshRender()->SetMaterial(pItemScript->GetItemMtrl());
	pItemObj->Transform()->SetLocalScale(Vec3(50.f, 50.f, 1.f));

	CScene* pScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pScene->FindLayer(L"Default");
	pLayer->AddGameObject(pItemObj);

	return pItemScript;
}

int CItemTable::update()
{
	return RET_SUCCESS;
}
