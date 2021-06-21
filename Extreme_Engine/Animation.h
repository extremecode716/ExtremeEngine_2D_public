#pragma once

#include "global.h"

class CAnimator;

class CAnimation
{
protected:
	CAnimator *     m_pAnimator;
	wstring			m_strKey;
	bool			m_bActive;

	UINT			m_iCurFrame;
	float			m_fAccTime;
	bool			m_b2DAnim;

public:
	virtual int lateupdate() = 0;
	virtual void UpdateData() = 0;

public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	const wstring& GetKey() { return m_strKey; }
	void SetAnimator(CAnimator* _pAnimator) { m_pAnimator = _pAnimator; }
	void SetFrameIdx(UINT _iFrameIdx) { m_iCurFrame = _iFrameIdx; }
	UINT GetFrameIdx() const { return m_iCurFrame; }
	void SetActive(bool _bOn) { m_bActive = _bOn; }
	bool IsActive() { return m_bActive; }
	bool Is2DAnim() { return m_b2DAnim; }
	virtual bool Load(const wstring & _strFolderPath, const wstring& _strFullPath) = 0;
	
	virtual void  SetAnimTerm(float _fTerm) {};
	virtual float GetAnimTerm() { return 0.f; };
	virtual float GetAnimTerm(UINT _iFrameIdx) { return 0.f; };
	virtual UINT  GetMaxFrameIdx() const { return 0; };

public:
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

	virtual CAnimation* Clone() = 0;

public:
	CAnimation();
	virtual ~CAnimation();
};

