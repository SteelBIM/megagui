#pragma once
#include "Resource.h"
#include "afxcmn.h"

// CDlgSectionList �Ի���

class CSectTableInfoColumn
{
public:
	CSectTableInfoColumn();
	virtual ~CSectTableInfoColumn();
	CSectTableInfoColumn(CString name,int format,int width);
	CString m_Name;
	int     m_nFormat;
	int     m_nWidth;
};


class CSectTableInfo  
{
public:
	CString m_TabName;
	int m_nCol;
	int m_nRow;
	void InitListCtrl(CListCtrl& list,int sel);
	CSectTableInfo();
	virtual ~CSectTableInfo();
	void Add(CString name,int format,int width);
	CArray<CSectTableInfoColumn,CSectTableInfoColumn&> m_Column;

};





class CDlgSectionList : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSectionList)

 
public:
	CDlgSectionList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSectionList();

// �Ի�������
	enum { IDD = IDD_DLG_SECT_LIST };

protected:
	CSectTableInfo m_TabInfo[10];
protected:
	int m_CurType;
	int m_CurSel;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	void InitLTreeListInfo();
public:
	CListCtrl c_ListR;
	virtual BOOL OnInitDialog();
	void FillListR(int nCurType,int nCurSel ,bool updateDateMember);

	void SetItemListR(int sel,bool updateDateMember);
	bool OnInitImage();
	bool FillTreeL();
	CImageList m_treeicons;
	CTreeCtrl c_treeL;
	afx_msg void OnSelchangedTreeL(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();

	void GetResult(int &Kd,int& sel);
	afx_msg void OnNMClickListR(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListR(NMHDR *pNMHDR, LRESULT *pResult);
};


