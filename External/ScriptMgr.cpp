#include "stdafx.h"
#include "ScriptMgr.h"

#include "ScriptCode\AccessoriesScript.h"
#include "ScriptCode\ArmorScript.h"
#include "ScriptCode\BasicBulletScript.h"
#include "ScriptCode\CameraScript.h"
#include "ScriptCode\ComsumptionItemScript.h"
#include "ScriptCode\Critical.h"
#include "ScriptCode\Damage.h"
#include "ScriptCode\DeleteEndAnim.h"
#include "ScriptCode\DontDestoryAddScript.h"
#include "ScriptCode\EquipmentWindow.h"
#include "ScriptCode\EquipSlot.h"
#include "ScriptCode\ETCItemScript.h"
#include "ScriptCode\GaugeScript.h"
#include "ScriptCode\Inventory.h"
#include "ScriptCode\MainWindowScript.h"
#include "ScriptCode\MeteorAttackScript.h"
#include "ScriptCode\MeteorScript.h"
#include "ScriptCode\MgrScript.h"
#include "ScriptCode\MissileBulletScript.h"
#include "ScriptCode\MonsterScript_Baphomet.h"
#include "ScriptCode\MonsterScript_BaphometJR.h"
#include "ScriptCode\MonsterScript_Creamy.h"
#include "ScriptCode\MonsterScript_Deviling.h"
#include "ScriptCode\MonsterScript_GoldPoring.h"
#include "ScriptCode\MonsterScript_Poring.h"
#include "ScriptCode\MonsterScript_Wolf.h"
#include "ScriptCode\MonsterScript_WraithDead.h"
#include "ScriptCode\MoveToMouseScript.h"
#include "ScriptCode\ParabolaBulletScript.h"
#include "ScriptCode\PlayerScript.h"
#include "ScriptCode\PortalScript.h"
#include "ScriptCode\RespawnScript.h"
#include "ScriptCode\RevolveBulletScript.h"
#include "ScriptCode\RevolveItemScript.h"
#include "ScriptCode\Scene_battleground1.h"
#include "ScriptCode\Scene_battleground2.h"
#include "ScriptCode\Scene_battleground3.h"
#include "ScriptCode\Scene_prontera.h"
#include "ScriptCode\ShortcutSlot.h"
#include "ScriptCode\ShortcutWindow.h"
#include "ScriptCode\Slot.h"
#include "ScriptCode\TornadoScript.h"
#include "ScriptCode\UIMgr.h"
#include "ScriptCode\WaterScript.h"
#include "ScriptCode\WeaponScript.h"
#include "ScriptMgr\View\AstarMgr.h"
#include "ScriptMgr\View\ItemTable.h"
#include "ScriptMgr\View\MediatorMgr.h"
#include "ScriptMgr\View\MonsterTable.h"
#include "ScriptMgr\View\MouseScript.h"
#include "ScriptMgr\View\PoolingMgr.h"
#include "ScriptMgr\View\PortalTable.h"
#include "ScriptMgr\View\SceneTable.h"
#include "ScriptMgr\View\SkillTable.h"
#include "ScriptMgr\View\TileMgrScript.h"

void CScriptMgr::GetScriptInfo(vector<tScriptInfo>& _vec)
{
	_vec.push_back(tScriptInfo{ L"AccessoriesScript", typeid(CAccessoriesScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"ArmorScript", typeid(CArmorScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"BasicBulletScript", typeid(CBasicBulletScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"CameraScript", typeid(CCameraScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"ComsumptionItemScript", typeid(CComsumptionItemScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"Critical", typeid(CCritical).hash_code() });
	_vec.push_back(tScriptInfo{ L"Damage", typeid(CDamage).hash_code() });
	_vec.push_back(tScriptInfo{ L"DeleteEndAnim", typeid(CDeleteEndAnim).hash_code() });
	_vec.push_back(tScriptInfo{ L"DontDestoryAddScript", typeid(CDontDestoryAddScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"EquipmentWindow", typeid(CEquipmentWindow).hash_code() });
	_vec.push_back(tScriptInfo{ L"EquipSlot", typeid(CEquipSlot).hash_code() });
	_vec.push_back(tScriptInfo{ L"ETCItemScript", typeid(CETCItemScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"GaugeScript", typeid(CGaugeScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"Inventory", typeid(CInventory).hash_code() });
	_vec.push_back(tScriptInfo{ L"MainWindowScript", typeid(CMainWindowScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"MeteorAttackScript", typeid(CMeteorAttackScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"MeteorScript", typeid(CMeteorScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"MgrScript", typeid(CMgrScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"MissileBulletScript", typeid(CMissileBulletScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"MonsterScript_Baphomet", typeid(CMonsterScript_Baphomet).hash_code() });
	_vec.push_back(tScriptInfo{ L"MonsterScript_BaphometJR", typeid(CMonsterScript_BaphometJR).hash_code() });
	_vec.push_back(tScriptInfo{ L"MonsterScript_Creamy", typeid(CMonsterScript_Creamy).hash_code() });
	_vec.push_back(tScriptInfo{ L"MonsterScript_Deviling", typeid(CMonsterScript_Deviling).hash_code() });
	_vec.push_back(tScriptInfo{ L"MonsterScript_GoldPoring", typeid(CMonsterScript_GoldPoring).hash_code() });
	_vec.push_back(tScriptInfo{ L"MonsterScript_Poring", typeid(CMonsterScript_Poring).hash_code() });
	_vec.push_back(tScriptInfo{ L"MonsterScript_Wolf", typeid(CMonsterScript_Wolf).hash_code() });
	_vec.push_back(tScriptInfo{ L"MonsterScript_WraithDead", typeid(CMonsterScript_WraithDead).hash_code() });
	_vec.push_back(tScriptInfo{ L"MoveToMouseScript", typeid(CMoveToMouseScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"ParabolaBulletScript", typeid(CParabolaBulletScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"PlayerScript", typeid(CPlayerScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"PortalScript", typeid(CPortalScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"RespawnScript", typeid(CRespawnScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"RevolveBulletScript", typeid(CRevolveBulletScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"RevolveItemScript", typeid(CRevolveItemScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"Scene_battleground1", typeid(CScene_battleground1).hash_code() });
	_vec.push_back(tScriptInfo{ L"Scene_battleground2", typeid(CScene_battleground2).hash_code() });
	_vec.push_back(tScriptInfo{ L"Scene_battleground3", typeid(CScene_battleground3).hash_code() });
	_vec.push_back(tScriptInfo{ L"Scene_prontera", typeid(CScene_prontera).hash_code() });
	_vec.push_back(tScriptInfo{ L"ShortcutSlot", typeid(CShortcutSlot).hash_code() });
	_vec.push_back(tScriptInfo{ L"ShortcutWindow", typeid(CShortcutWindow).hash_code() });
	_vec.push_back(tScriptInfo{ L"Slot", typeid(CSlot).hash_code() });
	_vec.push_back(tScriptInfo{ L"TornadoScript", typeid(CTornadoScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"UIMgr", typeid(CUIMgr).hash_code() });
	_vec.push_back(tScriptInfo{ L"WaterScript", typeid(CWaterScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"WeaponScript", typeid(CWeaponScript).hash_code() });
}

CScript * CScriptMgr::GetScript(DWORD _dwTypeId)
{
	if (typeid(CAccessoriesScript).hash_code() == _dwTypeId)
		return new CAccessoriesScript;
	if (typeid(CArmorScript).hash_code() == _dwTypeId)
		return new CArmorScript;
	if (typeid(CBasicBulletScript).hash_code() == _dwTypeId)
		return new CBasicBulletScript;
	if (typeid(CCameraScript).hash_code() == _dwTypeId)
		return new CCameraScript;
	if (typeid(CComsumptionItemScript).hash_code() == _dwTypeId)
		return new CComsumptionItemScript;
	if (typeid(CCritical).hash_code() == _dwTypeId)
		return new CCritical;
	if (typeid(CDamage).hash_code() == _dwTypeId)
		return new CDamage;
	if (typeid(CDeleteEndAnim).hash_code() == _dwTypeId)
		return new CDeleteEndAnim;
	if (typeid(CDontDestoryAddScript).hash_code() == _dwTypeId)
		return new CDontDestoryAddScript;
	if (typeid(CEquipmentWindow).hash_code() == _dwTypeId)
		return new CEquipmentWindow;
	if (typeid(CEquipSlot).hash_code() == _dwTypeId)
		return new CEquipSlot;
	if (typeid(CETCItemScript).hash_code() == _dwTypeId)
		return new CETCItemScript;
	if (typeid(CGaugeScript).hash_code() == _dwTypeId)
		return new CGaugeScript;
	if (typeid(CInventory).hash_code() == _dwTypeId)
		return new CInventory;
	if (typeid(CMainWindowScript).hash_code() == _dwTypeId)
		return new CMainWindowScript;
	if (typeid(CMeteorAttackScript).hash_code() == _dwTypeId)
		return new CMeteorAttackScript;
	if (typeid(CMeteorScript).hash_code() == _dwTypeId)
		return new CMeteorScript;
	if (typeid(CMgrScript).hash_code() == _dwTypeId)
		return new CMgrScript;
	if (typeid(CMissileBulletScript).hash_code() == _dwTypeId)
		return new CMissileBulletScript;
	if (typeid(CMonsterScript_Baphomet).hash_code() == _dwTypeId)
		return new CMonsterScript_Baphomet;
	if (typeid(CMonsterScript_BaphometJR).hash_code() == _dwTypeId)
		return new CMonsterScript_BaphometJR;
	if (typeid(CMonsterScript_Creamy).hash_code() == _dwTypeId)
		return new CMonsterScript_Creamy;
	if (typeid(CMonsterScript_Deviling).hash_code() == _dwTypeId)
		return new CMonsterScript_Deviling;
	if (typeid(CMonsterScript_GoldPoring).hash_code() == _dwTypeId)
		return new CMonsterScript_GoldPoring;
	if (typeid(CMonsterScript_Poring).hash_code() == _dwTypeId)
		return new CMonsterScript_Poring;
	if (typeid(CMonsterScript_Wolf).hash_code() == _dwTypeId)
		return new CMonsterScript_Wolf;
	if (typeid(CMonsterScript_WraithDead).hash_code() == _dwTypeId)
		return new CMonsterScript_WraithDead;
	if (typeid(CMoveToMouseScript).hash_code() == _dwTypeId)
		return new CMoveToMouseScript;
	if (typeid(CParabolaBulletScript).hash_code() == _dwTypeId)
		return new CParabolaBulletScript;
	if (typeid(CPlayerScript).hash_code() == _dwTypeId)
		return new CPlayerScript;
	if (typeid(CPortalScript).hash_code() == _dwTypeId)
		return new CPortalScript;
	if (typeid(CRespawnScript).hash_code() == _dwTypeId)
		return new CRespawnScript;
	if (typeid(CRevolveBulletScript).hash_code() == _dwTypeId)
		return new CRevolveBulletScript;
	if (typeid(CRevolveItemScript).hash_code() == _dwTypeId)
		return new CRevolveItemScript;
	if (typeid(CScene_battleground1).hash_code() == _dwTypeId)
		return new CScene_battleground1;
	if (typeid(CScene_battleground2).hash_code() == _dwTypeId)
		return new CScene_battleground2;
	if (typeid(CScene_battleground3).hash_code() == _dwTypeId)
		return new CScene_battleground3;
	if (typeid(CScene_prontera).hash_code() == _dwTypeId)
		return new CScene_prontera;
	if (typeid(CShortcutSlot).hash_code() == _dwTypeId)
		return new CShortcutSlot;
	if (typeid(CShortcutWindow).hash_code() == _dwTypeId)
		return new CShortcutWindow;
	if (typeid(CSlot).hash_code() == _dwTypeId)
		return new CSlot;
	if (typeid(CTornadoScript).hash_code() == _dwTypeId)
		return new CTornadoScript;
	if (typeid(CUIMgr).hash_code() == _dwTypeId)
		return new CUIMgr;
	if (typeid(CWaterScript).hash_code() == _dwTypeId)
		return new CWaterScript;
	if (typeid(CWeaponScript).hash_code() == _dwTypeId)
		return new CWeaponScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"AccessoriesScript" == _strScriptName)
		return new CAccessoriesScript;
	if (L"ArmorScript" == _strScriptName)
		return new CArmorScript;
	if (L"BasicBulletScript" == _strScriptName)
		return new CBasicBulletScript;
	if (L"CameraScript" == _strScriptName)
		return new CCameraScript;
	if (L"ComsumptionItemScript" == _strScriptName)
		return new CComsumptionItemScript;
	if (L"Critical" == _strScriptName)
		return new CCritical;
	if (L"Damage" == _strScriptName)
		return new CDamage;
	if (L"DeleteEndAnim" == _strScriptName)
		return new CDeleteEndAnim;
	if (L"DontDestoryAddScript" == _strScriptName)
		return new CDontDestoryAddScript;
	if (L"EquipmentWindow" == _strScriptName)
		return new CEquipmentWindow;
	if (L"EquipSlot" == _strScriptName)
		return new CEquipSlot;
	if (L"ETCItemScript" == _strScriptName)
		return new CETCItemScript;
	if (L"GaugeScript" == _strScriptName)
		return new CGaugeScript;
	if (L"Inventory" == _strScriptName)
		return new CInventory;
	if (L"MainWindowScript" == _strScriptName)
		return new CMainWindowScript;
	if (L"MeteorAttackScript" == _strScriptName)
		return new CMeteorAttackScript;
	if (L"MeteorScript" == _strScriptName)
		return new CMeteorScript;
	if (L"MgrScript" == _strScriptName)
		return new CMgrScript;
	if (L"MissileBulletScript" == _strScriptName)
		return new CMissileBulletScript;
	if (L"MonsterScript_Baphomet" == _strScriptName)
		return new CMonsterScript_Baphomet;
	if (L"MonsterScript_BaphometJR" == _strScriptName)
		return new CMonsterScript_BaphometJR;
	if (L"MonsterScript_Creamy" == _strScriptName)
		return new CMonsterScript_Creamy;
	if (L"MonsterScript_Deviling" == _strScriptName)
		return new CMonsterScript_Deviling;
	if (L"MonsterScript_GoldPoring" == _strScriptName)
		return new CMonsterScript_GoldPoring;
	if (L"MonsterScript_Poring" == _strScriptName)
		return new CMonsterScript_Poring;
	if (L"MonsterScript_Wolf" == _strScriptName)
		return new CMonsterScript_Wolf;
	if (L"MonsterScript_WraithDead" == _strScriptName)
		return new CMonsterScript_WraithDead;
	if (L"MoveToMouseScript" == _strScriptName)
		return new CMoveToMouseScript;
	if (L"ParabolaBulletScript" == _strScriptName)
		return new CParabolaBulletScript;
	if (L"PlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"PortalScript" == _strScriptName)
		return new CPortalScript;
	if (L"RespawnScript" == _strScriptName)
		return new CRespawnScript;
	if (L"RevolveBulletScript" == _strScriptName)
		return new CRevolveBulletScript;
	if (L"RevolveItemScript" == _strScriptName)
		return new CRevolveItemScript;
	if (L"Scene_battleground1" == _strScriptName)
		return new CScene_battleground1;
	if (L"Scene_battleground2" == _strScriptName)
		return new CScene_battleground2;
	if (L"Scene_battleground3" == _strScriptName)
		return new CScene_battleground3;
	if (L"Scene_prontera" == _strScriptName)
		return new CScene_prontera;
	if (L"ShortcutSlot" == _strScriptName)
		return new CShortcutSlot;
	if (L"ShortcutWindow" == _strScriptName)
		return new CShortcutWindow;
	if (L"Slot" == _strScriptName)
		return new CSlot;
	if (L"TornadoScript" == _strScriptName)
		return new CTornadoScript;
	if (L"UIMgr" == _strScriptName)
		return new CUIMgr;
	if (L"WaterScript" == _strScriptName)
		return new CWaterScript;
	if (L"WeaponScript" == _strScriptName)
		return new CWeaponScript;
	if (L"AstarMgr" == _strScriptName)
		return new CAstarMgr;
	if (L"ItemTable" == _strScriptName)
		return new CItemTable;
	if (L"MediatorMgr" == _strScriptName)
		return new CMediatorMgr;
	if (L"MonsterTable" == _strScriptName)
		return new CMonsterTable;
	if (L"MouseScript" == _strScriptName)
		return new CMouseScript;
	if (L"PoolingMgr" == _strScriptName)
		return new CPoolingMgr;
	if (L"PortalTable" == _strScriptName)
		return new CPortalTable;
	if (L"SceneTable" == _strScriptName)
		return new CSceneTable;
	if (L"SkillTable" == _strScriptName)
		return new CSkillTable;
	if (L"TileMgrScript" == _strScriptName)
		return new CTileMgrScript;
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	if (NULL != dynamic_cast<CAccessoriesScript*>(_pScript))
		return L"AccessoriesScript";
	if (NULL != dynamic_cast<CArmorScript*>(_pScript))
		return L"ArmorScript";
	if (NULL != dynamic_cast<CBasicBulletScript*>(_pScript))
		return L"BasicBulletScript";
	if (NULL != dynamic_cast<CCameraScript*>(_pScript))
		return L"CameraScript";
	if (NULL != dynamic_cast<CComsumptionItemScript*>(_pScript))
		return L"ComsumptionItemScript";
	if (NULL != dynamic_cast<CCritical*>(_pScript))
		return L"Critical";
	if (NULL != dynamic_cast<CDamage*>(_pScript))
		return L"Damage";
	if (NULL != dynamic_cast<CDeleteEndAnim*>(_pScript))
		return L"DeleteEndAnim";
	if (NULL != dynamic_cast<CDontDestoryAddScript*>(_pScript))
		return L"DontDestoryAddScript";
	if (NULL != dynamic_cast<CEquipmentWindow*>(_pScript))
		return L"EquipmentWindow";
	if (NULL != dynamic_cast<CEquipSlot*>(_pScript))
		return L"EquipSlot";
	if (NULL != dynamic_cast<CETCItemScript*>(_pScript))
		return L"ETCItemScript";
	if (NULL != dynamic_cast<CGaugeScript*>(_pScript))
		return L"GaugeScript";
	if (NULL != dynamic_cast<CInventory*>(_pScript))
		return L"Inventory";
	if (NULL != dynamic_cast<CMainWindowScript*>(_pScript))
		return L"MainWindowScript";
	if (NULL != dynamic_cast<CMeteorAttackScript*>(_pScript))
		return L"MeteorAttackScript";
	if (NULL != dynamic_cast<CMeteorScript*>(_pScript))
		return L"MeteorScript";
	if (NULL != dynamic_cast<CMgrScript*>(_pScript))
		return L"MgrScript";
	if (NULL != dynamic_cast<CMissileBulletScript*>(_pScript))
		return L"MissileBulletScript";
	if (NULL != dynamic_cast<CMonsterScript_Baphomet*>(_pScript))
		return L"MonsterScript_Baphomet";
	if (NULL != dynamic_cast<CMonsterScript_BaphometJR*>(_pScript))
		return L"MonsterScript_BaphometJR";
	if (NULL != dynamic_cast<CMonsterScript_Creamy*>(_pScript))
		return L"MonsterScript_Creamy";
	if (NULL != dynamic_cast<CMonsterScript_Deviling*>(_pScript))
		return L"MonsterScript_Deviling";
	if (NULL != dynamic_cast<CMonsterScript_GoldPoring*>(_pScript))
		return L"MonsterScript_GoldPoring";
	if (NULL != dynamic_cast<CMonsterScript_Poring*>(_pScript))
		return L"MonsterScript_Poring";
	if (NULL != dynamic_cast<CMonsterScript_Wolf*>(_pScript))
		return L"MonsterScript_Wolf";
	if (NULL != dynamic_cast<CMonsterScript_WraithDead*>(_pScript))
		return L"MonsterScript_WraithDead";
	if (NULL != dynamic_cast<CMoveToMouseScript*>(_pScript))
		return L"MoveToMouseScript";
	if (NULL != dynamic_cast<CParabolaBulletScript*>(_pScript))
		return L"ParabolaBulletScript";
	if (NULL != dynamic_cast<CPlayerScript*>(_pScript))
		return L"PlayerScript";
	if (NULL != dynamic_cast<CPortalScript*>(_pScript))
		return L"PortalScript";
	if (NULL != dynamic_cast<CRespawnScript*>(_pScript))
		return L"RespawnScript";
	if (NULL != dynamic_cast<CRevolveBulletScript*>(_pScript))
		return L"RevolveBulletScript";
	if (NULL != dynamic_cast<CRevolveItemScript*>(_pScript))
		return L"RevolveItemScript";
	if (NULL != dynamic_cast<CScene_battleground1*>(_pScript))
		return L"Scene_battleground1";
	if (NULL != dynamic_cast<CScene_battleground2*>(_pScript))
		return L"Scene_battleground2";
	if (NULL != dynamic_cast<CScene_battleground3*>(_pScript))
		return L"Scene_battleground3";
	if (NULL != dynamic_cast<CScene_prontera*>(_pScript))
		return L"Scene_prontera";
	if (NULL != dynamic_cast<CShortcutSlot*>(_pScript))
		return L"ShortcutSlot";
	if (NULL != dynamic_cast<CShortcutWindow*>(_pScript))
		return L"ShortcutWindow";
	if (NULL != dynamic_cast<CSlot*>(_pScript))
		return L"Slot";
	if (NULL != dynamic_cast<CTornadoScript*>(_pScript))
		return L"TornadoScript";
	if (NULL != dynamic_cast<CUIMgr*>(_pScript))
		return L"UIMgr";
	if (NULL != dynamic_cast<CWaterScript*>(_pScript))
		return L"WaterScript";
	if (NULL != dynamic_cast<CWeaponScript*>(_pScript))
		return L"WeaponScript";
	if (NULL != dynamic_cast<CAstarMgr*>(_pScript))
		return L"AstarMgr";
	if (NULL != dynamic_cast<CItemTable*>(_pScript))
		return L"ItemTable";
	if (NULL != dynamic_cast<CMediatorMgr*>(_pScript))
		return L"MediatorMgr";
	if (NULL != dynamic_cast<CMonsterTable*>(_pScript))
		return L"MonsterTable";
	if (NULL != dynamic_cast<CMouseScript*>(_pScript))
		return L"MouseScript";
	if (NULL != dynamic_cast<CPoolingMgr*>(_pScript))
		return L"PoolingMgr";
	if (NULL != dynamic_cast<CPortalTable*>(_pScript))
		return L"PortalTable";
	if (NULL != dynamic_cast<CSceneTable*>(_pScript))
		return L"SceneTable";
	if (NULL != dynamic_cast<CSkillTable*>(_pScript))
		return L"SkillTable";
	if (NULL != dynamic_cast<CTileMgrScript*>(_pScript))
		return L"TileMgrScript";
	return nullptr;
}

