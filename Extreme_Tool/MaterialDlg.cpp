// MaterialDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "MaterialDlg.h"
#include "afxdialogex.h"

#include "ListDlg.h"
#include "Texture.h"


// CMaterialDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMaterialDlg, CDialogEx)

CMaterialDlg::CMaterialDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MATERIALDLG, pParent)
	, m_pMtrl(NULL)
	, bFocusInfo(false)
{

}

CMaterialDlg::~CMaterialDlg()
{
}

void CMaterialDlg::InitSP(CMaterial* _pMtrl,const tShaderParam_EX& _eParmaEx)
{
	m_pMtrl = _pMtrl;
	m_eShaderParamEx = _eParmaEx;
	SHADER_PARAM eShaderParam = _eParmaEx.eShaderParam;

	m_bnTex.ShowWindow(false);
	UINT iSPNumber;
	switch (eShaderParam)
	{
	case SHADER_PARAM::SP_INT_0:
	case SHADER_PARAM::SP_INT_1:
	case SHADER_PARAM::SP_INT_2:
	case SHADER_PARAM::SP_INT_3:
	{
		iSPNumber = ((UINT)eShaderParam - (UINT)SHADER_PARAM::SP_INT_0);
		m_EditSPName.SetWindowTextW(wstring(L"SP_INT_" + to_wstring(iSPNumber)).c_str());
		int iData = *((int*)_eParmaEx.pData);
		m_EditSPInfo.SetWindowTextW(wstring(to_wstring(iData)).c_str());
	}
	break;
	case SHADER_PARAM::SP_FLOAT_0:
	case SHADER_PARAM::SP_FLOAT_1:
	case SHADER_PARAM::SP_FLOAT_2:
	case SHADER_PARAM::SP_FLOAT_3:
	{
		iSPNumber = ((UINT)eShaderParam - (UINT)SHADER_PARAM::SP_FLOAT_0);
		m_EditSPName.SetWindowTextW(wstring(L"SP_FLOAT_" + to_wstring(iSPNumber)).c_str());
		float fData = *((float*)_eParmaEx.pData);
		m_EditSPInfo.SetWindowTextW(wstring(to_wstring(fData)).c_str());
	}
	break;
	case SHADER_PARAM::SP_VEC4_0:
	case SHADER_PARAM::SP_VEC4_1:
	case SHADER_PARAM::SP_VEC4_2:
	case SHADER_PARAM::SP_VEC4_3:
	{
		iSPNumber = ((UINT)eShaderParam - (UINT)SHADER_PARAM::SP_VEC4_0);
		m_EditSPName.SetWindowTextW(wstring(L"SP_VEC4_" + to_wstring(iSPNumber)).c_str());
		Vec4 vec4Data = *((Vec4*)_eParmaEx.pData);
		CString strTotalData;
		CString strData;
		strData.Format(L"%.2f ", vec4Data.x);
		strTotalData += strData;
		strData.Format(L"%.2f ", vec4Data.y);
		strTotalData += strData;
		strData.Format(L"%.2f ", vec4Data.z);
		strTotalData += strData;
		strData.Format(L"%.2f ", vec4Data.w);
		strTotalData += strData;
		m_EditSPInfo.SetWindowTextW(strTotalData.GetBuffer());
	}
	break;
	case SHADER_PARAM::SP_TEX_0:
	case SHADER_PARAM::SP_TEX_1:
	case SHADER_PARAM::SP_TEX_2:
	case SHADER_PARAM::SP_TEX_3:
	{
		m_bnTex.ShowWindow(true);
		iSPNumber = ((UINT)eShaderParam - (UINT)SHADER_PARAM::SP_TEX_0);
		m_EditSPName.SetWindowTextW(wstring(L"SP_TEX_" + to_wstring(iSPNumber)).c_str());
		CTexture* pData = *((CTexture**)_eParmaEx.pData);
		if (NULL == pData) break;
		m_EditSPInfo.SetWindowTextW(wstring(pData->GetKey()).c_str());
		m_EditSPInfo.SetReadOnly();
	}
	break;
	default:
		break;
	}

	UpdateData(false);
}

void CMaterialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_EditSPName);
	DDX_Control(pDX, IDC_EDIT1, m_EditSPInfo);
	DDX_Control(pDX, IDC_BUTTON1, m_bnTex);
}


BEGIN_MESSAGE_MAP(CMaterialDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMaterialDlg::OnBnSPClicked)
//	ON_WM_MOVE()
ON_EN_CHANGE(IDC_EDIT1, &CMaterialDlg::OnEnChangeEdit1)
ON_EN_KILLFOCUS(IDC_EDIT1, &CMaterialDlg::OnEnKillfocusEdit1)
ON_EN_SETFOCUS(IDC_EDIT1, &CMaterialDlg::OnEnSetfocusEdit1)
ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CMaterialDlg 메시지 처리기입니다.

BOOL CMaterialDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();



	return TRUE;
}


void CMaterialDlg::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	delete this;
	CDialogEx::PostNcDestroy();
}


void CMaterialDlg::OnBnSPClicked()
{
	if (NULL == m_pMtrl) return;
	bool bTexShader = false;
	for (int i = (int)SHADER_PARAM::SP_TEX_0; i < (int)SHADER_PARAM::SP_TEX_END; ++i)
	{
		if (i == (int)m_eShaderParamEx.eShaderParam)
		{
			bTexShader = true;
			break;
		}
	}
	if (!bTexShader) return;
	CListDlg dlg;

	dlg.InitList(RESOURCE_TYPE::TEXTURE);

	CTexture* pTex = (CTexture*)dlg.DoModal();

	m_pMtrl->SetData(m_eShaderParamEx.eShaderParam, &pTex);
	InitSP(m_pMtrl, m_eShaderParamEx);
}




void CMaterialDlg::OnEnChangeEdit1()
{
	if (!bFocusInfo) return;
	CString str;
	m_EditSPInfo.GetWindowTextW(str);

	switch (m_eShaderParamEx.eShaderParam)
	{
	case SHADER_PARAM::SP_INT_0:
	case SHADER_PARAM::SP_INT_1:
	case SHADER_PARAM::SP_INT_2:
	case SHADER_PARAM::SP_INT_3:
	{
		int i = (int)_wtoi(str.GetBuffer());
		m_pMtrl->SetData(m_eShaderParamEx.eShaderParam, &i);
	}
	break;
	case SHADER_PARAM::SP_FLOAT_0:
	case SHADER_PARAM::SP_FLOAT_1:
	case SHADER_PARAM::SP_FLOAT_2:
	case SHADER_PARAM::SP_FLOAT_3:
	{
		float f = (float)_wtof(str.GetBuffer());
		m_pMtrl->SetData(m_eShaderParamEx.eShaderParam, &f);
	}
	break;
	default:
		break;
	}
}


void CMaterialDlg::OnEnKillfocusEdit1()
{
	bFocusInfo = false;
}


void CMaterialDlg::OnEnSetfocusEdit1()
{
	bFocusInfo = true;
}


void CMaterialDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_RETURN:
		::SetFocus(m_hWndOwner);
		break;
	default:
		break;
	}

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMaterialDlg::OnOK()
{

}


void CMaterialDlg::OnCancel()
{

}
