#pragma once
#include "afxdialogex.h"
#include <afxdb.h>


// CDescribeStat 对话框

class CDescribeStat : public CDialogEx
{
	DECLARE_DYNAMIC(CDescribeStat)

public:
	CDescribeStat(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDescribeStat();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DESCRIBE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CDatabase db;
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListData;
	CString m_dbLink;
	CString m_sheetName;
	afx_msg void OnBnClickedButtonFile();
	afx_msg void OnBnClickedButtonBegin();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonSave();
};
