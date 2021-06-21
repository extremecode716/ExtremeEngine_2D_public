#pragma once
#include "afxwin.h"
#include "Material.h"

class CMaterial;
// CMaterialDlg 대화 상자입니다.

class CMaterialDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMaterialDlg)

public:
	CMaterialDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMaterialDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MATERIALDLG };
#endif

public:
	CMaterial*		m_pMtrl;
	tShaderParam_EX m_eShaderParamEx;
	void InitSP(CMaterial* _pMtrl ,const tShaderParam_EX& _eParmaEx);

	bool bFocusInfo;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditSPName;
	CEdit m_EditSPInfo;
	CButton m_bnTex;

	afx_msg void OnBnSPClicked();
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
//	afx_msg void OnMove(int x, int y);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnEnSetfocusEdit1();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	virtual void OnOK();
	virtual void OnCancel();
};
