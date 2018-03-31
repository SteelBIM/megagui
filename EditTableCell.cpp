// EditTableCell.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "EditTableCell.h"
#include "MsgMacroHeader.h "

// CEditTableCell

IMPLEMENT_DYNAMIC(CEditTableCell, CEdit)

CEditTableCell::CEditTableCell()
{

}

CEditTableCell::~CEditTableCell()
{
}


BEGIN_MESSAGE_MAP(CEditTableCell, CEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, &CEditTableCell::OnEnChange)
	ON_CONTROL_REFLECT(EN_SETFOCUS, &CEditTableCell::OnEnSetfocus)
END_MESSAGE_MAP()



// CEditTableCell 消息处理程序




void CEditTableCell::OnEnChange()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CEdit::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (GetParent())
	{
		GetParent()->SendMessage(EDITMSG_CHANGED,GetDlgCtrlID(),0);
	}

}


void CEditTableCell::OnEnSetfocus()
{
	if (GetParent())
	{
		GetParent()->SendMessage(EDITMSG_SELECTED,GetDlgCtrlID(),0);
	}
}
