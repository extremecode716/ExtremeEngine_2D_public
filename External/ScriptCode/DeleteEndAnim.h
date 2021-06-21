#pragma once
#include "Script.h"


class CDeleteEndAnim :
	public CScript
{
	bool m_bAnim;

	bool m_bEnd;
	UINT m_iCount;
	UINT m_iMaxCount;
	UINT m_iAnimFrameIdex;
	UINT m_iAnimMaxFrameIdx;

public:
	void SetCount(UINT _iCount, UINT _iMaxCount) { m_iCount = _iCount; m_iMaxCount = _iMaxCount; }

public:
	virtual void start() override;
private:
	virtual int update() override;

public:
	virtual CDeleteEndAnim* Clone() override { return new CDeleteEndAnim(*this); }

public:
	CDeleteEndAnim();
	virtual ~CDeleteEndAnim();
};

