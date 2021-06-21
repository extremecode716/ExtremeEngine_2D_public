#include "stdafx.h"
#include "ComponentDlg.h"


CComponentDlg::CComponentDlg()
	: m_pTargetObj(NULL)
{
}

CComponentDlg::CComponentDlg(UINT nIDTemplate, CWnd * pParent)
	: CDialogEx(nIDTemplate, pParent)
	, m_pTargetObj(NULL)
{
}

CComponentDlg::~CComponentDlg()
{
}

void CComponentDlg::OnCancel()
{
}

void CComponentDlg::OnOK()
{
}