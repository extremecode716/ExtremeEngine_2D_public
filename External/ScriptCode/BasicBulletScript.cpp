#include "stdafx.h"
#include "BasicBulletScript.h"

#include "PlayerScript.h"

#include "Scene.h"
#include "Layer.h"
#include "SceneMgr.h"

#include "RevolveItemScript.h"
CBasicBulletScript::CBasicBulletScript()
	: m_fSpeed(0.f)
	, m_vMoveRot(Vec3(0.f,0.f,0.f))
	, m_vMovePos(Vec3(0.f,0.f,0.f))
	, m_bAlive(false)
	, m_bCollision(false)
	, m_fTempTime(0.f)
{
}


CBasicBulletScript::~CBasicBulletScript()
{

}

void CBasicBulletScript::OnCollisionEnter(CCollider * _pOther)
{
	m_bCollision = true;
	if (m_bAlive)
	{
		bool bItemRevolve = _pOther->GetGameObject()->Script<CRevolveItemScript>()->IsRevolve();
		if (bItemRevolve)
		{
			// 자기 자신 오브젝트 삭제. 
//			CDestroyMgr::GetInst()->AddGameObject(GetGameObject());
			m_bAlive = false;
		}
	}
}

void CBasicBulletScript::OnCollisionExit(CCollider * _pOther)
{
	m_bCollision = false;
}

void CBasicBulletScript::start()
{
	//////////////////
	// Bullet Setting
	//////////////////
	m_Idx = 201801281;
	m_strName = L"Basic Bullet";
	m_eState = BULLET_STATE::STATE_START;
	m_pTransform = Transform();
 	m_pTransform->SetLocalPos(m_vStartPos);
	m_pTransform->SetLocalRot(m_vStartRot);
	m_pTransform->SetLocalScale(Vec3(10.f, 10.f, 1.f));

	m_bAlive = true;
	m_fSpeed = 200.f;
	//m_fDeleteTime = 3.f;
}

int CBasicBulletScript::update()
{
	float fDT = DT();
	m_fTempTime += fDT;
	m_fElapsedTimeAfterFire += fDT;
	m_eState = BULLET_STATE::STATE_UPDATE;

	Vec3 vPos = m_pTransform->GetLocalPos();
	Vec3 vRot = m_pTransform->GetLocalRot();

	m_vMoveRot.z = m_vStartRot.z;
	m_vMovePos.x = cos(m_vMoveRot.z) * m_fSpeed * fDT;
	m_vMovePos.y = sin(m_vMoveRot.z) * m_fSpeed * fDT;

	vPos.x += m_vMovePos.x;
	vPos.y += m_vMovePos.y;

	m_pTransform->SetLocalPos(vPos);
	m_pTransform->SetLocalRot(vRot);

	if (m_fTempTime >= m_fDeleteTime)
	{
		// 자기 자신 오브젝트 삭제. 
		m_eState = BULLET_STATE::STATE_DELETE;
		CDestroyMgr::GetInst()->AddGameObject(GetGameObject());
		m_bAlive = false;
	}
	return RET_SUCCESS;
}

void CBasicBulletScript::SetGrayColor()
{
	m_pMtrl = MeshRender()->GetMaterial();
	float fData = 1.f;
	m_pMtrl->SetData(SHADER_PARAM::SP_FLOAT_0, &fData);
}
