#pragma once

class CPathMgr
{
private:
	static wchar_t m_szResPath[255];
	static wchar_t m_szExternalPath[255];
	static wchar_t m_szExt[20];
	static wchar_t m_szFileName[255];
	static wchar_t m_szFolderPath[511];


private:
	CPathMgr();
	~CPathMgr();

public:
	static void init();

public:
	static wchar_t* GetResPath() { return m_szResPath; }
	static wchar_t* GetExternalPath() { return m_szExternalPath; }
	static wchar_t* GetExt(const wchar_t* _pFileName);
	static wchar_t* GetFileName(const wchar_t* _pFilePath);
	static wchar_t* GetFolderPath(const wchar_t* _pFilePath);
};

