#pragma once
#include "afxdialogex.h"

class CGameObject;

class CComponentDlg :
	public CDialogEx
{
protected:
	CGameObject*	m_pTargetObj;

public:
	virtual void UpdateComponent(CGameObject* _pObj) = 0;
	void InitTarget() { m_pTargetObj = NULL; }

public:
	CComponentDlg();
	CComponentDlg(UINT nIDTemplate, CWnd *pParent = NULL);
	virtual ~CComponentDlg();
	virtual void OnCancel();
	virtual void OnOK();
};

