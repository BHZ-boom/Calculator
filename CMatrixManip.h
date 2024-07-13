#pragma once
#include "afxdialogex.h"
#include <vector>


// CMatrixManip 对话框

class CMatrixManip : public CDialogEx
{
	DECLARE_DYNAMIC(CMatrixManip)

public:
	CMatrixManip(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMatrixManip();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MATRIX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_A;
	CString m_B;
	CString m_C;
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonMul();
	void readMatrix();
	typedef std::vector<std::vector<long double>> Matrix;
	void Matrix2String(const Matrix& a, CString& b);
private:
	void readOneMatrix(const CString& input, Matrix& matrix);
	Matrix m_MA, m_MB;
};
