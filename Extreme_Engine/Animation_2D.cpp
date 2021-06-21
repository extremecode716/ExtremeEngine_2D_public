#include "Animation_2D.h"

#include "TimeMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"

#include "Device.h"

CAnimation_2D::CAnimation_2D()
{
	m_b2DAnim = true;
}

CAnimation_2D::~CAnimation_2D()
{
}

int CAnimation_2D::lateupdate()
{
	if (false == m_bActive)
	{
		//m_iCurFrame = 0;
		return RET_FAILED;
	}

	float fDT = CTimeMgr::GetInst()->DeltaTime();

	m_fAccTime += fDT;

	if (m_vecFrame[m_iCurFrame].fTerm <= m_fAccTime)
	{
		m_fAccTime = 0.f;
		m_iCurFrame += 1;

		if (m_vecFrame.size() <= m_iCurFrame)
		{
			m_iCurFrame = m_vecFrame.size() - 1;
			m_bActive = false;
		}
	}

	return RET_SUCCESS;
}

bool CAnimation_2D::Load(const wstring & _strFolderPath, const wstring& _strFullPath)
{
	WIN32_FIND_DATA	tData = {};

	HANDLE hHandle = FindFirstFile(wstring(_strFullPath + L"//" + L"*.*").c_str(), &tData);

	if (INVALID_HANDLE_VALUE == hHandle)
		return false;
	
	tFrameInfo info = {};

	do
	{
		CTexture* pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(tData.cFileName
			, wstring(_strFolderPath + L"\\" + tData.cFileName));

		if (NULL == pTex)
		{
			continue;
		}

		info.pTex = pTex;
		info.vLeftTop = Vec2(0.f, 0.f);
		info.fWidth = 1.f;
		info.fHeight = 1.f;
		info.fTerm = 0.09f;

		m_vecFrame.push_back(info);
	} while (FindNextFile(hHandle, &tData));

	FindClose(hHandle);
	return true;
}

bool CAnimation_2D::LoadMultiAnimation(const wstring & _strFolderPath
	, const wstring & _strFullPath
	, map<wstring, CAnimation*>& _mapAnim)
{
	wstring strFilePath = _strFullPath + L"\\desc.txt";
	FILE* pFile = NULL;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	wchar_t szBuff[255] = {};
	tDescInfo tInfo = {};
	vector<tDescInfo> vecInfo;

	while (true)
	{
		if (-1 == fwscanf_s(pFile, L"%s", szBuff, 255))
			break;

		if (!wcscmp(szBuff, L"[ANIMATION]"))
		{
			fwscanf_s(pFile, L"%s", szBuff, 255);
			tInfo.strTexName = szBuff;

			fwscanf_s(pFile, L"%d", &tInfo.iContinue);

			if (tInfo.iContinue)
			{
				int iMax = 0;
				fwscanf_s(pFile, L"%d", &tInfo.iFrameCount);

				fwscanf_s(pFile, L"%s", szBuff, 255);
				tInfo.strAnimName = szBuff;
			}
			else
			{
				fwscanf_s(pFile, L"%s", szBuff, 255);
				tInfo.strAnimName = szBuff;

				fwscanf_s(pFile, L"%f%f", &tInfo.vLeftTop.x, &tInfo.vLeftTop.y);
				fwscanf_s(pFile, L"%f%f", &tInfo.vSize.x, &tInfo.vSize.y);
				fwscanf_s(pFile, L"%d", &tInfo.iFrameCount);
			}

			vecInfo.push_back(tInfo);
		}
	}
	fclose(pFile);

	UINT iInfoSize = vecInfo.size();
	for (UINT i = 0; i < iInfoSize; ++i)
	{
		CAnimation_2D* pAnim = FromDescToAnimation(vecInfo[i], _strFolderPath);
		_mapAnim.insert(make_pair(pAnim->GetKey(), pAnim));
	}
	
	return true;
}


CAnimation_2D * CAnimation_2D::FromDescToAnimation(const tDescInfo & _tDesc, const wstring & _strFolderPath)
{
	CAnimation_2D* pAnim = new CAnimation_2D;

	wstring strFolderPath;
	if (-1 == _strFolderPath.find(CPathMgr::GetResPath()))
		strFolderPath = _strFolderPath;
	else
		strFolderPath = _strFolderPath.substr(wcslen(CPathMgr::GetResPath()), _strFolderPath.length());

	if (_tDesc.iContinue)
	{
		pAnim->SetKey(_tDesc.strAnimName);

		WIN32_FIND_DATA tData = {};
		HANDLE hHandle = FindFirstFile(wstring(CPathMgr::GetResPath() + strFolderPath + L"\\" + L"*.*").c_str(), &tData);

		if (INVALID_HANDLE_VALUE == hHandle)
			assert(NULL);

		while (true)
		{
			if (!wcscmp(_tDesc.strTexName.c_str(), tData.cFileName))
			{
				break;
			}

			if (!FindNextFile(hHandle, &tData))
				assert(NULL);
		}

		wstring strTexPath = strFolderPath + L"\\" + tData.cFileName;
		for (UINT j = 0; j < _tDesc.iFrameCount; ++j)
		{
			tFrameInfo tFrame = {};
			tFrame.vLeftTop = Vec2(0.f, 0.f);
			tFrame.fWidth = 1.f;
			tFrame.fHeight = 1.f;
			tFrame.fTerm = 0.09f;
			tFrame.pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(tData.cFileName, strTexPath.c_str());
			FindNextFile(hHandle, &tData);
			strTexPath = strFolderPath + L"\\" + tData.cFileName;

			pAnim->AddFrame(tFrame);
		}
		FindClose(hHandle);
	}
	else
	{
		CTexture* pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(_tDesc.strTexName, strFolderPath + L"//" + _tDesc.strTexName);
		pAnim->SetKey(_tDesc.strAnimName);

		for (UINT j = 0; j < _tDesc.iFrameCount; ++j)
		{
			tFrameInfo tFrame = {};
			tFrame.pTex = pTex;

			tFrame.vLeftTop.x = _tDesc.vLeftTop.x / pTex->GetWidth() + (j * _tDesc.vSize.x / pTex->GetWidth());
			tFrame.vLeftTop.y = _tDesc.vLeftTop.y / pTex->GetHeight();
			tFrame.fWidth = _tDesc.vSize.x / pTex->GetWidth();
			tFrame.fHeight = _tDesc.vSize.y / pTex->GetHeight();

			tFrame.fTerm = 0.09f;

			pAnim->AddFrame(tFrame);
		}
	}
	return pAnim;
}


void CAnimation_2D::UpdateData()
{
	tAnimInfo tInfo = {};
	tInfo.vAnim.x = 1;
	tInfo.vUV.x = m_vecFrame[m_iCurFrame].vLeftTop.x;
	tInfo.vUV.y = m_vecFrame[m_iCurFrame].vLeftTop.y;
	tInfo.vUV.z = m_vecFrame[m_iCurFrame].fWidth;
	tInfo.vUV.w = m_vecFrame[m_iCurFrame].fHeight;

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

	if (NULL != m_vecFrame[m_iCurFrame].pTex)
		m_vecFrame[m_iCurFrame].pTex->UpdateData(16, (UINT)SHADER_TYPE::ST_PIXEL);
}

void CAnimation_2D::SetAnimTerm(float _fTerm)
{
	for (UINT i = 0; i < m_vecFrame.size(); ++i)
	{
		m_vecFrame[i].fTerm = _fTerm;
	}
}

float CAnimation_2D::GetAnimTerm()
{
	return 	m_vecFrame[m_iCurFrame].fTerm;
}

float CAnimation_2D::GetAnimTerm(UINT _iFrameIdx)
{
	return 	m_vecFrame[_iFrameIdx].fTerm;
}


void CAnimation_2D::Save(FILE * _pFile)
{
	CAnimation::Save(_pFile);

	UINT iCount = m_vecFrame.size();
	fwrite(&iCount, sizeof(UINT), 1, _pFile);

	for (UINT i = 0; i < m_vecFrame.size(); ++i)
	{
		fwrite(&m_vecFrame[i].vLeftTop, sizeof(Vec2), 1, _pFile);
		fwrite(&m_vecFrame[i].fWidth, sizeof(float), 1, _pFile);
		fwrite(&m_vecFrame[i].fHeight, sizeof(float), 1, _pFile);
		fwrite(&m_vecFrame[i].fTerm, sizeof(float), 1, _pFile);

		SaveResourceKey(m_vecFrame[i].pTex.GetTarget(), _pFile);
	}
}

void CAnimation_2D::Load(FILE * _pFile)
{
	CAnimation::Load(_pFile);

	UINT iCount = 0;
	fread(&iCount, sizeof(UINT), 1, _pFile);

	tFrameInfo info = {};
	for (UINT i = 0; i < iCount; ++i)
	{
		fread(&info.vLeftTop, sizeof(Vec2), 1, _pFile);
		fread(&info.fWidth, sizeof(float), 1, _pFile);
		fread(&info.fHeight, sizeof(float), 1, _pFile);
		fread(&info.fTerm, sizeof(float), 1, _pFile);

		wstring strKey = LoadResourceKey(_pFile);
		if (!strKey.empty())
			info.pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(strKey);

		AddFrame(info);
	}
}

