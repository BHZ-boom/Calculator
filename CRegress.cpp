// CRegress.cpp: 实现文件
//

#include "pch.h"
#include "Calculator.h"
#include "afxdialogex.h"
#include "CRegress.h"


// CRegress 对话框

IMPLEMENT_DYNAMIC(CRegress, CDialogEx)

CRegress::CRegress(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_REGRESS, pParent)
{

}

CRegress::~CRegress()
{
}

void CRegress::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRegress, CDialogEx)
END_MESSAGE_MAP()


// CRegress 消息处理程序
