#pragma once
// MFCApplicationAccidentHandlerDlg.h: 헤더 파일
//
#define LOADMSG WM_USER + 1

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Citys.h"
#include "SearchDlg.h"
class CMFCApplicationAccidentHandlerDlg;
using namespace std;

// CMFCApplicationAccidentHandlerDlg 대화 상자
class CMFCApplicationAccidentHandlerDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplicationAccidentHandlerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATIONACCIDENTHANDLER_DIALOG };
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

	vector<Citys*> vCity;
	CString m_searchBox;
	int selectIdx;
	CListCtrl m_accidentList;
	CListCtrl m_searchSumList;
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtondelete();
	afx_msg void OnBnClickedButtonload();
	
	CString PlaceString(int place);
	afx_msg void OnBnClickedButtonsearch();
	afx_msg void OnEnChangeEdit1();
	afx_msg LRESULT OnLoadMsg(WPARAM wParam, LPARAM lParam);
//	afx_msg LRESULT OnLoadMsg();

};
