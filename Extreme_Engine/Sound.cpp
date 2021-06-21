#include "Sound.h"

FMOD::System* CSound::g_pSystem = NULL;

CSound::CSound()
	: m_pSound(NULL)
	, m_pChannel(NULL)
	, m_pBGMChannel(NULL)
	, m_bRepeat(false)
	, m_iCount(0)
{
}


CSound::~CSound()
{
	if (NULL != m_pSound)
	{
		m_pSound->release();
	}
}

FMOD::Channel* CSound::Play(int _iRepeatCount, bool _BGM, bool _bOverlap)
{
	if (_bOverlap == true)
	{
		if (m_pChannel != NULL)
		{
			bool bPlay;
			m_pChannel->isPlaying(&bPlay);
			if (bPlay == true)
			{
				Channel_Stop();
			}
		}
	}

	if (0 == _iRepeatCount)
		return NULL;
	else if (_iRepeatCount < -1)
		assert(NULL);

	if (_iRepeatCount == -1)
		m_bRepeat = true;
	else
	{
		_iRepeatCount -= 1;
		m_bRepeat = false;
	}

	if (_BGM == true)
	{
		g_pSystem->playSound(m_pSound, NULL, false, &m_pBGMChannel);

		m_pBGMChannel->setMode(FMOD_LOOP_NORMAL);
		m_pBGMChannel->setLoopCount(_iRepeatCount);
		m_pBGMChannel->setPriority(0);

		return m_pBGMChannel;
	}


	g_pSystem->playSound(m_pSound, NULL, false, &m_pChannel);
	m_pChannel->setMode(FMOD_LOOP_NORMAL);
	m_pChannel->setLoopCount(_iRepeatCount);
	m_pChannel->setPriority(128);


	return m_pChannel;

}

void CSound::Channel_Stop()
{
	if (NULL == m_pChannel)
		return;

	m_pChannel->stop();

}

CSound * CSound::Create(const wstring& _strFullPath)
{
	FMOD::Sound* pSound = NULL;

	string path(_strFullPath.begin(), _strFullPath.end());
	g_pSystem->createSound(path.c_str(), FMOD_DEFAULT, NULL, &pSound);

	CSound* pNew = new CSound;
	pNew->m_pSound = pSound;

	return pNew;
}
