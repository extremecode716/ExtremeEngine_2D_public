// CodeGen.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

#include "pathMgr.h"

vector<wstring> g_vecName1;
vector<wstring> g_vecName2;

int main()
{
	CPathMgr::init();
	wstring strExternalPath = CPathMgr::GetExternalPath();
	wstring strScriptMgr = strExternalPath + L"ScriptMgr.cpp";

	// 1. 현재 존재하는 모든 스크립트를 알아내야함.
	wstring strScriptCode = strExternalPath + L"ScriptCode";
	wstring strMgrScriptCode = strExternalPath + L"ScriptMgr\\View";

	// ScriptCode Find ////////
	WIN32_FIND_DATA tData1 = {};
	HANDLE handle1 = FindFirstFile(wstring(strScriptCode + L"\\*.h").c_str(), &tData1);

	if (INVALID_HANDLE_VALUE == handle1)
		return 0;

	while (true)
	{
		g_vecName1.push_back(wstring(tData1.cFileName).substr(0, wcslen(tData1.cFileName) - 2));
		if (!FindNextFile(handle1, &tData1))
			break;
	}

	FindClose(handle1);
	/////////////////////////
	// MgrScriptCode Find/////
	WIN32_FIND_DATA tData2 = {};
	HANDLE handle2 = FindFirstFile(wstring(strMgrScriptCode + L"\\*.h").c_str(), &tData2);

	if (INVALID_HANDLE_VALUE == handle2)
		return 0;

	while (true)
	{
		g_vecName2.push_back(wstring(tData2.cFileName).substr(0, wcslen(tData2.cFileName) - 2));
		if (!FindNextFile(handle2, &tData2))
			break;
	}

	FindClose(handle2);
	///////////////////////////

	FILE* pFile = NULL;

	_wfopen_s(&pFile, strScriptMgr.c_str(), L"w");

	// 헤더 입력
	fwprintf_s(pFile, L"#include \"stdafx.h\"\n");
	fwprintf_s(pFile, L"#include \"ScriptMgr.h\"\n\n");

	for (UINT i = 0; i < g_vecName1.size(); ++i)
	{
		fwprintf_s(pFile, L"#include \"ScriptCode\\");
		fwprintf_s(pFile, g_vecName1[i].c_str());
		fwprintf_s(pFile, L".h\"\n");
	}
	for (UINT i = 0; i < g_vecName2.size(); ++i)
	{
		fwprintf_s(pFile, L"#include \"ScriptMgr\\View\\");
		fwprintf_s(pFile, g_vecName2[i].c_str());
		fwprintf_s(pFile, L".h\"\n");
	}

	// 첫 번째 함수 작성
	fwprintf_s(pFile, L"\nvoid CScriptMgr::GetScriptInfo(vector<tScriptInfo>& _vec)\n{\n");

	for (UINT i = 0; i < g_vecName1.size(); ++i)
	{
		fwprintf_s(pFile, L"\t_vec.push_back(tScriptInfo{ L\"");
		fwprintf_s(pFile, g_vecName1[i].c_str());
		fwprintf_s(pFile, L"\", typeid(C");
		fwprintf_s(pFile, g_vecName1[i].c_str());
		fwprintf_s(pFile, L").hash_code() });\n");
	}
	fwprintf_s(pFile, L"}\n\n");


	// 두번째 함수 작성
	fwprintf_s(pFile, L"CScript * CScriptMgr::GetScript(DWORD _dwTypeId)\n{\n");

	for (UINT i = 0; i < g_vecName1.size(); ++i)
	{
		fwprintf_s(pFile, L"\tif (typeid(C");
		fwprintf_s(pFile, g_vecName1[i].c_str());
		fwprintf_s(pFile, L").hash_code() == _dwTypeId)\n");
		fwprintf_s(pFile, L"\t\treturn new C");
		fwprintf_s(pFile, g_vecName1[i].c_str());
		fwprintf_s(pFile, L";\n");
	}
	fwprintf_s(pFile, L"\treturn nullptr;\n}\n\n");


	// 세번째 함수 작성
	fwprintf_s(pFile, L"CScript * CScriptMgr::GetScript(const wstring& _strScriptName)\n{\n");

	for (UINT i = 0; i < g_vecName1.size(); ++i)
	{
		fwprintf_s(pFile, L"\tif (L\"");
		fwprintf_s(pFile, g_vecName1[i].c_str());
		fwprintf_s(pFile, L"\" == _strScriptName)\n");
		fwprintf_s(pFile, L"\t\treturn new C");
		fwprintf_s(pFile, g_vecName1[i].c_str());
		fwprintf_s(pFile, L";\n");
	}
	for (UINT i = 0; i < g_vecName2.size(); ++i)
	{
		fwprintf_s(pFile, L"\tif (L\"");
		fwprintf_s(pFile, g_vecName2[i].c_str());
		fwprintf_s(pFile, L"\" == _strScriptName)\n");
		fwprintf_s(pFile, L"\t\treturn new C");
		fwprintf_s(pFile, g_vecName2[i].c_str());
		fwprintf_s(pFile, L";\n");
	}
	fwprintf_s(pFile, L"\treturn nullptr;\n}\n\n");


	// 네번째 함수 작성
	fwprintf_s(pFile, L"const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)\n{\n");

	for (UINT i = 0; i < g_vecName1.size(); ++i)
	{
		fwprintf_s(pFile, L"\tif (NULL != dynamic_cast<C");
		fwprintf_s(pFile, g_vecName1[i].c_str());
		fwprintf_s(pFile, L"*>(_pScript))\n");
		fwprintf_s(pFile, L"\t\treturn L\"");
		fwprintf_s(pFile, g_vecName1[i].c_str());
		fwprintf_s(pFile, L"\";\n");
	}
	for (UINT i = 0; i < g_vecName2.size(); ++i)
	{
		fwprintf_s(pFile, L"\tif (NULL != dynamic_cast<C");
		fwprintf_s(pFile, g_vecName2[i].c_str());
		fwprintf_s(pFile, L"*>(_pScript))\n");
		fwprintf_s(pFile, L"\t\treturn L\"");
		fwprintf_s(pFile, g_vecName2[i].c_str());
		fwprintf_s(pFile, L"\";\n");
	}
	fwprintf_s(pFile, L"\treturn nullptr;\n}\n\n");

	fclose(pFile);

	return 0;
}