// MegaMainData.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "MegaMainData.h"
#include "afxdialogex.h"
extern "C" void MegaMainDataDlg(){
	MegaMainData pDlg;
	pDlg.DoModal();
}

// MegaMainData �Ի���

IMPLEMENT_DYNAMIC(MegaMainData, CDialog)

MegaMainData::MegaMainData(CWnd* pParent /*=NULL*/)
	: CDialog(MegaMainData::IDD, pParent)
{

	m_bklen = 0.0f;
	m_lens = 0.0f;
	m_support = 0;
	m_stud_d = 0;
	m_stud_l = 0;
	m_stud_fu = 0.0f;
	m_stud_fy = 0.0f;
	m_aixal = 2;
	ifcantilever = false;
}

MegaMainData::~MegaMainData()
{
}

void MegaMainData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BKLEN, m_bklen);
	DDX_Text(pDX, IDC_LEN, m_lens);
	DDX_Radio(pDX, IDC_SIMPLESUPPORT, m_support);
	DDX_Text(pDX, IDC_STUD_D, m_stud_d);
	DDX_Text(pDX, IDC_STUD_L, m_stud_l);
	DDX_Text(pDX, IDC_STUD_FU, m_stud_fu);
	DDX_Text(pDX, IDC_STUD_FY, m_stud_fy);
	DDX_Radio(pDX, IDC_YY, m_aixal);
}


BEGIN_MESSAGE_MAP(MegaMainData, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &MegaMainData::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &MegaMainData::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_SIMPLESUPPORT, &MegaMainData::OnBnClickedSimplesupport)
	ON_BN_CLICKED(IDC_CANTILEVER, &MegaMainData::OnBnClickedCantilever)
	ON_EN_CHANGE(IDC_LEN, &MegaMainData::OnEnChangeLen)
END_MESSAGE_MAP()


// MegaMainData ��Ϣ�������


void MegaMainData::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GlobalPara::m_DesnPara.Lens = m_lens;
	GlobalPara::m_DesnPara.uL = m_bklen/m_lens;
	GlobalPara::m_DesnPara.Restrict = m_support+3;
// 	GlobalPara::m_DesnPara.stud_d = m_stud_d;
// 	GlobalPara::m_DesnPara.stud_len = m_stud_l;
// 	GlobalPara::m_DesnPara.stud_fu = m_stud_fu;
// 	GlobalPara::m_DesnPara.stud_fy = m_stud_fy;
	CDialog::OnOK();
}


void MegaMainData::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


BOOL MegaMainData::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_lens = GlobalPara::m_DesnPara.Lens;
	m_bklen = GlobalPara::m_DesnPara.uL*m_lens;
	m_stud_d = int(GlobalPara::m_DesnPara.stud_d);
	m_stud_l = int(GlobalPara::m_DesnPara.stud_len);
	m_stud_fu = GlobalPara::m_DesnPara.stud_fu;
	m_stud_fy = GlobalPara::m_DesnPara.stud_fy;
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_support = GlobalPara::m_DesnPara.Restrict-3;
	bitmap1.LoadBitmap(IDB_simplesupport);
	bitmap2.LoadBitmap(IDB_Cantilever);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void MegaMainData::OnBnClickedSimplesupport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 	UpdateData();
	 	CStatic* pst = (CStatic*)GetDlgItem(IDC_SUPPORT);
		pst->SetBitmap(bitmap1);
		m_bklen = m_lens;
		ifcantilever = false;
		UpdateData(FALSE);
	// 	}
	// 	else if(m_cursel==1){
	// 		pst->SetBitmap(bitmap2);
}


void MegaMainData::OnBnClickedCantilever()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CStatic* pst = (CStatic*)GetDlgItem(IDC_SUPPORT);
	pst->SetBitmap(bitmap2);
	m_bklen = 2*m_lens;
	ifcantilever = true;
	UpdateData(FALSE);

}


void MegaMainData::OnEnChangeLen()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(ifcantilever)
		m_bklen = 2*m_lens;
	else
		m_bklen = m_lens;
	UpdateData(FALSE);
}
