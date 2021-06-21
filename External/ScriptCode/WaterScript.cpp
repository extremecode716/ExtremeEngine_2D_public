#include "stdafx.h"
#include "WaterScript.h"


int CWaterScript::update()
{
	m_fAccTime += DT();

	if (m_fAccTime > 10000.f)
	{
		m_fAccTime = 0.f;
	}

	//MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::SP_INT_0, &TYPE); // е╦ют
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::SP_FLOAT_0, &m_fAccTime);

	return RET_SUCCESS;
}

CWaterScript::CWaterScript()
	: m_fAccTime(0.f)
{
}


CWaterScript::~CWaterScript()
{
}
