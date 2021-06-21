#pragma once
#include "..\SingletonScript.h"
#include "..\External\DefineCode\Colleaque.h"

class CColleaque;
class CMediatorMgr :
	public CSingletonScript<CMediatorMgr>
{
protected:
	map<wstring, CColleaque*>   m_mapColleauque;

protected:
	bool AddColleaque(CColleaque* _collq);
	virtual void Mediate(const wstring& _strSrc, CMessage* _pData); // ALL
	virtual void Mediate_Find(const wstring& _strSrc, const wstring& _strDest, CMessage* _pData); // Find
	virtual void Mediate_ExceptMe(const wstring& _strSrc, CMessage* _pData); // ALL Except Me
	virtual void Mediate(const wstring& _strSrc, const wstring& _strDest, CMessage* _pData);  // One //Fast

public:
	CColleaque* FindColleaque(const wstring& _strKey);
	bool EraseCollq(const wstring& _strKey);

private:
	virtual int update() override { return RET_SUCCESS; }

public:
	CLONE(CMediatorMgr);

public:
	CMediatorMgr();
	explicit CMediatorMgr(const CMediatorMgr& _pOther) = default;
	virtual ~CMediatorMgr();

	friend class CColleaque;
};

