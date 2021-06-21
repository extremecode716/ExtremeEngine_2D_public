#include "stdafx.h"
#include "BulletScript.h"

CBulletScript::CBulletScript()
	: m_Idx(0)
	, m_strName(L"")
	, m_pOwnerObj(NULL)
	, m_pTransform(NULL)
	, m_eState(BULLET_STATE::STATE_NONE)
	, m_vStartPos(Vec3(0.f, 0.f, 0.f))
	, m_vStartRot(Vec3(0.f, 0.f, 0.f))
	, m_fElapsedTimeAfterFire(0.f)
	, m_fDeleteTime(3.f)
	, m_fAttack(0)
{
}

CBulletScript::~CBulletScript()
{
}

void CBulletScript::start()
{
}

int CBulletScript::update()
{
	return RET_SUCCESS;
}


