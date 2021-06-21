// MySplitterWnd.cpp : 구현 파일입니다.
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



// CMySplitterWnd 메시지 처리기입니다.




int CMySplitterWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_cxBorder = m_ptBorder.x;
	m_cyBorder = m_ptBorder.y;

	m_cxSplitterGap = m_ptGap.x;
	m_cySplitterGap = m_ptGap.y;

	return 0;
}
