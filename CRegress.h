#pragma once
#include "afxdialogex.h"


// CRegress 对话框

class CRegress : public CDialogEx
{
	DECLARE_DYNAMIC(CRegress)

public:
	CRegress(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRegress();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REGRESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
