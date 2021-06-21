#pragma once
#include "Script.h"

class CScene_prontera
	: public CScript
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
	virtual CScene_prontera* Clone() override { return new CScene_prontera(*this); }

public:
	CScene_prontera();
	virtual ~CScene_prontera();
};

