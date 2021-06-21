#pragma once



// CGameView 폼 뷰입니다.

class CGameView : public CFormView
{
	DECLARE_DYNCREATE(CGameView)

protected:
	CGameView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CGameView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	LRESULT ReceiveLog(WPARAM, LPARAM);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate();
};


