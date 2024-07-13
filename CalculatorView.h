
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
	void evaluate(CString& expression, int mode);

private:
	template <typename T>
	T applyOp(T a, T b, wchar_t op);
	long double precedence(wchar_t op);
	void ConvertDouble(long double result, CString& input);
	
public:
	afx_msg void OnEnChangeEdit();
	afx_msg void OnBnClickedButtonPoint();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonAc();
	CButton m_FractionMode;
	afx_msg void OnBnClickedButtonslash();
	afx_msg void OnBnClickedButtonAdvance();
	afx_msg void OnBnClickedCheckFraction();
	afx_msg void OnStatDescribe();
	afx_msg void OnBnClickedButtonFile();
	afx_msg void OnStatRegress();
	afx_msg void OnStatMatrix();
	afx_msg void OnBnClickedButtonRightp();
	afx_msg void OnBnClickedButtonLeftp();
	afx_msg void OnBnClickedButtonE();
	afx_msg void OnBnClickedButtonPi();
	afx_msg void OnBnClickedButtonF();
	afx_msg void OnBnClickedButtonPow();
	afx_msg void OnBnClickedButtonLn();
	afx_msg void OnBnClickedButtonLg();
	afx_msg void OnBnClickedButtonSin();
	afx_msg void OnBnClickedButtonCos();
	afx_msg void OnBnClickedButtonTan();
	void checkVisibility(int nID);
};

#ifndef _DEBUG  // CalculatorView.cpp 中的调试版本
inline CCalculatorDoc* CCalculatorView::GetDocument() const
   { return reinterpret_cast<CCalculatorDoc*>(m_pDocument); }
#endif

