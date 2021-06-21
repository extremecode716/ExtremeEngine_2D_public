#pragma once

#include "global.h"

enum class BULLET_TYPE
{
	BULLET_NONE,
	BULLET_BASIC,
	BULLET_PARABOLA,
	BULLET_MISSILE,
	BULLET_REVOLVE,
	BULLET_SHOTGUN,
	BULLET_END
};

typedef struct _tagGun
{
	wstring				strName;
	UINT				iBulletType;
	list<UINT>			listAvailableBulletType;
	float               fDelayTime;
	float				fReloadTime;
	bool				isFireFlag;

	Vec3				vPos;
	Vec3                vRot;

	_tagGun()
		: strName(L""), iBulletType(0), fDelayTime(0.1f), fReloadTime(0.2f), isFireFlag(true)
		, vPos(Vec3(0.f, 0.f, 0.f)), vRot(Vec3(0.f, 0.f, 0.f))
	{
	}
}tGun;

typedef struct _tWeaponInfo
{
	wstring			strName;
	float			fRange;
	int				iDamage;
	float			fSpeed;

	_tWeaponInfo()
		: strName(L""), fRange(0.f), iDamage(0), fSpeed(0.f)
	{
	}
	void SetInfo(const wstring& _strName, float _fRange,int _Damage, float _speed)
	{
		strName = _strName;
		fRange = _fRange;
		iDamage = _Damage;
		fSpeed = _speed;
	}
}tWeaponInfo;


typedef struct _tArmorInfo
{
	wstring			strName;
	int				iDefense;

	_tArmorInfo()
		: strName(L""), iDefense(0)
	{

	}
	void SetInfo(const wstring& _strName, int _iDefense)
	{
		strName = _strName;
		iDefense = _iDefense;
	}
}tArmorInfo;

typedef struct _tAccInfo
{
	wstring			strName;
	int				iDamage;
	int				iDefense;

	_tAccInfo()
		: strName(L""), iDamage(0), iDefense(0)
	{

	}
	void SetInfo(const wstring& _strName, int _iDamage ,int _iDefense)
	{
		strName = _strName;
		iDamage = _iDamage;
		iDefense = _iDefense;
	}
}tAccInfo;

typedef struct _tStatus
{
	int iLv;
	int iMaxHP;
	int iMaxMP;
	int iHP;
	int iMP;

	int iStr;
	int iAgi;
	int iVit;
	int iInt;
	int iDex;
	int iLuk;

	int iAtk;
	int iDef;
	int iMatk;
	int iHit;
	int iFlee;
	int iCritical;
	int iApsd;
	int iSpeed;
	int iStatus_Point;

	_tStatus() 
		: iLv(0), iMaxHP(0), iMaxMP(0), iHP(0), iMP(0), iStr(0), iAgi(0), iVit(0), iInt(0), iDex(0), iLuk(0)
		, iAtk(0), iDef(0), iMatk(0), iHit(0), iFlee(0), iCritical(0), iApsd(0), iSpeed(0), iStatus_Point(0)
	{};

	_tStatus(int _lv, int _maxhp, int _maxmp, int _hp, int _mp, int _str, int _agi, int _vit, int _int, int _dex, int _luk
	, int _atk, int _def, int _matk, int _hit, int _flee, int _critical, int _apsd, int _speed,int _statuse_point)
		: iLv(_lv), iMaxHP(_maxhp), iMaxMP(_maxmp), iHP(_hp), iMP(_mp), iStr(_str), iAgi(_agi), iVit(_vit), iInt(_int), iDex(_dex), iLuk(_luk)
		, iAtk(_atk), iDef(_def), iMatk(_matk), iHit(_hit), iFlee(_flee), iCritical(_critical), iApsd(_apsd), iSpeed(_speed)
		, iStatus_Point(_statuse_point)
	{};

	void SetStatus(int _lv, int _maxhp, int _maxmp, int _hp, int _mp, int _str, int _agi, int _vit, int _int, int _dex, int _luk
		, int _atk, int _def, int _matk, int _hit, int _flee, int _critical, int _apsd, int _speed,int _statuse_point)
	{
		iLv = _lv;
		iMaxHP = _maxhp;
		iMaxMP = _maxmp;
		iHP = _hp;
		iMP = _mp;

		iStr = _str;
		iAgi = _agi;
		iVit = _vit;
		iInt = _int;
		iDex = _dex;
		iLuk = _luk;

		iAtk = _atk;
		iDef = _def;
		iMatk = _matk;
		iHit = _hit;
		iFlee = _flee;
		iCritical = _critical;
		iApsd = _apsd;
		iSpeed = _speed;
		iStatus_Point = _statuse_point;
	}

	int GetApsd() { return iApsd; }

}tStatus;

enum class DIRECTION_8
{
	NONE,
	UP,
	UPPERRIGHT,
	RIGHT,
	LOWERRIGHT,
	DOWN,
	LOWERLEFT,
	LEFT,
	UPPERLEFT
};

enum class MessageType
{
	NONE_MT,
	ATTACK_MT,
	FIND_MT,
	PATHFIND_MT,
	DIE_MT,
	ERROR_MT
	// 추가중
};

enum class TILE_TYPE
{
	BASIC,
	BLOCK
};

typedef struct _tPathNode
{
	UINT  iIndexX;
	UINT  iIndexY;

	float fCostF;
	float fCostG;
	float fCostH;
	_tPathNode*  pParrentNode;

	_tPathNode()
		: iIndexX(0), iIndexY(0), fCostF(0.f), fCostG(0.f), fCostH(0.f), pParrentNode(NULL)
	{};
	~_tPathNode()
	{};
}tPathNode;

// 오브젝트 타입 정의용.
enum class OBJECT_TYPE
{
	NONE_TYPE = 0,
	PLAYER_TYPE = 1,
	MONSTER_TYPE,
	NPC_TYPE,
	PET_TYPE,
	MGR_TYPE,
	END
};

enum class STATE
{
	DIYING = 0,
	ATTACK = 1,
	WALKING = 2,
	DAMAGE = 3
};

enum class ITEM_TYPE
{
	ETC_TYPE         = 0x01,
	COMSUMPTION_TYPE = 0x02,
	EQUIP_TYPE       = 0x04,
	EQUIP_HEAD1_TYPE = 0x08 | EQUIP_TYPE,
	EQUIP_HEAD2_TYPE = 0x10 | EQUIP_TYPE,
	EQUIP_HEAD3_TYPE = 0x20 | EQUIP_TYPE,
	EQUIP_BODY_TYPE  = 0x40 | EQUIP_TYPE,
	EQUIP_RHAND_TYPE = 0x80 | EQUIP_TYPE,
	EQUIP_LHAND_TYPE = 0x100 | EQUIP_TYPE,
	EQUIP_ROBE_TYPE  = 0x200 | EQUIP_TYPE,
	EQUIP_SHOES_TYPE = 0x400 | EQUIP_TYPE,
	EQUIP_ACC1_TYPE  = 0x800 | EQUIP_TYPE,
	EQUIP_ACC2_TYPE  = 0x1000 | EQUIP_TYPE
};

enum class MONSTER_AGGRESSIVE_TYPE
{
	NON_AGGRESSIVE_TYPE,
	AGGRESSIVE_TYPE,
};

union PATH_NODE_ID
{
	struct
	{
		UINT	iIndexXID;
		UINT	iIndexYID;
	};
	ULONG64 llID;
};