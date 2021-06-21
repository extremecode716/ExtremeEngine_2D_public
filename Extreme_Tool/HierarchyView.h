#pragma once



// CHierarchyView �� ���Դϴ�.

class CHierarchyDlg;
class CResDlg;

class CHierarchyView : public CFormView
{
	DECLARE_DYNCREATE(CHierarchyView)

protected:
	CHierarchyView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CHierarchyView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HIERARCHYVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
private:
	CHierarchyDlg*	m_pHierarchyDlg;
	CResDlg*		m_pResDlg;

public:
	void Init();

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	virtual void OnInitialUpdate();
};


