#pragma once
#include "Component.h"

class CAnimation;

struct tDescInfo;

struct tAnimPair
{
	wstring			strKey;
	CAnimation*		pAnim;
};

class CAnimator :
	public CComponent
{
private:
	map<wstring, CAnimation*>		m_mapAnim;
	CAnimation*						m_pCurAnim;
	bool							m_bRepeat;

public:
	virtual int update() { return RET_SUCCESS; }
	virtual int lateupdate();

public:
	void LoadAnimation_2D(const wstring& _strFolderPath);
	void LoadAnimation_2D(const tDescInfo* _pInfo, const wstring& _strFolderPath);

	void PlayAnimation(const wstring& _strKey, bool _bRepeat = true, UINT _iStartFrameIdx = 0);
	bool IsPlayAnimation(const wstring& _strKey);
	void ChangeAnimation(const wstring& _strKey, UINT _iStartFrameIdx = 0);
	void ChangeAnimation(CAnimation* _pAnim, UINT _iStartFrameIdx = 0);
	void UpdateData();
	static void Disable();

	void PushAnimations(vector<tAnimPair>& _vecOut);
	CAnimation* GetCurAnim() const { return m_pCurAnim; }
	wstring GetCurAnimKey() const;
	bool IsRepeat() { return m_bRepeat; }
	void SetRepeat(bool _bTrue) { m_bRepeat = _bTrue; }

public:
	map<wstring, CAnimation*>& GetAnimMap() { return m_mapAnim; }

private:
	CAnimation * FindAnimation(const wstring& _strKey);
	CAnimation * FindAnimation(CAnimation* _pAnim);
	void RemoveAnimation(const wstring& _strKey);

	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

public:
	virtual CAnimator* Clone() { return new CAnimator(*this); }

public:
	CAnimator();
	CAnimator(const CAnimator& _other);
	virtual ~CAnimator();

	friend class CAnimatorDlg;
};

