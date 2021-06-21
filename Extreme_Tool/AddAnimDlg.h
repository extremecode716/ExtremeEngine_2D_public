#pragma once

#include "afxcmn.h"
#include "afxwin.h"

// CAddAnimDlg ��ȭ �����Դϴ�.
class CGameObject;

class CAddAnimDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddAnimDlg)

public:
	CAddAnimDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAddAnimDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDANIMDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

private:
	CGameObject* m_pTarget;

private:
	void SetContinue(BOOL _bContinue);

public:
	void SetTarget(CGameObject* _pTarget) { m_pTarget = _pTarget; }

private:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClicked();
	afx_msg void OnContinueBnClicked();

private:
	CString	m_strFolderPath;
	CString m_strTexName;
	CString m_strAnimName;

	BOOL m_bContinue;
	CListCtrl m_List;

	CEdit m_editTexCount;
	CEdit m_editFrameCount;
	CEdit m_editLT;
	CEdit m_editRT;
	CEdit m_editSizeX;
	CEdit m_editSizeY;

};
