#include "stdafx.h"
#include "DontDestoryAddScript.h"

CDontDestoryAddScript::CDontDestoryAddScript()
{
}


CDontDestoryAddScript::~CDontDestoryAddScript()
{
}

void CDontDestoryAddScript::start()
{
	////////////////
	// Dont Destory
	///////////////
	static bool bDont = false;
	if (bDont == true) return;
	CSceneMgr::GetInst()->DontDestroyOnLoad(GetGameObject());
	bDont = true;
}
