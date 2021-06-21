// DebugView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "DebugView.h"

#include "DebugMgr.h"
// CDebugView

IMPLEMENT_DYNCREATE(CDebugView, CFormView)

CDebugView::CDebugView()
	: CFormView(IDD_DEBUGVIEW)
{

}

CDebugView::~CDebugView()
{
}

void CDebugView::AddLog(DWORD_PTR _pLog)
{
	m_LogBox.AddString((LPCTSTR)_pLog);
	// ��ũ�� �ڵ� ������
	m_LogBox.SetTopIndex(m_LogBox.GetCount() - 1);
}

void CDebugView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_LogBox);
}

BEGIN_MESSAGE_MAP(CDebugView, CFormView)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDebugView �����Դϴ�.

#ifdef _DEBUG
void CDebugView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDebugView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDebugView �޽��� ó�����Դϴ�.


void CDebugView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	// �ι� ȣ��Ǳ� ������ ���������� 1���� ȣ��ǰ� ó��. PreCreate���� �ѹ� �� ȣ�� ������
	static bool bInit = false;

	if (bInit)
		return;
	bInit = true;

}


int CDebugView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	m_Brush.CreateSolidBrush(RGB(120, 120, 120));   // Blue brush.

	return 0;
}


HBRUSH CDebugView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	CRect rect;
	if (pWnd->GetDlgCtrlID() == IDC_LIST1)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		hbr = m_Brush;
	}

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}
