#include "stdafx.h"
#include "RevolveItemScript.h"

#include "Scene.h"
#include "Layer.h"
#include "SceneMgr.h"

#include <math.h>


CRevolveItemScript::CRevolveItemScript()
	: m_fSpeed(0.f)
	, m_vMoveRot(Vec3(0.f, 0.f, 0.f))
	, m_vMovePos(Vec3(0.f, 0.f, 0.f))
	, m_bAlive(false)
	, m_bCollision(false)
	, m_fTempTime(0.f)
	, m_pTargetObj(NULL)
	, m_IsTarget(false)
	, m_bRevolve(false)
	, m_fDistanceRevolve(150.f)
	, m_fCollisionDistanceFromTarget(100.f)
	, m_fCollisionDistanceFromBullet(80.f)
	, m_vStartPos(Vec3(0.f, 0.f, 0.f))
	, m_vStartRot(Vec3(0.f, 0.f, 0.f))
	, m_fDeleteTime(15.f)
{
}


CRevolveItemScript::~CRevolveItemScript()
{
}

void CRevolveItemScript::OnCollisionEnter(CCollider * _pOther)
{
	if (!m_bRevolve) return;

	m_bCollision = true;
	if (m_bAlive)
	{
		// 자기 자신 오브젝트 삭제. 
//		CDestroyMgr::GetInst()->AddGameObject(GetGameObject());

		m_bAlive = false;
	}

}

void CRevolveItemScript::OnCollisionExit(CCollider * _pOther)
{
	if (!m_bRevolve) return;

	m_bCollision = false;
}



float CRevolveItemScript::Lerp(const float _a, const float _b, float _t)
{
	return _a + (_b - _a) * _t;
}

/*
float CRevolveItemScript::Sqrt(float _x)
{
	float temp = 0.f;
	float curculating = 0.f;

	curculating = (1 + (_x / 1)) * 0.5f;

	while (true)
	{
		temp = curculating;
		curculating = (curculating + (_x / curculating)) * 0.5f;

		if (temp - curculating < 0.005f || temp - curculating < -0.005f)
			break;
	}

	return curculating;
}
*/

float CRevolveItemScript::Pow(float _valueX, int _valueY)
{
	float result = 1;
	while (_valueY)
	{
		if (_valueY & 1)
			result *= _valueX;
		_valueY >>= 1;
		_valueX *= _valueX;
	}

	return result;
}
void CRevolveItemScript::start()
{
	//////////////////
	// Item Setting
	//////////////////
	m_iIdx = 201801284;
	m_strName = L"Revolve Item";
	m_pTransform = Transform();
	m_pTransform->SetLocalPos(m_vStartPos);
	m_pTransform->SetLocalRot(m_vStartRot);
	m_pTransform->SetLocalScale(Vec3(100.f, 100.f, 1.f));

	m_bAlive = true;
	m_fSpeed = 500.f;
	m_fDeleteTime = 20.f;

	/////////////////////////
	// Player Target Setting
	/////////////////////////
	m_pTargetObj = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Player")->FindWithTag(L"Player");
	if (NULL != m_pTargetObj)
	{
		m_vTargetPos = m_pTargetObj->Transform()->GetLocalPos();
		m_IsTarget = true;
	}
}

int CRevolveItemScript::update()
{
	if (NULL != m_pTargetObj)
	{
		m_vTargetPos = m_pTargetObj->Transform()->GetLocalPos();
		m_IsTarget = true;
	}
	else
	{
		m_IsTarget = false;
	}

	if (!m_IsTarget) return 0;

	float fDT = DT();
	m_fTempTime += fDT;
	Vec3 vPos = m_pTransform->GetLocalPos();
	Vec3 vRot = m_pTransform->GetLocalRot();


	if (!m_bRevolve)
	{
		m_fDistanceFromTarget = GetDistanceFromTarget(vPos);

		if (m_fDistanceFromTarget <= m_fCollisionDistanceFromTarget)
		{
			m_bRevolve = true;
		}
	}

	if (m_bRevolve)
	{
		m_vMoveRot.z += XM_PI * fDT;

		vPos = Vec3(m_fDistanceRevolve * cos(m_vMoveRot.z) + m_vTargetPos.x, m_fDistanceRevolve * sin(m_vMoveRot.z) + m_vTargetPos.y, vPos.z);

		//vRot = m_vMoveRot;
	}

	if (m_fTempTime >= m_fDeleteTime)
	{
		// 자기 자신 오브젝트 삭제. 
//		CDestroyMgr::GetInst()->AddGameObject(GetGameObject());
		m_bAlive = false;
	}

	m_pTransform->SetLocalPos(vPos);
	m_pTransform->SetLocalRot(vRot);
	return RET_SUCCESS;
}


float CRevolveItemScript::GetRotFromTarget(const Vec3& _vPos, const Vec3& _vRot)
{
	if (false == m_IsTarget) return _vRot.z;

	float angle;

	Vec3 vPos = _vPos;
	Vec3 vRot = _vRot;

	angle = atan2(vPos.x - m_vTargetPos.x, vPos.y - m_vTargetPos.y);

	vRot.z = -angle;

	return vRot.z;
}

float CRevolveItemScript::GetDistanceFromTarget(const Vec3& _vPos)
{
	if (false == m_IsTarget) return 1000.f;
	Vec3 vPos = _vPos;

	
	float fDistance = sqrt(Pow(vPos.x - m_vTargetPos.x, 2) + Pow(vPos.y - m_vTargetPos.y, 2));

	return fDistance;
}

float CRevolveItemScript::GetDistance(Vec3& _vPos, Vec3& _vTarget)
{
	Vec3 vPos = _vPos;
	Vec3 vTarget = _vTarget;

	float fDistance = sqrt(Pow(vPos.x - vTarget.x, 2) + Pow(vPos.y - vTarget.y, 2));

	return fDistance;
}
