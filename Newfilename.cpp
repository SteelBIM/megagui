// Newfilename.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "Newfilename.h"
#include "afxdialogex.h"


// CNewfilename �Ի���

IMPLEMENT_DYNAMIC(CNewfilename, CDialog)

CNewfilename::CNewfilename(CWnd* pParent /*=NULL*/)
	: CDialog(CNewfilename::IDD, pParent)
	, m_filename(_T(""))
{

}

CNewfilename::~CNewfilename()
{
}

void CNewfilename::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FileName, m_filename);
}


BEGIN_MESSAGE_MAP(CNewfilename, CDialog)
	ON_BN_CLICKED(IDOK, &CNewfilename::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNewfilename::OnBnClickedCancel)
END_MESSAGE_MAP()


// CNewfilename ��Ϣ�������


void CNewfilename::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}


void CNewfilename::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
