// ComListDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "ComListDlg.h"
#include "afxdialogex.h"


// CComListDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CComListDlg, CDialogEx)

CComListDlg::CComListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COMLISTDLG, pParent)
{

}

CComListDlg::~CComListDlg()
{
}

void CComListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbCom);
}


BEGIN_MESSAGE_MAP(CComListDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CComListDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CComListDlg 메시지 처리기입니다.


void CComListDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iSel = m_cbCom.GetCurSel();
	if (-1 == iSel)
		EndDialog(-1);
	else
	{
		switch (iSel)
		{
		case 0:
			iSel = (UINT)COMPONENT_TYPE::TRANSFORM;
			break;
		case 1:
			iSel = (UINT)COMPONENT_TYPE::MESHRENDER;
			break;
		case 2:
			iSel = (UINT)COMPONENT_TYPE::COLLIDER_2D;
			break;
		case 3:
			//iSel = (UINT)COMPONENT_TYPE::COLLIDER_3D;
			iSel = -1;
			break;
		case 4:
			iSel = (UINT)COMPONENT_TYPE::ANIMATOR;
			break;
		case 5:
			iSel = (UINT)COMPONENT_TYPE::CAMERA;
			break;
		case 6:
			iSel = (UINT)COMPONENT_TYPE::SCRIPT;
			break;
		}
		EndDialog(iSel);
	}

}

BOOL CComListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_cbCom.InsertString(0, L"TRANSFORM");
	m_cbCom.InsertString(1, L"MESHRENDER");
	m_cbCom.InsertString(2, L"COLLIDER_2D");
	m_cbCom.InsertString(3, L"COLLIDER_3D");
	m_cbCom.InsertString(4, L"ANIMATOR");
	m_cbCom.InsertString(5, L"CAMERA");
	m_cbCom.InsertString(6, L"SCRIPT");

	return TRUE;
}

void CComListDlg::OnCancel()
{
	EndDialog(-1);
}
