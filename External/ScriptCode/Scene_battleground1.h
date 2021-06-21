#pragma once
#include "Script.h"
class CScene_battleground1 :
	public CScript
{
private:
	CSound*		   m_pSound;
	FMOD::Channel* m_pChannel;

private:
	void CreatPortals();
	void SoundPlay();

private:
	virtual void start() override;
	virtual int update() override { return RET_SUCCESS; }
public:
	virtual CScene_battleground1* Clone() override { return new CScene_battleground1(*this); }

public:
	CScene_battleground1();
	virtual ~CScene_battleground1();
};

