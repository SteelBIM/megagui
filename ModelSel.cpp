// ModelSel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "ModelSel.h"
#include "afxdialogex.h"
#include "ConBenGou.h"
#include "ProBenGou.h"
#include "Tools.h"

// CModelSel �Ի���

IMPLEMENT_DYNAMIC(CModelSel, CDialog)

CModelSel::CModelSel(CWnd* pParent /*=NULL*/)
	: CDialog(CModelSel::IDD, pParent)
{

}

CModelSel::~CModelSel()
{
}

void CModelSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelSel, CDialog)
	ON_BN_CLICKED(IDC_Con_Model, &CModelSel::OnBnClickedConModel)
	ON_BN_CLICKED(IDC_PRO_MODEL, &CModelSel::OnBnClickedProModel)
END_MESSAGE_MAP()


// CModelSel ��Ϣ�������


void CModelSel::OnBnClickedConModel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ConBenGou	pDlg;
	pDlg.DoModal();
	CDialog::OnOK();
}


void CModelSel::OnBnClickedProModel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ProBenGou pDlg;
	pDlg.DoModal();
	CDialog::OnOK();
}

BOOL CModelSel::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	HBITMAP hBitmap1,hBitmap2;
	hBitmap1 = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_CONMODEL));
	hBitmap2 = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_PROMODEL));
	((CButton*)GetDlgItem(IDC_Con_Model))->SetBitmap(hBitmap1);
	((CButton*)GetDlgItem(IDC_PRO_MODEL))->SetBitmap(hBitmap2);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
