#include "DebugMgr.h"



CDebugMgr::CDebugMgr()
{
	//AllocConsole();
}


CDebugMgr::~CDebugMgr()
{
	//FreeConsole();
}



void CDebugMgr::Log(const wchar_t * _pLog)
{
	//_cwprintf(_pLog);
	//_cwprintf(L"\n");
#ifdef _EXTREME_TOOL
	SendMessage(CCore::GetInst()->GetMainWndHwnd(), MM_LOG, (WPARAM)_pLog, 0);
#endif
}

void CDebugMgr::Log(const wstring& _pLog)
{
	//_cwprintf(_pLog);
	//_cwprintf(L"\n");
#ifdef _EXTREME_TOOL
	SendMessage(CCore::GetInst()->GetMainWndHwnd(), MM_LOG, (WPARAM)_pLog.c_str(), 0);
#endif
}

wchar_t g_szLog[255] = {};
void CDebugMgr::Log(int _Log)
{
#ifdef _EXTREME_TOOL
	wmemset(g_szLog, 0, 255);
	wsprintf(g_szLog, L"%d", _Log);
	SendMessage(CCore::GetInst()->GetMainWndHwnd(), MM_LOG, (WPARAM)g_szLog, 0);
#endif
}

void CDebugMgr::Log(UINT _Log)
{
#ifdef _EXTREME_TOOL
	wmemset(g_szLog, 0, 255);
	wsprintf(g_szLog, L"%d", _Log);
	SendMessage(CCore::GetInst()->GetMainWndHwnd(), MM_LOG, (WPARAM)g_szLog, 0);
#endif
}

void CDebugMgr::Log(float _Log)
{
#ifdef _EXTREME_TOOL
	wmemset(g_szLog, 0, 255);
	swprintf(g_szLog, 255, L"%.3f", _Log);
	SendMessage(CCore::GetInst()->GetMainWndHwnd(), MM_LOG, (WPARAM)g_szLog, 0);
#endif
}