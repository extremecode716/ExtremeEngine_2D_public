#pragma once
#include "global.h"

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llFrequency;
	LARGE_INTEGER	m_llCurCnt;
	LARGE_INTEGER	m_llOldCnt;
	float			m_fOldDeltaTime;
	float			m_fDeltaTime;
	float			m_fAccTime;

	float			m_fFPS;
	float			m_fAccFPS;
	int				m_iAccFrame;


public:
	void init();
	int update();
	void render(HDC _dc);

public:
	float DeltaTime() { return m_fDeltaTime; }
};
