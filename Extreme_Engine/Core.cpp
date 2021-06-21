#include "Core.h"

#include "Device.h"
#include "PathMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ShaderMgr.h"
#include "ResMgr.h"
#include "SceneMgr.h"
#include "InstancingBuffer.h"

#include "FontEngine.h"
#include "Sound.h"

// 메모리 릭 검출
//#include <vld.h>


CCore::CCore()
	: m_hWnd(NULL)
{
}

CCore::~CCore()
{
}

int CCore::init(HWND _hWnd, bool _bWindow)
{
	m_hWnd = _hWnd;

	if (FAILED(CDevice::GetInst()->init(_hWnd, _bWindow)))
	{
		MessageBox(_hWnd, L"장치 초기화 실패", L"실패", MB_OK);
		return RET_FAILED;
	}

	CreateConstBuffer();

	// Manager 초기화
	CPathMgr::init();
	CKeyMgr::GetInst()->init(m_hWnd);
	CTimeMgr::GetInst()->init();
	CShaderMgr::GetInst()->init();
	CResMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();
	CInstancingBuffer::GetInst()->init();
	// 폰트
	CFontEngine::GetInst()->init();

	//float fCol[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
	float fCol[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
	CDevice::GetInst()->SetClearColor(fCol);


	return RET_SUCCESS;
}

int CCore::run()
{
	update();

	render();

	return RET_SUCCESS;
}

int CCore::update()
{
	CKeyMgr::GetInst()->update();
	CTimeMgr::GetInst()->update();
	CSceneMgr::GetInst()->progress();
	CSound::g_pSystem->update();

	return RET_SUCCESS;
}

void CCore::render()
{

	CDevice::GetInst()->ClearTarget();

	CSceneMgr::GetInst()->render();

	//폰트
	CFontEngine::GetInst()->DrawFont();

	CDevice::GetInst()->Present();

}

void CCore::CreateConstBuffer()
{
	// 상수버퍼 만들기
	CDevice::GetInst()->CreateConstBuffer(L"Transform", sizeof(tTransform), D3D11_USAGE_DYNAMIC, 0);

	// Int
	CDevice::GetInst()->CreateConstBuffer
	(g_SPName[(UINT)SHADER_PARAM::SP_INT_END]
		, sizeof(int) *((UINT)SHADER_PARAM::SP_INT_END - (UINT)SHADER_PARAM::SP_INT_0)
		, D3D11_USAGE_DYNAMIC
		, g_SPRegister[(UINT)SHADER_PARAM::SP_INT_0]);

	// Float
	CDevice::GetInst()->CreateConstBuffer
	(g_SPName[(UINT)SHADER_PARAM::SP_FLOAT_END]
		, sizeof(float) *((UINT)SHADER_PARAM::SP_FLOAT_END - (UINT)SHADER_PARAM::SP_FLOAT_0)
		, D3D11_USAGE_DYNAMIC
		, g_SPRegister[(UINT)SHADER_PARAM::SP_FLOAT_0]);

	// Vec4
	CDevice::GetInst()->CreateConstBuffer
	(g_SPName[(UINT)SHADER_PARAM::SP_VEC4_END]
		, sizeof(Vec4) *((UINT)SHADER_PARAM::SP_VEC4_END - (UINT)SHADER_PARAM::SP_VEC4_0)
		, D3D11_USAGE_DYNAMIC
		, g_SPRegister[(UINT)SHADER_PARAM::SP_VEC4_0]);

	// Animation Info Buffer
	CDevice::GetInst()->CreateConstBuffer
	(L"AnimationInfo"
		, sizeof(tAnimInfo)
		, D3D11_USAGE_DYNAMIC
		, 13);

}
