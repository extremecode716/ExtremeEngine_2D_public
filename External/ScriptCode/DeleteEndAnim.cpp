#include "stdafx.h"
#include "DeleteEndAnim.h"

#include "Animation.h"

CDeleteEndAnim::CDeleteEndAnim()
	: m_bAnim(false)
	, m_bEnd(false)
	, m_iAnimFrameIdex(0)
	, m_iAnimMaxFrameIdx(0)
	, m_iCount(0)
	, m_iMaxCount(1)
{
}

CDeleteEndAnim::~CDeleteEndAnim()
{
}

void CDeleteEndAnim::start()
{
	if (Animator() != NULL)
	{
		m_bAnim = true;
		m_iAnimMaxFrameIdx = Animator()->GetCurAnim()->GetMaxFrameIdx() - 1;
	}

	if (m_bAnim == false)
		CDestroyMgr::GetInst()->AddGameObject(GetGameObject());
}

int CDeleteEndAnim::update()
{
	m_iAnimFrameIdex = Animator()->GetCurAnim()->GetFrameIdx();

	if (m_iAnimFrameIdex == m_iAnimMaxFrameIdx)
	{
		if (m_bEnd == false)
		{
			m_bEnd = true;
			++m_iCount;
			if (m_iCount >= m_iMaxCount)
			{
				CDestroyMgr::GetInst()->AddGameObject(GetGameObject());
			}
		}
	}
	else
	{
		m_bEnd = false;
	}


	return RET_SUCCESS;
}

