#pragma once
#include "afxcmn.h"
//#include <Table.h>
#include "afxwin.h"


// MegaCombDlg �Ի���
struct CombForce_{		//ԭ����Ͻṹ
	float DeadPara;
	float LivePara1;
	float LivePara2;
	float LivePara3;
};

class MegaCombDlg : public CDialog
{
	DECLARE_DYNAMIC(MegaCombDlg)
	CArray<CombForce_,CombForce_&> aryDesnComb;
public:
	MegaCombDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MegaCombDlg();

// �Ի�������
	enum { IDD = IDD_MEGA_COMB };

private:
	void AutoGenCombi();		//�Զ��������

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnItemchangedLISTDeadLoad(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	int i_DeadP_CurSel;
	CListCtrl m_ObjectList;
	CSectTableInfo m_Tab;
	void SetList1();
	void SetList1Item(CListCtrl &list);
	void GetlistItem();
	afx_msg void OnBnClickedAutogen();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedRemove();


#pragma region  TABLE_EDIT
	//static const int s_nPosColumn;
	CEdit m_editWnd;


	int m_iBeingEdit;
	int m_iClickColum;

	enum {
		KILLFOCUS_NULL,
		KILLFOCUS_ESC,
		KILLFOCUS_OK,
		KILLFOCUS_OTHER
	};

	int m_loseFocusFrom;
	bool EditStarts();
	bool EditEnds(/*bool SaveText=true*/);
	bool EditSaveText();
	void OnEnKillfocusEditListwnd();
	void OnClickList(NMHDR *pNMHDR, LRESULT *pResult);
#pragma endregion 
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
//	float m_gsup;
	float m_rginf;
	float m_rgsup;
	float m_rq;
	float m_rq22;
	float m_rginf2;
	afx_msg void OnEnKillfocusrgsup();
	afx_msg void OnEnKillfocusrq();
	afx_msg void OnEnKillfocusrginf();
	afx_msg void OnEnKillfocusrq22();
	afx_msg void OnEnKillfocusrginf2();
	BOOL m_checkautobeta;
};
#pragma once


// Megacombdlg �Ի���

// class Megacombdlg : public CDialog
// {
// 	DECLARE_DYNAMIC(Megacombdlg)
// 
// public:
// 	Megacombdlg(CWnd* pParent = NULL);   // ��׼���캯��
// 	virtual ~Megacombdlg();
// 
// // �Ի�������
// 	enum { IDD = IDD_MEGA_COMB };
// 
// protected:
// 	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
// 
// 	DECLARE_MESSAGE_MAP()
// };
