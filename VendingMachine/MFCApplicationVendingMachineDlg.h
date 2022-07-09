
// MFCApplicationVendingMachineDlg.h: 헤더 파일
//

#pragma once
#include "VendingMachine.h"


// CMFCApplicationVendingMachineDlg 대화 상자
class CMFCApplicationVendingMachineDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplicationVendingMachineDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATIONVENDINGMACHINE_DIALOG };
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
	afx_msg void OnBnClickedButtonadd100();
	afx_msg void OnBnClickedButtonadd500();
	afx_msg void OnBnClickedButtonbeverage1();
	afx_msg void OnBnClickedButtonbeverage2();
	afx_msg void OnBnClickedButtonbeverage3();
	afx_msg void OnBnClickedButtonbeverage4();
	afx_msg void OnBnClickedButtonreturn();
	CEdit m_moneyBox;
	CString m_textMessage;
	CString m_moneyBOX02;
	CString m_beverageText;
	BOOL m_handlerMode;
	int money;
	int flag_setting;

public:
	VendingMachine VM;
	CString beverageName;
	CString beverageStock;
	CString beveragePrice;

	afx_msg void OnBnClickedRadiohandler();
	afx_msg void OnBnClickedRadiocustomer();
};
