#pragma once



// CGameView �� ���Դϴ�.

class CGameView : public CFormView
{
	DECLARE_DYNCREATE(CGameView)

protected:
	CGameView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate();
};


