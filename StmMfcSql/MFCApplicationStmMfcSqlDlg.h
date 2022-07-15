
// MFCApplicationStmMfcSqlDlg.h: 헤더 파일
// 

#define WM_QUERY WM_USER + 1

#pragma once
#include "SerialCom.h"	//추가 MrKang.
#include "CMysqlHandler.h"
#include "AdcValue.h"
#include <sstream>
#include <string>

using namespace std;

// CMFCApplicationStmMfcSqlDlg 대화 상자
class CMFCApplicationStmMfcSqlDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplicationStmMfcSqlDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATIONSTMMFCSQL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CSerialComm* m_comm;
	BOOL comport_state;
	CComboBox m_combo_comport_list;
	CComboBox m_combo_baudrate_list;
	CString m_str_comport;
	CString m_combo_baudrate;
	vector<char> vSerial;
	vector<string> vQuery;
	afx_msg void OnBnClickedButtonopen();
	afx_msg void OnCbnSelchangeComboComport();
	afx_msg void OnCbnSelchangeComboBaudrate();
	CListCtrl m_listAdc1;
	CListCtrl m_listAdc2;

	COleDateTime Time;

	//Make Uart ADC Value to Query
	string MakeQuery(string package);
	CString Make24Time(CString Time);

protected:
	afx_msg LRESULT OnReceive(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThreadClosed(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButtonload();

//	void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonsearch();
	COleDateTime m_startDate;
	COleDateTime m_startTime;
	COleDateTime m_endDate;
	COleDateTime m_endTime;
	CDateTimeCtrl m_startDateCtrl;
	CDateTimeCtrl m_startTimeCtrl;
	CDateTimeCtrl m_endDateCtrl;
	CDateTimeCtrl m_endTimeCtrl;

protected:

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDtnDatetimechangeDatetimepickerstartdate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerstarttime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerenddate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerendtime(NMHDR* pNMHDR, LRESULT* pResult);
};
