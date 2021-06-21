#include "TimeMgr.h"

#include "FontEngine.h"

CTimeMgr::CTimeMgr()
	: m_llFrequency{ 0 }
	, m_llCurCnt{ 0 }
	, m_llOldCnt{ 0 }
	, m_fDeltaTime(0.f)
	, m_fOldDeltaTime(1.f)
	, m_fAccTime(0.f)
	, m_iAccFrame(0)
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::init()
{
	// 초당 진동 회수
	QueryPerformanceFrequency(&m_llFrequency);
	QueryPerformanceCounter(&m_llCurCnt);
	m_llOldCnt = m_llCurCnt;
}

int CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCnt);
	m_fDeltaTime = (m_llCurCnt.QuadPart - m_llOldCnt.QuadPart) / (float)m_llFrequency.QuadPart;
	m_llOldCnt = m_llCurCnt;

	// DT 가 너무 크게 튀는경우
	if (m_fDeltaTime > m_fOldDeltaTime * 1000.f)
	{
		m_fDeltaTime = m_fOldDeltaTime;
	}

	// FPS 계산
	m_fFPS = 1 / m_fDeltaTime;
	m_iAccFrame += 1;

	m_fAccTime += m_fDeltaTime;
	if (m_fAccTime > 1.f)
	{
		m_fAccTime = 0.f;
		QueryPerformanceFrequency(&m_llFrequency);

		// 프레임 카운팅 0 으로 초기화
		m_fAccFPS = (float)m_iAccFrame;
		m_iAccFrame = 0;
	}

	m_fOldDeltaTime = m_fDeltaTime;

	return RET_SUCCESS;
}

void CTimeMgr::render(HDC _dc)
{
	wchar_t szFPS[50] = {};
	wsprintf(szFPS, L"FPS : %d", (int)m_fAccFPS);
	//TextOut(_dc, 0, 0, szFPS, wcslen(szFPS));

	//CFontEngine::GetInst()->DrawFont(szFPS, 50.f, 50.f, 30.f, ABGR(10, 240, 10, 255));
}
