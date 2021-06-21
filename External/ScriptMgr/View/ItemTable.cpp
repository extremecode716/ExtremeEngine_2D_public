#include "stdafx.h"
#include "ItemTable.h"
#include "DefineCode\DefineScript.h"

#include "..\External\ScriptCode\WeaponScript.h"
#include "..\External\ScriptCode\ArmorScript.h"
#include "..\External\ScriptCode\AccessoriesScript.h"
#include "..\External\ScriptCode\ETCItemScript.h"
#include "..\External\ScriptCode\ComsumptionItemScript.h"

// 스킬 Table
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
	// 흑요석단검 - 무기
	CTexture* pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"흑요석단검Tex");
	int iIdex = 1;
	CItemScript* pItemScript = new CWeaponScript;
	((CWeaponScript*)pItemScript)->SetWeaponInfo(iIdex, L"근거리무기", ((UINT)ITEM_TYPE::EQUIP_RHAND_TYPE | (UINT)ITEM_TYPE::EQUIP_LHAND_TYPE), L"흑요석단검", 100, 10, 1.f);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"흑요석단검", pItemScript));
	m_listMtrl.push_back(pMtrl);
	//================
	// 머리빗 - 머리1
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"머리빗Tex");
	++iIdex;
	pItemScript = new CArmorScript;
	((CArmorScript*)pItemScript)->SetArmorInfo(iIdex, L"투구1", ((UINT)ITEM_TYPE::EQUIP_HEAD1_TYPE), L"머리빗", 5);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"머리빗", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 가시달린아가미 - 기타
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"가시달린아가미Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"기타", ((UINT)ITEM_TYPE::ETC_TYPE), L"가시달린아가미");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"가시달린아가미", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 각궁 - 무기 활
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"각궁Tex");
	++iIdex;
	pItemScript = new CWeaponScript;
	((CWeaponScript*)pItemScript)->SetWeaponInfo(iIdex, L"원거리무기", ((UINT)ITEM_TYPE::EQUIP_RHAND_TYPE | (UINT)ITEM_TYPE::EQUIP_LHAND_TYPE), L"각궁", 600, 10, 1.f);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"각궁", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 각성포션 - 소비 물약
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"각성포션Tex");
	++iIdex;
	pItemScript = new CComsumptionItemScript;
	tStatus.SetStatus(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
	((CComsumptionItemScript*)pItemScript)->SetComsumptionInfo(iIdex, L"소비물약", ((UINT)ITEM_TYPE::COMSUMPTION_TYPE), L"각성포션", tStatus, 30, 0);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	// 스킬추가
	pSkill = CSkillTable::GetThis()->FindSkill(L"Skill_SPRecovery");
	if (NULL != pSkill)
	{
		pItemScript->SetSkill(pSkill);
	}
	m_mapItemTable.insert(make_pair(L"각성포션", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 강철 - 기타
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"강철Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"기타아이템", ((UINT)ITEM_TYPE::ETC_TYPE), L"강철");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"강철", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 강철화살 - 소비 화살
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"강철화살Tex");
	++iIdex;
	pItemScript = new CComsumptionItemScript;
	tStatus.SetStatus(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0);
	((CComsumptionItemScript*)pItemScript)->SetComsumptionInfo(iIdex, L"소비아이템", ((UINT)ITEM_TYPE::COMSUMPTION_TYPE), L"강철화살", tStatus, 1, 0);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"강철화살", pItemScript));
	m_listMtrl.push_back(pMtrl);


	//================
	// 강화클립 - 악세서리 반지 (스킬! 텔레포트)
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"강화클립Tex");
	++iIdex;
	pItemScript = new CAccessoriesScript;
	((CAccessoriesScript*)pItemScript)->SetAccInfo(iIdex, L"악세서리", ((UINT)ITEM_TYPE::EQUIP_ACC1_TYPE | (UINT)ITEM_TYPE::EQUIP_ACC2_TYPE), L"강화클립", 1,1);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	// 스킬추가
	pSkill = CSkillTable::GetThis()->FindSkill(L"Skill_Teleport");
	if (NULL != pSkill)
	{
		pItemScript->SetSkill(pSkill);
	}
	m_mapItemTable.insert(make_pair(L"강화클립", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 거궁 - 무기 활
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"거궁Tex");
	++iIdex;
	pItemScript = new CWeaponScript;
	((CWeaponScript*)pItemScript)->SetWeaponInfo(iIdex, L"원거리무기", ((UINT)ITEM_TYPE::EQUIP_LHAND_TYPE | (UINT)ITEM_TYPE::EQUIP_RHAND_TYPE), L"거궁", 600.f, 10, 1);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"거궁", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 고기 - 소비 고기
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"고기Tex");
	++iIdex;
	pItemScript = new CComsumptionItemScript;
	tStatus.SetStatus(0, 0, 0, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	((CComsumptionItemScript*)pItemScript)->SetComsumptionInfo(iIdex, L"소비아이템", ((UINT)ITEM_TYPE::COMSUMPTION_TYPE), L"고기", tStatus, 0, 0);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"고기", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 고농축오리데오콘 - 기타 강화
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"고농축오리데오콘Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"강화아이템", ((UINT)ITEM_TYPE::ETC_TYPE), L"고농축오리데오콘");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"고농축오리데오콘", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 고밀도카르늄 - 기타 강화
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"고밀도카르늄Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"강화아이템", ((UINT)ITEM_TYPE::ETC_TYPE), L"고밀도카르늄");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"고밀도카르늄", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 곰발바닥 - 기타
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"곰발바닥Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"강화아이템", ((UINT)ITEM_TYPE::ETC_TYPE), L"곰발바닥");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"곰발바닥", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 금화 - 기타
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"금화Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"기타아이템", ((UINT)ITEM_TYPE::ETC_TYPE), L"금화");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"금화", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 꽃반지  - 악세서리 반지
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"꽃반지Tex");
	++iIdex;
	pItemScript = new CAccessoriesScript;
	((CAccessoriesScript*)pItemScript)->SetAccInfo(iIdex, L"악세서리", ((UINT)ITEM_TYPE::EQUIP_ACC1_TYPE | (UINT)ITEM_TYPE::EQUIP_ACC2_TYPE), L"꽃반지", 1, 1);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"꽃반지", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 끈적끈적한액체  - 기타
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"끈적끈적한액체Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"기타아이템", ((UINT)ITEM_TYPE::ETC_TYPE), L"끈적끈적한액체");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"끈적끈적한액체", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 나비의날개  - 소비아이템
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"나비의날개Tex");
	++iIdex;
	pItemScript = new CComsumptionItemScript;
	tStatus.SetStatus(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	((CComsumptionItemScript*)pItemScript)->SetComsumptionInfo(iIdex, L"소비아이템", ((UINT)ITEM_TYPE::COMSUMPTION_TYPE), L"나비의날개",tStatus, 0, 0);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"나비의날개", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 노랑포션  - 소비아이템 (스킬! hp 회복)
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"노랑포션Tex");
	++iIdex;
	pItemScript = new CComsumptionItemScript;
	tStatus.SetStatus(0, 0, 0, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	((CComsumptionItemScript*)pItemScript)->SetComsumptionInfo(iIdex, L"소비아이템", ((UINT)ITEM_TYPE::COMSUMPTION_TYPE), L"노랑포션", tStatus, 0, 0);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	// 스킬추가
	pSkill = CSkillTable::GetThis()->FindSkill(L"Skill_HPRecovery");
	if (NULL != pSkill)
	{
		pItemScript->SetSkill(pSkill);
	}
	m_mapItemTable.insert(make_pair(L"노랑포션", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 도깨비의뿔  - 기타아이템
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"도깨비의뿔Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"기타아이템", ((UINT)ITEM_TYPE::ETC_TYPE), L"도깨비의뿔");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"도깨비의뿔", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 디아볼루스부츠  - 방어구 아이템 (스킬! 토네이도)
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"디아볼루스부츠Tex");
	++iIdex;
	pItemScript = new CArmorScript;
	((CArmorScript*)pItemScript)->SetArmorInfo(iIdex, L"방어구아이템", ((UINT)ITEM_TYPE::EQUIP_SHOES_TYPE), L"디아볼루스부츠", 10);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	// 스킬추가
	pSkill = CSkillTable::GetThis()->FindSkill(L"Skill_Tornado");
	if (NULL != pSkill)
	{
		pItemScript->SetSkill(pSkill);
	}
	m_mapItemTable.insert(make_pair(L"디아볼루스부츠", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 디아볼루스아머  - 방어구 아이템 (스킬! 메테오)
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"디아볼루스아머Tex");
	++iIdex;
	pItemScript = new CArmorScript;
	((CArmorScript*)pItemScript)->SetArmorInfo(iIdex, L"방어구아이템", ((UINT)ITEM_TYPE::EQUIP_BODY_TYPE), L"디아볼루스아머", 15);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	// 스킬추가
	pSkill = CSkillTable::GetThis()->FindSkill(L"Skill_Meteor");
	if (NULL != pSkill)
	{
		pItemScript->SetSkill(pSkill);
	}
	m_mapItemTable.insert(make_pair(L"디아볼루스아머", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 망토  - 방어구 아이템
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"망토Tex");
	++iIdex;
	pItemScript = new CArmorScript;
	((CArmorScript*)pItemScript)->SetArmorInfo(iIdex, L"방어구아이템", ((UINT)ITEM_TYPE::EQUIP_ROBE_TYPE), L"망토", 5);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"망토", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 머플러  - 방어구 아이템
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"머플러Tex");
	++iIdex;
	pItemScript = new CArmorScript;
	((CArmorScript*)pItemScript)->SetArmorInfo(iIdex, L"방어구아이템", ((UINT)ITEM_TYPE::EQUIP_ROBE_TYPE), L"머플러", 3);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"머플러", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 미스틱프로즌  - 기타 아이템
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"미스틱프로즌Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"기타아이템", ((UINT)ITEM_TYPE::ETC_TYPE), L"미스틱프로즌");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"미스틱프로즌", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 보물상자  - 기타 아이템
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"보물상자Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"기타아이템", ((UINT)ITEM_TYPE::ETC_TYPE), L"보물상자");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"보물상자", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 이름없는카드  - 기타 아이템
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"이름없는카드Tex");
	++iIdex;
	pItemScript = new CETCItemScript;
	((CETCItemScript*)pItemScript)->SetETCInfo(iIdex, L"기타아이템", ((UINT)ITEM_TYPE::ETC_TYPE), L"이름없는카드");
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"이름없는카드", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 이속증가포션  - 소비 아이템
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"이속증가포션Tex");
	++iIdex;
	pItemScript = new CComsumptionItemScript;
	tStatus.SetStatus(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 0);
	((CComsumptionItemScript*)pItemScript)->SetComsumptionInfo(iIdex, L"소비아이템", ((UINT)ITEM_TYPE::COMSUMPTION_TYPE), L"이속증가포션", tStatus, 30, 0);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"이속증가포션", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 포춘쿠키  - 소비 아이템
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"포춘쿠키Tex");
	++iIdex;
	pItemScript = new CComsumptionItemScript;
	tStatus.SetStatus(0, 50, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 100, 0);
	((CComsumptionItemScript*)pItemScript)->SetComsumptionInfo(iIdex, L"소비아이템", ((UINT)ITEM_TYPE::COMSUMPTION_TYPE), L"포춘쿠키", tStatus, 30, 0);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"포춘쿠키", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 하얀포션  - 소비 아이템
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"하얀포션Tex");
	++iIdex;
	pItemScript = new CComsumptionItemScript;
	tStatus.SetStatus(0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	((CComsumptionItemScript*)pItemScript)->SetComsumptionInfo(iIdex, L"소비아이템", ((UINT)ITEM_TYPE::COMSUMPTION_TYPE), L"하얀포션", tStatus, 0, 0);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"하얀포션", pItemScript));
	m_listMtrl.push_back(pMtrl);

	//================
	// 하회탈  - 방어구 아이템
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"하회탈Tex");
	++iIdex;
	pItemScript = new CArmorScript;
	((CArmorScript*)pItemScript)->SetArmorInfo(iIdex, L"가면", ((UINT)ITEM_TYPE::EQUIP_HEAD2_TYPE), L"하회탈", 5);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"하회탈", pItemScript));
	m_listMtrl.push_back(pMtrl);


	//================
	// 후드  - 방어구 아이템
	pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"후드Tex");
	++iIdex;
	pItemScript = new CArmorScript;
	((CArmorScript*)pItemScript)->SetArmorInfo(iIdex, L"투구1", ((UINT)ITEM_TYPE::EQUIP_HEAD1_TYPE), L"후드", 3);
	pMtrl = pMtrl->Clone();
	pItemScript->SetItemMtrl(pMtrl);
	pItemScript->SetItemTex(pTexture);
	m_mapItemTable.insert(make_pair(L"후드", pItemScript));
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
