// EditTableHeader.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "EditTableHeader.h"
#include "MsgMacroHeader.h"


// CEditTableHeader
#define EDITINDEX_BK_SELECTED RGB(255,69,0)
#define EDITINDEX_TEXT_SELECTED RGB(255,255,255)

IMPLEMENT_DYNAMIC(CEditTableIndex, CEdit)

CEditTableIndex::CEditTableIndex()
{
	m_bSelected = false;
	m_hbrEditBk = ::CreateSolidBrush(EDITINDEX_BK_SELECTED);
}

CEditTableIndex::~CEditTableIndex()
{
}


BEGIN_MESSAGE_MAP(CEditTableIndex, CEdit)
	//ON_WM_CTLCOLOR()
	ON_WM_CTLCOLOR_REFLECT()
	ON_CONTROL_REFLECT(EN_KILLFOCUS, &CEditTableIndex::OnEnKillfocus)
	ON_CONTROL_REFLECT(EN_SETFOCUS, &CEditTableIndex::OnEnSetfocus)
END_MESSAGE_MAP()



// CEditTableHeader 消息处理程序




HBRUSH CEditTableIndex::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CEdit::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}


HBRUSH CEditTableIndex::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  在此更改 DC 的任何特性
	
	if (nCtlColor==CTLCOLOR_STATIC)
	{
		if (m_bSelected)
		{
			pDC->SetTextColor(EDITINDEX_TEXT_SELECTED);
			pDC->SetBkMode(TRANSPARENT);
			return m_hbrEditBk;
		}
		return NULL;
	}

	return NULL;
}

void CEditTableIndex::SetSelected( bool bSel,bool bRedraw/*=false*/ )
{
	m_bSelected = bSel;
	if (bRedraw)
	{
		RedrawWindow();
	}
}


void CEditTableIndex::OnEnKillfocus()
{
	//SetSelected(false);
}


void CEditTableIndex::OnEnSetfocus()
{
	//SetSelected(true);
	if (GetParent())
	{
		GetParent()->SendMessage(EDITINDEXMSG_SELECTED,GetDlgCtrlID(),0);
	}
}
