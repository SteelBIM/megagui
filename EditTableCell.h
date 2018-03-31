#pragma once


// CEditTableCell
#include "MsgMacroHeader.h "
class CEditTableCell : public CEdit
{
	DECLARE_DYNAMIC(CEditTableCell)

public:
	CEditTableCell();
	virtual ~CEditTableCell();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChange();
	afx_msg void OnEnSetfocus();
};


