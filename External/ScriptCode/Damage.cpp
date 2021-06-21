#include "stdafx.h"
#include "Damage.h"
#include "RandomScript.h"

CDamage::CDamage()
	: m_iDamage(1)
	, m_iDamageCount(1)
	, m_pTex(NULL)
	, m_pCloneMtrl(NULL)
	, m_fXSize(40)
	, m_fYSize(50)
	, m_fSpeed(0.f)
	, m_vStartPos{ 0.f, 0.f, 0.f }
	, m_vStartRot{ 0.f, 0.f, 1.2f }
	, m_vMovePos{ 0.f, 0.f, 0.f }
	, m_fTempTime(0.f)
	, m_fDeleteTime(0.f)
	, m_fGravity(0.f)
	, m_fReduceScale(0.f)
	, m_vReduceMinScale{ 0.f , 0.f, 0.f }
{
}


CDamage::~CDamage()
{
	// Vector Res 추가되어 있기 때문에 내가 삭제 해주면 안됨. 고민중
	SAFE_DELETE(m_pCloneMtrl);
}

void CDamage::CalDamageCount()
{
	int iDamage = m_iDamage;
	int iCount = 0;

	while (iDamage > 0)
	{
		++iCount;
		iDamage /= 10;
	}

	m_iDamageCount = iCount;
}

void CDamage::SetDamage(int _idamage)
{
	m_iDamage = _idamage;
}

void CDamage::start()
{
	CalDamageCount();

	m_pCloneMtrl = MeshRender()->GetMaterial();

	int iColorRandom = GameRandom::RandomInt(0, 10);
	if (iColorRandom > 8)
	{
		m_pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"RedNumberTex");
	}
	else if (iColorRandom > 6)
	{
		m_pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"YellowNumberTex");
	}
	else
	{
		m_pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"NumberTex");
	}
	m_pCloneMtrl->SetData(SHADER_PARAM::SP_TEX_0, &m_pTex);
	m_pCloneMtrl->SetData(SHADER_PARAM::SP_INT_0, &m_iDamage);
	m_pCloneMtrl->SetData(SHADER_PARAM::SP_INT_1, &m_iDamageCount);
	Vec4 vData = { 0.f, 0.f, 1.f, 1.f };
	m_pCloneMtrl->SetData(SHADER_PARAM::SP_VEC4_0, &vData);

	Vec3 vScale = Vec3(m_fXSize * m_iDamageCount, m_fYSize, 1.f);
	Transform()->SetLocalScale(vScale);

#ifdef _DEBUG
	m_fSpeed = 200.f;
#else
	m_fSpeed = 400.f;
#endif // _DEBUG


	m_fGravity = 9.8f;
	m_fDeleteTime = 2.f;

	float vXMinReduce = m_fXSize / 3.f * m_iDamageCount;
	m_vReduceMinScale = Vec3(vXMinReduce, 10.f, 1.f);
}

int CDamage::update()
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
	m_pCloneMtrl->SetData(SHADER_PARAM::SP_FLOAT_0, &fData);

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

void CDamage::ReduceScale()
{
	Vec3 vScale = Transform()->GetLocalScale();

	m_fReduceScale = DT();
	if (vScale.x > m_vReduceMinScale.x)
	{
		vScale.x -= m_fReduceScale * 200;
		if (vScale.x < m_vReduceMinScale.x)
		{
			vScale.x = m_vReduceMinScale.x;
		}
	}

	if (vScale.y > m_vReduceMinScale.y)
	{
		vScale.y -= m_fReduceScale * 20;

		if (vScale.y < m_vReduceMinScale.y)
		{
			vScale.y = m_vReduceMinScale.y;
		}
	}

	Transform()->SetLocalScale(vScale);
}

void CDamage::SetColor(Vec4 _vColor)
{
	m_pCloneMtrl->SetData(SHADER_PARAM::SP_VEC4_1, &_vColor);
}
