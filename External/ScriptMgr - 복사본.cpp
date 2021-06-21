#include "ScriptMgr.h"

#include "PlayerScript.h"
#include "MonsterScript.h"
#include "CameraScript.h"
#include "BasicBulletScript.h"
#include "MissileBulletScript.h"
#include "ParabolaBulletScript.h"
#include "RevolveBulletScript.h"
#include "RevolveItemScript.h"
#include "RespawnScript.h"

void CScriptMgr::GetScriptInfo(vector<tScriptInfo>& _vec)
{
	_vec.push_back(tScriptInfo{ L"PlayerScript", typeid(CPlayerScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"MonsterScript", typeid(CMonsterScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"CameraScript", typeid(CCameraScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"BasicBulletScript", typeid(CBasicBulletScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"MissileBulletScript", typeid(CMissileBulletScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"ParabolaBulletScript", typeid(CParabolaBulletScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"RevolveBulletScript", typeid(CRevolveBulletScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"RevolveItemScript", typeid(CRevolveItemScript).hash_code() });
	_vec.push_back(tScriptInfo{ L"RespawnScript", typeid(CRespawnScript).hash_code() });
}

CScript * CScriptMgr::GetScript(DWORD _dwTypeId)
{
	if (typeid(CPlayerScript).hash_code() == _dwTypeId)
		return new CPlayerScript;
	else if (typeid(CMonsterScript).hash_code() == _dwTypeId)
		return new CMonsterScript;
	else if (typeid(CCameraScript).hash_code() == _dwTypeId)
		return new CCameraScript;
	else if (typeid(CBasicBulletScript).hash_code() == _dwTypeId)
		return new CBasicBulletScript;
	else if (typeid(CMissileBulletScript).hash_code() == _dwTypeId)
		return new CMissileBulletScript;
	else if (typeid(CParabolaBulletScript).hash_code() == _dwTypeId)
		return new CParabolaBulletScript;
	else if (typeid(CRevolveBulletScript).hash_code() == _dwTypeId)
		return new CRevolveBulletScript;
	else if (typeid(CRevolveItemScript).hash_code() == _dwTypeId)
		return new CRevolveItemScript;
	else if (typeid(CRespawnScript).hash_code() == _dwTypeId)
		return new CRespawnScript;

	return NULL;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	if (NULL != dynamic_cast<CRespawnScript*>(_pScript))
		return L"RespawnScript";
	if (NULL != dynamic_cast<CRevolveItemScript*>(_pScript))
		return L"RevolveItemScript";
	if (NULL != dynamic_cast<CRevolveBulletScript*>(_pScript))
		return L"RevolveBulletScript";
	if (NULL != dynamic_cast<CParabolaBulletScript*>(_pScript))
		return L"ParabolaBulletScript";
	if (NULL != dynamic_cast<CMissileBulletScript*>(_pScript))
		return L"MissileBulletScript";
	if (NULL != dynamic_cast<CBasicBulletScript*>(_pScript))
		return L"BasicBulletScript";
	if (NULL != dynamic_cast<CCameraScript*>(_pScript))
		return L"CameraScript";
	if (NULL != dynamic_cast<CMonsterScript*>(_pScript))
		return L"MonsterScript";
	if (NULL != dynamic_cast<CPlayerScript*>(_pScript))
		return L"PlayerScript";

	return nullptr;
}

