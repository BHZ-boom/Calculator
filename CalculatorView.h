
// CalculatorView.h: CCalculatorView 类的接口
//
#pragma once

class CCalculatorView : public CFormView
{
protected: // 仅从序列化创建
	CCalculatorView() noexcept;
	DECLARE_DYNCREATE(CCalculatorView);

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_CALCULATOR_FORM };
#endif

// 特性
public:
	CCalculatorDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CCalculatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数与变量
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CString m_input;
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	CButton markTimes;
	CButton markDivision;
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonTimes();
	afx_msg void OnBnClickedButtonDivision();
	afx_msg void OnBnClickedButtonEqual();
	
public: //数据处理
	double applyOp(double a, double b, char op);
	double precedence(char op);
	double evaluate(CString& expression);
	
};

#ifndef _DEBUG  // CalculatorView.cpp 中的调试版本
inline CCalculatorDoc* CCalculatorView::GetDocument() const
   { return reinterpret_cast<CCalculatorDoc*>(m_pDocument); }
#endif

