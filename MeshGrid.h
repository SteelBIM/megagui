#pragma once
#include "GlobalPara.h"

// CMeshGrid �Ի���

class CMeshGrid : public CDialog
{
	DECLARE_DYNAMIC(CMeshGrid)

public:
	CMeshGrid(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMeshGrid();

// �Ի�������
	enum { IDD = IDD_MESH_GRID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	float m_con_mesh;
	float m_steel_mesh;
};
