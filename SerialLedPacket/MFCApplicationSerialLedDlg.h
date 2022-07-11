
// MFCApplicationSerialLedDlg.h: 헤더 파일
//

#pragma once

#include "afxwin.h"

#include "SerialCom.h"	//추가 MrKang.
#include <vector>

using namespace std;

// CMFCApplicationSerialLedDlg 대화 상자
class CMFCApplicationSerialLedDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplicationSerialLedDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	/* 추가 부분  MrKang*/
	CSerialComm* m_comm;
	//LRESULT		OnThreadClosed(WPARAM length, LPARAM lpara);
	//LRESULT		OnReceive(WPARAM length, LPARAM lpara);
	/* 추가 부분 끝 MrKang*/

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATIONSERIALLED_DIALOG };
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

	BOOL comport_state;
	afx_msg void OnBnClickedButtonopen();
	afx_msg void OnBnClickedButtonclear();
	CComboBox m_combo_baudrate_list;
	CString m_combo_baudrate;
	CComboBox m_combo_comport_list;
	CString m_str_comport;
	afx_msg void OnCbnSelchangeComboComport();
	afx_msg void OnCbnSelchangeComboBaudrate();


	afx_msg void OnBnClickedButtonled1();
	afx_msg void OnBnClickedButtonled2();
	afx_msg void OnBnClickedButtonled3();
	CString m_led1;
	CString m_led2;
	CString m_led3;
protected:

	afx_msg LRESULT OnReceive(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThreadClosed(WPARAM wParam, LPARAM lParam);
public:

	vector <char> vSerial;
	CString m_ledStat1;
	CString m_ledStat2;
	CString m_ledStat3;
};
