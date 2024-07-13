// CMatrixManip.cpp: 实现文件
//

#include "pch.h"
#include "Calculator.h"
#include "afxdialogex.h"
#include "CMatrixManip.h"
#include <stdexcept>


// CMatrixManip 对话框

IMPLEMENT_DYNAMIC(CMatrixManip, CDialogEx)
typedef std::vector<std::vector<long double>> Matrix;
CMatrixManip::CMatrixManip(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MATRIX, pParent)
	, m_A(_T(""))
	, m_B(_T(""))
	, m_C(_T(""))
{

}

CMatrixManip::~CMatrixManip()
{
}

void CMatrixManip::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_A);
	DDX_Text(pDX, IDC_EDIT1, m_B);
	DDX_Text(pDX, IDC_EDIT3, m_C);
}


BEGIN_MESSAGE_MAP(CMatrixManip, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CMatrixManip::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CMatrixManip::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CMatrixManip::OnBnClickedButtonMul)
END_MESSAGE_MAP()


// CMatrixManip 消息处理程序

void CMatrixManip::readOneMatrix(const CString& input, Matrix& matrix)
{
    int pos = 0;
    CString token;
    CString delimiters = _T("\r\n"); // 列分隔符

    // 分割字符串为多个行
    CString rowString = input.Tokenize(delimiters, pos);
    while (pos != -1) {
        std::vector<long double> row;
        int rowPos = 0;
        CString rowDelimiter = _T(" "); // 行内元素分隔符
        CString element = rowString.Tokenize(rowDelimiter, rowPos);

        // 分割行为多个元素
        while (rowPos != -1) {
            long double num = _tcstold(element, NULL); // 转换CString到long double
            row.push_back(num);
            element = rowString.Tokenize(rowDelimiter, rowPos);
        }

        matrix.push_back(row);
        rowString = input.Tokenize(delimiters, pos);
    }
}

void CMatrixManip::readMatrix()
{
	UpdateData(TRUE);
    m_MA.clear();  // 清除现有内容
    m_MB.clear();  // 清除现有内容
    readOneMatrix(m_A, m_MA);
    readOneMatrix(m_B, m_MB);
}

void CMatrixManip::Matrix2String(const Matrix& a, CString& b)
{
    b = L"";
    for (int i = 0; i < a.size(); ++i) {
        if (i > 0) {
            b += _T("\r\n"); // 添加分号作为行的分隔符
        }
        for (int j = 0; j < a[i].size(); ++j) {
            if (j > 0) {
                b += _T(" "); // 添加空格作为元素的分隔符
            }
            CString number;
            number.Format(_T("%g"), a[i][j]); // 将数字转换为CString
            b += number;
        }
    }
}


void CMatrixManip::OnBnClickedButtonPlus()
{
    readMatrix();
    if (m_MA.size() != m_MB.size() || m_MA[0].size() != m_MB[0].size()) {
        throw std::invalid_argument("Matrices dimensions do not match.");
    }
    std::vector<std::vector<long double>> C(m_MA.size(), std::vector<long double>(m_MA[0].size()));
    for (size_t i = 0; i < m_MA.size(); i++) {
        for (size_t j = 0; j < m_MA[0].size(); j++) {
            C[i][j] = m_MA[i][j] + m_MB[i][j];
        }
    }
    Matrix2String(C, m_C);
    UpdateData(FALSE);
}


void CMatrixManip::OnBnClickedButtonMinus()
{
    readMatrix();
    if (m_MA.size() != m_MB.size() || m_MA[0].size() != m_MB[0].size()) {
        throw std::invalid_argument("Matrices dimensions do not match.");
    }
    std::vector<std::vector<long double>> C(m_MA.size(), std::vector<long double>(m_MA[0].size()));
    for (size_t i = 0; i < m_MA.size(); i++) {
        for (size_t j = 0; j < m_MA[0].size(); j++) {
            C[i][j] = m_MA[i][j] - m_MB[i][j];
        }
    }
    Matrix2String(C, m_C);
    UpdateData(FALSE);
}


void CMatrixManip::OnBnClickedButtonMul()
{
    readMatrix();
    if (m_MA[0].size() != m_MB.size()) {
        throw std::invalid_argument("Matrices dimensions do not allow multiplication.");
    }
    std::vector<std::vector<long double>> C(m_MA.size(), std::vector<long double>(m_MB[0].size(), 0));
    for (size_t i = 0; i < m_MA.size(); i++) {
        for (size_t j = 0; j < m_MB[0].size(); j++) {
            for (size_t k = 0; k < m_MA[0].size(); k++) {
                C[i][j] += m_MA[i][k] * m_MB[k][j];
            }
        }
    } 
    Matrix2String(C, m_C);
    UpdateData(FALSE);
}
