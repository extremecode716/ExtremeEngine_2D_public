#pragma once
#include "Script.h"
class CMainWindowScript :
	public CScript
{
private:
	// 최신 버전으로 업데이트 해주기 현재 39버전.
	wstring strNextScene;

private:
	CSound*		   m_pSound;
	FMOD::Channel* m_pChannel;

private:
	void SoundPlay();

private:
	virtual void awake() override;
	virtual int update() override;

public:
	CMainWindowScript* Clone() override { return new CMainWindowScript(*this); }
public:
	CMainWindowScript();
	virtual ~CMainWindowScript();
};

