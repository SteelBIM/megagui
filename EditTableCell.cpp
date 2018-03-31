// EditTableCell.cpp : ʵ���ļ�
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



// CEditTableCell ��Ϣ�������




void CEditTableCell::OnEnChange()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CEdit::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
