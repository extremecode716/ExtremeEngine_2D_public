#pragma once
#include "C:\Users\pc\Documents\Visual Studio 2015\Projects\ExtremeEngine\Extreme_Engine\Script.h"
class CScene_battleground2 :
	public CScript
{
private:
	CSound*		   m_pSound;
	FMOD::Channel* m_pChannel;

private:
	void CreatPortals();
	void PlaySound();

private:
	virtual void start() override;
	virtual int update() override { return RET_SUCCESS; }
public:
	virtual CScene_battleground2* Clone() override { return new CScene_battleground2(*this); }


public:
	CScene_battleground2();
	virtual ~CScene_battleground2();
};

