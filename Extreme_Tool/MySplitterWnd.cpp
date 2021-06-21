// MySplitterWnd.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MySplitterWnd.h"


// CMySplitterWnd


CMySplitterWnd::CMySplitterWnd()
{

}

CMySplitterWnd::~CMySplitterWnd()
{
}

void CMySplitterWnd::SetBorderSize(CPoint _ptBorder, CPoint _ptGap)
{
	m_ptBorder = _ptBorder;
	m_ptGap = _ptGap;
}

BEGIN_MESSAGE_MAP(CMySplitterWnd, CSplitterWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CMySplitterWnd �޽��� ó�����Դϴ�.




int CMySplitterWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	m_cxBorder = m_ptBorder.x;
	m_cyBorder = m_ptBorder.y;

	m_cxSplitterGap = m_ptGap.x;
	m_cySplitterGap = m_ptGap.y;

	return 0;
}
