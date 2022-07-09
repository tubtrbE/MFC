#pragma once
#include <vector>
#include <algorithm>

#include "Citys.h"
#include "MFCApplicationAccidentHandlerDlg.h"
// SearchDlg 대화 상자

using std::vector;


class CMFCApplicationAccidentHandlerDlg;

class SearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SearchDlg)

public:
	SearchDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SearchDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCHDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_searchList;
	vector<Citys*> searchCity;

	// 표 그리기
	virtual BOOL OnInitDialog();
	// 정의할 함수
	// 데이터 를 받는다
	void InputData(vector<Citys*> vCity);
	// 표에 내용을 집어 넣는다.
	CString PlaceString(int place);
	int sumL;
	void SetSearchTable();
	afx_msg void OnBnClickedButtonsum();
	void SetHandlerPtr(CMFCApplicationAccidentHandlerDlg* dlg);
	CMFCApplicationAccidentHandlerDlg* dlgPtr;
};
