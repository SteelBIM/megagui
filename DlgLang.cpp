// DlgLang.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "DlgLang.h"
#include "afxdialogex.h"


// CDlgLang �Ի���

IMPLEMENT_DYNAMIC(CDlgLang, CDialogEx)

CDlgLang::CDlgLang(CWnd* pParent /*=NULL*/)
	 
{

}

CDlgLang::~CDlgLang()
{
}

void CDlgLang::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
//	DDX_CBIndex(pDX, IDC_COMBO_LAN, m_lang);
}


BEGIN_MESSAGE_MAP(CDlgLang, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgLang::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgLang ��Ϣ�������


void CDlgLang::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
