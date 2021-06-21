// DebugView.cpp : 구현 파일입니다.
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
	// 스크롤 자동 내리기
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


// CDebugView 진단입니다.

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


// CDebugView 메시지 처리기입니다.


void CDebugView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	// 두번 호출되기 때문에 강제적으로 1번만 호출되게 처리. PreCreate에서 한번 더 호출 됨으로
	static bool bInit = false;

	if (bInit)
		return;
	bInit = true;

}


int CDebugView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_Brush.CreateSolidBrush(RGB(120, 120, 120));   // Blue brush.

	return 0;
}


HBRUSH CDebugView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	CRect rect;
	if (pWnd->GetDlgCtrlID() == IDC_LIST1)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		hbr = m_Brush;
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
