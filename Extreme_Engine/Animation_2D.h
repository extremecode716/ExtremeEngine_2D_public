#pragma once
#include "Animation.h"

#include "ResPtr.h"

class CTexture;

struct tFrameInfo
{
	CResPtr<CTexture>	pTex;
	Vec2				vLeftTop;
	float				fWidth;
	float				fHeight;
	float				fTerm;
};

struct tDescInfo
{
	wstring strTexName;
	wstring strAnimName;
	Vec2	vLeftTop;
	Vec2	vSize;
	UINT	iFrameCount;
	UINT	iContinue;
};

class CAnimation_2D :
	public CAnimation
{
private:
	vector<tFrameInfo>	m_vecFrame;

public:
	virtual int lateupdate();
	virtual void UpdateData();

public:
	virtual void SetAnimTerm(float _fTerm);
	virtual float GetAnimTerm();
	virtual float GetAnimTerm(UINT _iFrameIdx);
	virtual UINT  GetMaxFrameIdx() const { return m_vecFrame.size(); }

public:
	virtual bool Load(const wstring & _strFolderPath, const wstring& _strFullPath);
	static bool LoadMultiAnimation(const wstring& _strFolderPath
		, const wstring& _strFullPath, map<wstring, CAnimation*>& _mapAnim);

private:
	void AddFrame(const tFrameInfo& _tFrame) { m_vecFrame.push_back(_tFrame); }

public:
	static CAnimation_2D* FromDescToAnimation(const tDescInfo& _tDesc, const wstring& _strFolderPath);


	void Save(FILE* _pFile);
	void Load(FILE* _pFile);

public:
	virtual CAnimation_2D* Clone() { return new CAnimation_2D(*this); }
public:
	CAnimation_2D();
	virtual ~CAnimation_2D();
};

