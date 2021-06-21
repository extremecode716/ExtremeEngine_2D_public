#include "Animator.h"

#include "Animation_2D.h"
#include "Device.h"
#include "PathMgr.h"

// PathFileExists
#include "shlwapi.h"
#pragma comment(lib, "Shlwapi.lib")


CAnimator::CAnimator()
	: m_pCurAnim(NULL)
	, m_bRepeat(true)
{
}

CAnimator::CAnimator(const CAnimator & _other)
	:  m_bRepeat(_other.m_bRepeat)
{
	map<wstring, CAnimation*>::const_iterator iter = _other.m_mapAnim.begin();
	for (; iter != _other.m_mapAnim.end(); ++iter)
	{
		CAnimation* pAnim = iter->second->Clone();
		pAnim->SetAnimator(this);
		m_mapAnim.insert(make_pair(iter->first, pAnim));
	}

	// CurAnim setting
	if (_other.m_pCurAnim != NULL)
	{
		wstring strCurAnim = _other.m_pCurAnim->GetKey();
		PlayAnimation(strCurAnim, m_bRepeat);
	}
}

CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}


void CAnimator::PlayAnimation(const wstring & _strKey, bool _bRepeat, UINT _iStartFrameIdx)
{
	m_bRepeat = _bRepeat;

	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strKey);

	if (iter != m_mapAnim.end())
	{
		m_pCurAnim = iter->second;
		m_pCurAnim->SetActive(true);
		m_pCurAnim->SetFrameIdx(_iStartFrameIdx);
	}
}

bool CAnimator::IsPlayAnimation(const wstring & _strKey)
{
	if (_strKey == m_pCurAnim->GetKey())
		return true;
	return false;
}

void CAnimator::ChangeAnimation(const wstring & _strKey, UINT _iStartFrameIdx)
{
	CAnimation* pAnim = FindAnimation(_strKey);

	if (NULL == pAnim)
		return;

	m_pCurAnim = pAnim;
	m_pCurAnim->SetFrameIdx(_iStartFrameIdx);
}

void CAnimator::ChangeAnimation(CAnimation * _pAnim, UINT _iStartFrameIdx)
{
	CAnimation* pAnim = FindAnimation(_pAnim);

	if (NULL == pAnim)
		return;

	m_pCurAnim = pAnim;
	m_pCurAnim->SetFrameIdx(_iStartFrameIdx);
}

void CAnimator::UpdateData()
{
	if (NULL != m_pCurAnim)
	{
		m_pCurAnim->UpdateData();
	}
}


int CAnimator::lateupdate()
{
	if (NULL != m_pCurAnim)
	{
		m_pCurAnim->lateupdate();
		if (false == m_pCurAnim->IsActive() && m_bRepeat)
		{
			m_pCurAnim->SetFrameIdx(0);
			m_pCurAnim->SetActive(true);
		}
	}

	return 0;
}

void CAnimator::LoadAnimation_2D(const wstring & _strFolderPath)
{
	wstring strFullPath = CPathMgr::GetResPath();
	strFullPath += _strFolderPath;

	CAnimation_2D::LoadMultiAnimation(_strFolderPath, strFullPath, m_mapAnim);
}

void CAnimator::LoadAnimation_2D(const tDescInfo * _pInfo, const wstring& _strFolderPath)
{
	CAnimation_2D* pAnim = CAnimation_2D::FromDescToAnimation(*_pInfo, _strFolderPath);

	pAnim->SetKey(_pInfo->strAnimName);
	pAnim->SetAnimator(this);
	m_mapAnim.insert(make_pair(_pInfo->strAnimName, pAnim));
}

void CAnimator::Disable()
{
	tAnimInfo tInfo = {};
	tInfo.vAnim.x = 0;

	const CBUFFER* pBuffer = CDevice::GetInst()->FindConstBuffer(L"AnimationInfo");

	// 상수버퍼로 데이터 옮김
	D3D11_MAPPED_SUBRESOURCE tSub = {};

	CONTEXT->Map(pBuffer->pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, &tInfo, pBuffer->iSize);
	CONTEXT->Unmap(pBuffer->pBuffer, 0);

	CONTEXT->VSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);
	CONTEXT->HSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);
	CONTEXT->DSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);
	CONTEXT->CSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);
	CONTEXT->GSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);
	CONTEXT->PSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);
}
wstring CAnimator::GetCurAnimKey() const
{
	return m_pCurAnim->GetKey();
}
void CAnimator::PushAnimations(vector<tAnimPair>& _vecOut)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();;

	for (; iter != m_mapAnim.end(); ++iter)
	{
		_vecOut.push_back(tAnimPair{ iter->first, iter->second });
	}
}

CAnimation * CAnimator::FindAnimation(const wstring & _strKey)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strKey);

	if (iter == m_mapAnim.end())
		return NULL;

	return iter->second;
}

CAnimation * CAnimator::FindAnimation(CAnimation * _pAnim)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();

	for (; iter != m_mapAnim.end(); ++iter)
	{
		if (iter->second == _pAnim)
		{
			return iter->second;
		}
	}

	return NULL;
}

void CAnimator::RemoveAnimation(const wstring& _strKey)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();

	for (; iter != m_mapAnim.end();)
	{
		if (iter->second->GetKey() == _strKey)
		{
			SAFE_DELETE(iter->second);
			iter = m_mapAnim.erase(iter);
			m_pCurAnim = NULL;
			break;
		}
		else
		{
			++iter;
		}
	}

}

void CAnimator::Save(FILE * _pFile)
{
	UINT iType = (UINT)COMPONENT_TYPE::ANIMATOR;
	fwrite(&iType, sizeof(iType), 1, _pFile);

	UINT iCount = m_mapAnim.size();
	fwrite(&iCount, sizeof(UINT), 1, _pFile);

	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();
	for (; iter != m_mapAnim.end(); ++iter)
	{
		bool b2D = iter->second->Is2DAnim();
		fwrite(&b2D, 1, 1, _pFile);
		iter->second->Save(_pFile);
	}

	fwrite(&m_bRepeat, 1, 1, _pFile);
	SaveResourceKey(m_pCurAnim, _pFile);
}

void CAnimator::Load(FILE * _pFile)
{
	UINT iCount = 0;
	fread(&iCount, sizeof(UINT), 1, _pFile);

	CAnimation* pAnim = NULL;
	for (UINT i = 0; i < iCount; ++i)
	{
		bool b2D = false;
		fread(&b2D, 1, 1, _pFile);

		if (b2D)
			pAnim = new CAnimation_2D;
		else
		{
			//pAnim = new CAnimation_3D;			
		}
		pAnim->Load(_pFile);
		pAnim->SetAnimator(this);
		m_mapAnim.insert(make_pair(pAnim->GetKey(), pAnim));
	}

	fread(&m_bRepeat, 1, 1, _pFile);
	wstring strKey = LoadResourceKey(_pFile);
	PlayAnimation(strKey, m_bRepeat);
}
