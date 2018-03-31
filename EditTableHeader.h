#pragma once
#include "Loaddef.h"


// CEditTableHeader

class CEditTableIndex : public CEdit
{
	DECLARE_DYNAMIC(CEditTableIndex)

public:
	CEditTableIndex();
	virtual ~CEditTableIndex();
private:
	HBRUSH m_hbrEditBk;



public:
	bool m_bSelected;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnEnKillfocus();
	afx_msg void OnEnSetfocus();

	void SetSelected(bool bSel,bool bRedraw=true);

};
