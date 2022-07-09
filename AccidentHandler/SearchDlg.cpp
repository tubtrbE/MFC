// SearchDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplicationAccidentHandler.h"
#include "SearchDlg.h"
#include "afxdialogex.h"


// SearchDlg 대화 상자

IMPLEMENT_DYNAMIC(SearchDlg, CDialogEx)

SearchDlg::SearchDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEARCHDLG, pParent),
	  sumL(0)
{

}

SearchDlg::~SearchDlg()
{
}

void SearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_searchList);
}


BEGIN_MESSAGE_MAP(SearchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONSUM, &SearchDlg::OnBnClickedButtonsum)
END_MESSAGE_MAP()


// SearchDlg 메시지 처리기


BOOL SearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
		// draw the lines 
	m_searchList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_searchList.InsertColumn(0, _T("순서"), LVCFMT_CENTER, 40);

	// column, text, alignment, width
	for (int i = 0; i < 12; i++) {
		int size;

		if (i == 0) {
			size = 60;
		}
		else if (i == 1) {
			size = 80;
		}
		else {
			size = 100;
		}
		m_searchList.InsertColumn(i + 1, PlaceString(i), LVCFMT_CENTER, size);
	}
	SetSearchTable();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

CString SearchDlg::PlaceString(int place) {

	if (place == 0) {
		return (CString)"시도";
	}
	else if (place == 1) {
		return (CString)"시군구";
	}
	else if (place == 2) {
		return (CString)"터널안";
	}
	else if (place == 3) {
		return (CString)"교량위";
	}
	else if (place == 4) {
		return (CString)"고가도로위";
	}
	else if (place == 5) {
		return (CString)"하차도(도로)";
	}
	else if (place == 6) {
		return (CString)"기타단일로";
	}
	else if (place == 7) {
		return (CString)"차로횡단보도";
	}
	else if (place == 8) {
		return (CString)"교차로부근";
	}
	else if (place == 9) {
		return (CString)"철길건널목";
	}
	else if (place == 10) {
		return (CString)"기타";
	}
	else if (place == 11) {
		return (CString)"불명";
	}
	else {
		return (CString)"범위를 벗어났습니다.";
	}

}


void SearchDlg::InputData(vector<Citys*> vCity)
{
	// TODO: 여기에 구현 코드 추가.
/*
	vector<Citys*> searchCity(vCity.size());

*/
//	searchCity.assign(vCity.begin(), vCity.end());
//	dlgPtr
		for (int i = 0; i < vCity.size(); i++) {
			if (dlgPtr->m_searchBox == (CString)vCity.at(i)->GetCity().c_str()) {
				searchCity.push_back(vCity.at(i));
			}
			if (dlgPtr->m_searchBox == (CString)vCity.at(i)->GetDistrict().c_str()) {
				searchCity.push_back(vCity.at(i));
			}
		}
}


void SearchDlg::SetSearchTable()
{

	/*
	*/
	// TODO: 여기에 구현 코드 추가.
	for (int i = 0; i < searchCity.size(); i++) {

		//'행' 과 '내용'
		CString str1;
		string tempCity = searchCity.at(i)->GetCity();
		string tempDistrict = searchCity.at(i)->GetDistrict();
		str1.Format(_T("%d"), i + 1);
		m_searchList.InsertItem(i, str1);

		m_searchList.SetItem(i, 1, LVIF_TEXT, (CString)tempCity.c_str(), NULL, NULL, NULL, NULL);
		m_searchList.SetItem(i, 2, LVIF_TEXT, (CString)tempDistrict.c_str(), NULL, NULL, NULL, NULL);
		for (int j = 0; j < 11; j++) {
			int inData = searchCity.at(i)->GetDeath()[j];
			CString csData;
			csData.Format(_T("%d"), inData);
			m_searchList.SetItem(i, j + 3, LVIF_TEXT, csData, NULL, NULL, NULL, NULL);
		}

		// '행', '열', 폰트, 내용
	}
	UpdateData(false);
}


void SearchDlg::OnBnClickedButtonsum()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int inData[11] = {};
	CString str1;

	str1.Format(_T("%d"), sumL + 1);
	dlgPtr->m_searchSumList.InsertItem(sumL, str1);
	dlgPtr->m_searchSumList.SetItem(sumL, 1, LVIF_TEXT, dlgPtr->m_searchBox, NULL, NULL, NULL, NULL);
	for (int i = 0; i < searchCity.size(); i++) {
		for (int j = 0; j < 11; j++) {
			inData[j] += searchCity.at(i)->GetDeath()[j];
		}
		for (int j = 0; j < 11; j++) {
			CString csData;
			csData.Format(_T("%d"), inData[j]);
			dlgPtr->m_searchSumList.SetItem(sumL, j + 2, LVIF_TEXT, csData, NULL, NULL, NULL, NULL);
		}
	}
	sumL++;
	UpdateData(false);
}


void SearchDlg::SetHandlerPtr(CMFCApplicationAccidentHandlerDlg* dlg)
{
	// TODO: 여기에 구현 코드 추가.
	// 부모의 포인터 값을 받는다.
	dlgPtr = (CMFCApplicationAccidentHandlerDlg*)dlg;

}
