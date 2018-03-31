#pragma once
#include "GlobalPara.h"

// CMeshGrid 对话框

class CMeshGrid : public CDialog
{
	DECLARE_DYNAMIC(CMeshGrid)

public:
	CMeshGrid(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMeshGrid();

// 对话框数据
	enum { IDD = IDD_MESH_GRID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	float m_con_mesh;
	float m_steel_mesh;
};
