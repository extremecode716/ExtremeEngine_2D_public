#include "stdafx.h"
#include "Critical.h"

CCritical::CCritical()
	: m_fSpeed(0.f)
	, m_vStartPos{ 0.f, 0.f, 0.f }
	, m_vStartRot{ 0.f, 0.f, 1.2f }
	, m_vMovePos{ 0.f, 0.f, 0.f }
	, m_fTempTime(0.f)
	, m_fDeleteTime(0.f)
	, m_fGravity(0.f)
	, m_pMtrl(NULL)
	, m_fReduceScale(0.f)
	, m_vReduceMinScale{0.f , 0.f, 0.f}
{
}


CCritical::~CCritical()
{
	SAFE_DELETE(m_pMtrl);
}


void CCritical::start()
{
#ifdef _DEBUG
	m_fSpeed = 200.f;
#else
	m_fSpeed = 400.f;
#endif
	m_fGravity = 9.8f;
	m_fDeleteTime = 2.f;

	m_vReduceMinScale = Vec3(100.f, 100.f, 1.f);

	m_pMtrl = MeshRender()->GetMaterial();
}

int CCritical::update()
{
	float fDT = DT();
	m_fTempTime += fDT;
	Vec3 vPos = Transform()->GetLocalPos();
	Vec3 vRot = Transform()->GetLocalRot();

#ifdef _DEBUG
	float fData = (m_fTempTime * m_fTempTime * 50);
#else
	float fData = (m_fTempTime * m_fTempTime * 100);
#endif
	m_pMtrl->SetData(SHADER_PARAM::SP_FLOAT_0, &fData);

	m_vMovePos.x = cos(m_vStartRot.z) * m_fSpeed * fDT;
	m_vMovePos.y = sin(m_vStartRot.z) * m_fSpeed * fDT - (m_fGravity * m_fTempTime * m_fTempTime);

	vPos.x += m_vMovePos.x;
	vPos.y += m_vMovePos.y;

	ReduceScale();

	if (m_fTempTime >= m_fDeleteTime)
	{
		// 자기 자신 오브젝트 삭제. 
		CDestroyMgr::GetInst()->AddGameObject(GetGameObject());
	}

	Transform()->SetLocalPos(vPos);
	return RET_SUCCESS;
}


void CCritical::ReduceScale()
{
	Vec3 vScale = Transform()->GetLocalScale();

	if (vScale.x > m_vReduceMinScale.x && vScale.y > m_vReduceMinScale.y)
	{
		m_fReduceScale = DT();
		vScale.x -= m_fReduceScale * 200;
		vScale.y -= m_fReduceScale * 200;
	}
	else
	{
		vScale = m_vReduceMinScale;
	}

	Transform()->SetLocalScale(vScale);
}