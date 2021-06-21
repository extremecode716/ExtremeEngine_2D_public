#include "stdafx.h"
#include "ParabolaBulletScript.h"

#include "PlayerScript.h"

#include "Scene.h"
#include "Layer.h"
#include "SceneMgr.h"

CParabolaBulletScript::CParabolaBulletScript()
	: m_fSpeed(0.f)
	, m_vMoveRot(Vec3(0.f, 0.f, 0.f))
	, m_vMovePos(Vec3(0.f, 0.f, 0.f))
	, m_isCollision(false)
	, m_fTempTime(0.f)
	, m_fGravity(0.f)
{
}


CParabolaBulletScript::~CParabolaBulletScript()
{
}


float CParabolaBulletScript::Pow(float _valueX, int _valueY)
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

void CParabolaBulletScript::start()
{
	//////////////////
	// Bullet Setting
	//////////////////
	m_Idx = 201801282;
	m_strName = L"Parabola Bullet";
	m_eState = BULLET_STATE::STATE_START;
	m_pTransform = Transform();
	m_pTransform->SetLocalPos(m_vStartPos);
	m_pTransform->SetLocalRot(m_vStartRot);
	m_pTransform->SetLocalScale(Vec3(10.f, 10.f, 1.f));

	m_fSpeed = 200.f;
	m_fGravity = 0.22f;
	m_fDeleteTime = 7.f;
}

int CParabolaBulletScript::update()
{
	float fDT = DT();
	m_fTempTime += fDT;
	m_fElapsedTimeAfterFire += fDT;
	m_eState = BULLET_STATE::STATE_UPDATE;

	Vec3 vPos = m_pTransform->GetLocalPos();
	Vec3 vRot = m_pTransform->GetLocalRot();


	m_vMoveRot.z = m_vStartRot.z;
	m_vMovePos.x = cos(m_vMoveRot.z) * m_fSpeed * fDT;
	m_vMovePos.y = sin(m_vMoveRot.z) * m_fSpeed * fDT - (m_fGravity * Pow(m_fTempTime, 2));

	vPos.x += m_vMovePos.x;
	vPos.y += m_vMovePos.y;

	//cout << vPos.x << "    " << vPos.y << endl;

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
