#include "stdafx.h"
#include "RevolveBulletScript.h"

#include "PlayerScript.h"

#include "Scene.h"
#include "Layer.h"
#include "SceneMgr.h"

CRevolveBulletScript::CRevolveBulletScript()
	: m_fSpeed(0.f)
	, m_vMoveRot(Vec3(0.f, 0.f, 0.f))
	, m_vMovePos(Vec3(0.f, 0.f, 0.f))
	, m_isCollision(false)
	, m_fTempTime(0.f)
	, m_pTargetObj(NULL)
	, m_IsTarget(false)
{
}


CRevolveBulletScript::~CRevolveBulletScript()
{
}


float CRevolveBulletScript::Lerp(const float _a, const float _b, float _t)
{
	return _a + (_b - _a) * _t;
}

void CRevolveBulletScript::start()
{
	//////////////////
	// Bullet Setting
	//////////////////
	m_Idx = 201801284;
	m_strName = L"Revolve Bullet";
	m_eState = BULLET_STATE::STATE_START;
	m_pTransform = Transform();
	m_pTransform->SetLocalPos(m_vStartPos);
	m_pTransform->SetLocalRot(m_vStartRot);
	m_pTransform->SetLocalScale(Vec3(10.f, 10.f, 1.f));

	m_fSpeed = 200.f;
	m_fDeleteTime = 30.f;

	/////////////////////////
	// Bullet Target Setting
	/////////////////////////
	m_pTargetObj = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Monster")->FindWithTag(L"Monster");
	if (NULL != m_pTargetObj)
	{
		m_vTargetPos = m_pTargetObj->Transform()->GetLocalPos();
		m_IsTarget = true;
	}
}

int CRevolveBulletScript::update()
{
	if (NULL != m_pTargetObj)
	{
		m_vTargetPos = m_pTargetObj->Transform()->GetLocalPos();
		m_IsTarget = true;
	}

	float fDT = DT();
	m_fTempTime += fDT;
	m_fElapsedTimeAfterFire += fDT;
	m_eState = BULLET_STATE::STATE_UPDATE;

	Vec3 vPos = m_pTransform->GetLocalPos();
	Vec3 vRot = m_pTransform->GetLocalRot();

	m_vMoveRot.z = m_vStartRot.z;
	m_vMoveRot.z = GetRotFromTarget(vPos, m_vMoveRot);
	m_vMovePos.x = vPos.x + cos(m_vMoveRot.z) * m_fSpeed * fDT;
	m_vMovePos.y = vPos.y + sin(m_vMoveRot.z) * m_fSpeed * fDT;

	vPos.x = m_vMovePos.x;
	vPos.y = m_vMovePos.y;
	vRot = m_vMoveRot;

	if (m_fTempTime >= m_fDeleteTime)
	{
		// 자기 자신 오브젝트 삭제. 
		m_eState = BULLET_STATE::STATE_DELETE;
//		CDestroyMgr::GetInst()->AddGameObject(GetGameObject());
	}

	m_pTransform->SetLocalPos(vPos);
	m_pTransform->SetLocalRot(vRot);
	return RET_SUCCESS;
}

float CRevolveBulletScript::GetRotFromTarget(const Vec3& _vPos, const Vec3& _vRot)
{
	if (false == m_IsTarget) return _vRot.z;

	float angle;

	Vec3 vPos = _vPos;
	Vec3 vRot = _vRot;

	angle =  atan2(vPos.x - m_vTargetPos.x, vPos.y - m_vTargetPos.y);

	vRot.z = -angle;

	return vRot.z;
}
