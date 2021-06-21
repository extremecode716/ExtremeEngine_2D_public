#pragma once


// CMySplitterWnd

class CMySplitterWnd : public CSplitterWnd
{
private:
	CPoint  m_ptBorder;
	CPoint  m_ptGap;

public:
	void SetBorderSize(CPoint _ptBorder, CPoint _ptGap);


public:
	CMySplitterWnd();
	virtual ~CMySplitterWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


