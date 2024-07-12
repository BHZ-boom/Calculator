// CDescribeStat.cpp: 实现文件
//

#include "pch.h"
#include <vector>
#include <unordered_map>
#include <cmath>
#include <numeric>
#include "Calculator.h"
#include "afxdialogex.h"
#include "CDescribeStat.h"


typedef std::vector<std::vector<long double>> DataTable;
typedef std::vector<CString> ColumnNames;
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
	DDX_Control(pDX, IDC_LIST_DATA, m_ListData);
}


BEGIN_MESSAGE_MAP(CDescribeStat, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDescribeStat::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_FILE, &CDescribeStat::OnBnClickedButtonFile)
END_MESSAGE_MAP()


// CDescribeStat 消息处理程序
// CMyDialog.cpp
BOOL CDescribeStat::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 设置List Control的样式为整行选择和网格线

	m_ListData.SetExtendedStyle(m_ListData.GetExtendedStyle() | 
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | WS_HSCROLL | WS_VSCROLL);

	// 添加列
	m_ListData.InsertColumn(0, _T("统计数据"), LVCFMT_LEFT, 100);
	

	// 添加行数据
	int nItem = m_ListData.InsertItem(0, _T("平均数"));
	//m_ListData.SetItemText(nItem, 1, _T("行1列2"));

	nItem = m_ListData.InsertItem(1, _T("中位数"));
	//m_ListData.SetItemText(nItem, 1, _T("行2列2"));

	nItem = m_ListData.InsertItem(2, _T("众数"));
	//m_ListData.SetItemText(nItem, 1, _T("行3列2"));
	nItem = m_ListData.InsertItem(3, _T("方差"));
	nItem = m_ListData.InsertItem(4, _T("标准差"));
	nItem = m_ListData.InsertItem(5, _T("极差"));
	nItem = m_ListData.InsertItem(6, _T("偏度"));
	nItem = m_ListData.InsertItem(7, _T("峰度"));
	
	return TRUE;  
}



void CDescribeStat::OnBnClickedOk()
{
	CDialogEx::OnOK();
}


void CDescribeStat::OnBnClickedButtonFile()
{
	// 创建一个CFileDialog实例，参数true表示为“打开文件”对话框，false为“保存文件”对话框
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("All Files (*.*)|*.*||"));

	// 显示对话框并等待用户响应
	CString dbFilePath;
	if (dlg.DoModal() == IDOK)
	{
		dbFilePath = dlg.GetPathName(); // 获取选择的文件路径
		// 可以在这里使用filePath，例如显示在一个文本框中或处理文件
	}
	CString dbLink = L"DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=" + dbFilePath;
	try {
		db.OpenEx(dbLink);
		CRecordset rs(&db);
		rs.Open(CRecordset::forwardOnly, _T("SELECT * FROM SHEET4"));
		// 获取列数
		short nFields = rs.GetODBCFieldCount();

		// 定义一个二维数组来存储数据
		DataTable dataTable(nFields);

		// 获取并储存列名
		ColumnNames columnNames(nFields);
		for (short i = 0; i < nFields; ++i) {
			CODBCFieldInfo fieldInfo;
			rs.GetODBCFieldInfo(i, fieldInfo);
			columnNames[i] = fieldInfo.m_strName;
		}

		// 遍历记录集并存储数据
		while (!rs.IsEOF()) {
			for (short i = 0; i < nFields; ++i) {
				long double fieldValue;
				CDBVariant varValue;
				rs.GetFieldValue(i, varValue);

				// 判断字段类型并转换为double
				switch (varValue.m_dwType) {
				case DBVT_LONG:
					fieldValue = static_cast<double>(varValue.m_lVal);
					break;
				case DBVT_SINGLE:
					fieldValue = static_cast<double>(varValue.m_fltVal);
					break;
				case DBVT_DOUBLE:
					fieldValue = varValue.m_dblVal;
					break;
				default:
					fieldValue = 0.0; // 默认值
					break;
				}
				dataTable[i].push_back(fieldValue);
			}
			rs.MoveNext();
		}

		// 求统计数据
		long double* mean = new long double[nFields];
		long double* median = new long double[nFields];
		long double* mode = new long double[nFields];
		long double* variance = new long double[nFields];
		long double* stdVariance = new long double[nFields];
		long double* range = new long double[nFields];
		long double* skewness = new long double[nFields];
		long double* kurtosis = new long double[nFields];

		// 求平均数
		for (short i = 0; i < nFields - 1; ++i) {
			long double sum = 0;
			for (const auto& data : dataTable[i + 1]) {
				sum += data;
			}
			mean[i] = sum / dataTable[i].size();
		}

		// 求中位数
		for (short i = 0; i < nFields - 1; ++i) {
			long double median = dataTable[i][dataTable[i].size() / 2];
		}

		// 求众数
		for (short i = 0; i < nFields - 1; ++i) {
			// 使用unordered_map来统计每个元素的出现次数
			std::unordered_map<long double, int> frequency;
			for (long double num : dataTable[i]) {
				frequency[num]++;
			}
			// 找到出现次数最多的元素
			long double Mode = dataTable[i][0];
			int max_count = 1;
			for (const auto& pair : frequency) {
				if (pair.second > max_count) {
					max_count = pair.second;
					Mode = pair.first;
				}
			}
			mode[i] = Mode;
		}

		// 求方差和标准差
		for (short i = 0; i < nFields - 1; ++i) {
			long double Variance = 0.0;
			for (double x : dataTable[i]) {
				Variance += (x - mean[i]) * (x - mean[i]);
			}
			variance[i] =  Variance / dataTable[i].size();
			stdVariance[i] = std::pow(variance[i], 0.5);
		}

		// 求偏度
		for (short i = 0; i < nFields - 1; ++i) {
			long double Skewness = 0;
			long double Kurtosis = 0;
			for (double x : dataTable[i]) {
				Skewness += std::pow((x - mean[i]) / stdVariance[i], 3);
				Kurtosis += std::pow((x - mean[i]) / stdVariance[i], 4);
			}
			skewness[i] = Skewness / dataTable[i].size();
			kurtosis[i] = Kurtosis / dataTable[i].size() - 3;
		}

		// 更新表格
		for (int i = 1; i < nFields - 1; i++) {
			m_ListData.InsertColumn(i, columnNames[i], LVCFMT_LEFT, 150);
		}
		
		for (int i = 0; i < nFields; i++) {
			CString strValue[7];
			strValue[0].Format(L"%lf", mean[i]);
			strValue[1].Format(L"%lf", median[i]);
			strValue[2].Format(L"%lf", mode[i]);
			strValue[3].Format(L"%lf", variance[i]);
			strValue[4].Format(L"%lf", stdVariance[i]);
			strValue[5].Format(L"%lf", skewness[i]);
			strValue[6].Format(L"%lf", kurtosis[i]);
			m_ListData.SetItemText(0, i + 1, strValue[0]);
			m_ListData.SetItemText(1, i + 1, strValue[1]);
			m_ListData.SetItemText(2, i + 1, strValue[2]);
			m_ListData.SetItemText(3, i + 1, strValue[3]);
			m_ListData.SetItemText(4, i + 1, strValue[4]);
			m_ListData.SetItemText(5, i + 1, strValue[5]);
			m_ListData.SetItemText(6, i + 1, strValue[6]);
		} 


		// 释放内存
		delete[] mean;
		delete[] median;
		delete[] mode;
		delete[] variance;
		delete[] stdVariance;
		delete[] range;
		delete[] skewness;
		delete[] kurtosis;
		
		// 关闭记录集和数据库连接
		rs.Close();
		db.Close();
	}
	catch (CDBException* e) {
		// 捕获数据库异常并显示错误信息
		CString errorMessage;
		errorMessage.Format(_T("Database error: %s"), e->m_strError);
		AfxMessageBox(errorMessage);
		e->Delete();
	}

	
}
