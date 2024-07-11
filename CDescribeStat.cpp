// CDescribeStat.cpp: 实现文件
//

#include "pch.h"
#include "Calculator.h"
#include "afxdialogex.h"
#include "CDescribeStat.h"


// CDescribeStat 对话框

IMPLEMENT_DYNAMIC(CDescribeStat, CDialogEx)

CDescribeStat::CDescribeStat(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DESCRIBE, pParent)
{

}

CDescribeStat::~CDescribeStat()
{
}

void CDescribeStat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDescribeStat, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDescribeStat::OnBnClickedOk)
END_MESSAGE_MAP()


// CDescribeStat 消息处理程序
// CMyDialog.cpp
BOOL CDescribeStat::OnInitDialog()
{
	CDialog::OnInitDialog();
	db.Open(_T("企业数据"));
	// 在这里添加初始化代码
	// 例如设置控件的初始状态，加载数据等

	return TRUE;  // return TRUE 除非你将焦点设置到控件
}



void CDescribeStat::OnBnClickedOk()
{
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, _T("SELECT * FROM SHEET4"));
	// 检查是否有记录返回
	if (!rs.IsEOF()) {
		// 定义一个变量来存储第一个属性的值
		CString strValue;

		// 获取第一个属性的值
		rs.GetFieldValue((short)0, strValue);

		// 输出结果
		AfxMessageBox(strValue);
	}
	else {
		AfxMessageBox(_T("No records found."));
	}

	// 关闭记录集和数据库连接
	rs.Close();
	db.Close();
	CDialogEx::OnOK();
}
