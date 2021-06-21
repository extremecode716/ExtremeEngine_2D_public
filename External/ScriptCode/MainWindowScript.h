#pragma once
#include "Script.h"
class CMainWindowScript :
	public CScript
{
private:
	// �ֽ� �������� ������Ʈ ���ֱ� ���� 39����.
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

