#pragma once

#include "Core.h"

#define MM_LOG 5000

#ifdef _EXTREME_TOOL
#define SAVELOAD_DEBUG
#endif
class CDebugMgr
{
	SINGLE(CDebugMgr);
public:
	void Log(const wchar_t* _pLog);
	void Log(const wstring& _pLog);
	void Log(int _Log);
	void Log(UINT _Log);
	void Log(float _Log);
};

