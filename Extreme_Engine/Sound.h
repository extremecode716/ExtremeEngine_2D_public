#pragma once
#include "Res.h"
#include "fmod\fmod.h"
#include "fmod\fmod.hpp"
#include "fmod\fmod_codec.h"

#ifdef _DEBUG
#pragma comment(lib, "fmod_vc.lib")
#else
#pragma comment(lib, "fmodL_vc.lib")
#endif

class CSound :
	public CRes
{
public:
	static FMOD::System*	g_pSystem;

private:
	FMOD::Sound*   m_pSound;
	FMOD::Channel* m_pChannel;
	FMOD::Channel* m_pBGMChannel;
	bool		   m_bRepeat;

	int			   m_iCount;

public:
	FMOD::Channel* Play(int _iRepeatCount = -1, bool _BGM = false ,bool _bOverlap = false);
	void Channel_Stop();
	void Release()
	{
		if (NULL != m_pSound) m_pSound->release();
	}

private:
	static CSound* Create(const wstring& _strFullPath);

private:
	CLONE(CSound);

public:
	CSound();
	virtual ~CSound();

	friend class CResMgr;
};

