
// MFCApplicationVendingMachineDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplicationVendingMachine.h"
#include "MFCApplicationVendingMachineDlg.h"
#include "afxdialogex.h"
#include <string>
#include <sstream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplicationVendingMachineDlg 대화 상자



CMFCApplicationVendingMachineDlg::CMFCApplicationVendingMachineDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATIONVENDINGMACHINE_DIALOG, pParent)
	, m_textMessage(_T("")), money(0)
	, m_moneyBOX02(_T(""))
	, m_beverageText(_T(""))
	, m_handlerMode(FALSE)
	, flag_setting(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationVendingMachineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATICTEXT, m_textMessage);
	DDX_Control(pDX, IDC_EDITMONEYBOX, m_moneyBox);
	DDX_Text(pDX, IDC_EDITMONEYBOX, m_moneyBOX02);
	DDX_Text(pDX, IDC_STATICBEVERAGETEXT, m_beverageText);
	DDX_Radio(pDX, IDC_RADIOHANDLER, m_handlerMode);
}

BEGIN_MESSAGE_MAP(CMFCApplicationVendingMachineDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONADD100, &CMFCApplicationVendingMachineDlg::OnBnClickedButtonadd100)
	ON_BN_CLICKED(IDC_BUTTONADD500, &CMFCApplicationVendingMachineDlg::OnBnClickedButtonadd500)
	ON_BN_CLICKED(IDC_BUTTONBEVERAGE1, &CMFCApplicationVendingMachineDlg::OnBnClickedButtonbeverage1)
	ON_BN_CLICKED(IDC_BUTTONBEVERAGE2, &CMFCApplicationVendingMachineDlg::OnBnClickedButtonbeverage2)
	ON_BN_CLICKED(IDC_BUTTONBEVERAGE3, &CMFCApplicationVendingMachineDlg::OnBnClickedButtonbeverage3)
	ON_BN_CLICKED(IDC_BUTTONBEVERAGE4, &CMFCApplicationVendingMachineDlg::OnBnClickedButtonbeverage4)
	ON_BN_CLICKED(IDC_BUTTONRETURN, &CMFCApplicationVendingMachineDlg::OnBnClickedButtonreturn)
	ON_BN_CLICKED(IDC_RADIOHANDLER, &CMFCApplicationVendingMachineDlg::OnBnClickedRadiohandler)
	ON_BN_CLICKED(IDC_RADIOCUSTOMER, &CMFCApplicationVendingMachineDlg::OnBnClickedRadiocustomer)
END_MESSAGE_MAP()


// CMFCApplicationVendingMachineDlg 메시지 처리기

BOOL CMFCApplicationVendingMachineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplicationVendingMachineDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplicationVendingMachineDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplicationVendingMachineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplicationVendingMachineDlg::OnBnClickedButtonadd100()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	money += 100;
	m_moneyBOX02.Format(_T("%d"), money);
	m_textMessage.Format(_T("%d 원이 투입되었습니다."), money);
	UpdateData(false);
}


void CMFCApplicationVendingMachineDlg::OnBnClickedButtonadd500()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	money += 500;
	m_moneyBOX02.Format(_T("%d"), money);
	m_textMessage.Format(_T("%d 원이 투입되었습니다."), money);
	UpdateData(false);
}


void CMFCApplicationVendingMachineDlg::OnBnClickedButtonbeverage1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_handlerMode == TRUE) {
		int price = _ttoi(VM.BeverageGet(0)->GetPrice());
		int stock = _ttoi(VM.BeverageGet(0)->GetStock());

		UpdateData(true);
		if (money >= price) {
			money -= price;
			stock--;
			CString temp;
			temp.Format(_T("%d"), stock);

			VM.BeverageGet(0)->SetStock(temp);
			m_textMessage.Format(_T("%d 원을 사용합니다"), price);
			m_beverageText.Format(VM.BeverageGet(0)->GetName() + _T("를 내렸습니다."));
			m_moneyBOX02.Format(_T("%d"), money);
		}
		else {
			m_moneyBOX02.Format(_T("%d"), money);
			m_textMessage = _T("잔액이 부족합니다.");
			m_beverageText = _T(" ");
		}
		m_handlerMode = TRUE;
		UpdateData(false);
	}
	else {
		UpdateData(true);
		if (VM.BeverageGet(0) == nullptr) {
			m_textMessage = _T("음료 세팅값을 적어주십시요");
			m_beverageText = _T("name,price,stock");
			m_moneyBOX02 = "";
			flag_setting = 1;
		}
		else {
			CString strName = VM.BeverageGet(0)->GetName();
			CString strPrice = VM.BeverageGet(0)->GetPrice();
			CString strStock = VM.BeverageGet(0)->GetStock();
			CString N = _T("\r\n");

			m_moneyBOX02 = strName + N + strPrice + N + strStock;
		}

		m_handlerMode = FALSE;
		UpdateData(false);

	}
}




void CMFCApplicationVendingMachineDlg::OnBnClickedButtonbeverage2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	if (money >= 600) {
		money -= 600;
		m_moneyBOX02.Format(_T("%d"), money);
		m_textMessage.Format(_T("600 원을 사용합니다"));
		m_beverageText.Format(_T("사이다를 내렸습니다."));
	}
	else {
		m_moneyBOX02.Format(_T("%d"), money);
		m_textMessage = _T("잔액이 부족합니다.");
		m_beverageText = _T(" ");
	}
	UpdateData(false);
}


void CMFCApplicationVendingMachineDlg::OnBnClickedButtonbeverage3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	if (money >= 700) {
		money -= 700;
		m_textMessage.Format(_T("700 원을 사용합니다"));
		m_beverageText.Format(_T("환타를 내렸습니다."));
		m_moneyBOX02.Format(_T("%d"), money);
	}
	else {
		m_moneyBOX02.Format(_T("%d"), money);
		m_textMessage = _T("잔액이 부족합니다.");
		m_beverageText = _T(" ");
	}
	UpdateData(false);
}


void CMFCApplicationVendingMachineDlg::OnBnClickedButtonbeverage4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	if (money >= 800) {
		money -= 800;
		m_textMessage.Format(_T("800 원을 사용합니다"));
		m_beverageText.Format(_T("생수를 내렸습니다."));
		m_moneyBOX02.Format(_T("%d"), money);
	}
	else {
		m_moneyBOX02.Format(_T("%d"), money);
		m_textMessage = _T("잔액이 부족합니다.");
		m_beverageText = _T(" ");
	}
	UpdateData(false);
}

void CMFCApplicationVendingMachineDlg::OnBnClickedButtonreturn()
{
	//customer mode
	if (m_handlerMode == TRUE) {
		UpdateData(true);
		money = 0;
		m_moneyBOX02.Format(_T("%d"), money);
		m_textMessage = _T("모든 금액을 반환합니다.");
		m_beverageText = _T(" ");
		UpdateData(false);
		m_handlerMode = TRUE;
	}
	//handler mode
	else {
		UpdateData(true);
		if (flag_setting == 1) {
			m_beverageText.Format(m_moneyBOX02);

			int column = 0;
			string line = string(CT2CA(m_moneyBOX02));
			stringstream linestream(line);
			string cell;

			string tempName;
			string tempPrice;
			string tempStock;

			while (getline(linestream, cell, ',')) {
				if (column == 0) {
					tempName = cell;
				}
				if (column == 1) {
					tempPrice = cell;
				}
				if (column == 2) {
					tempStock = cell;
				}
				column++;
			}

			Beverage temp((CString)tempName.c_str(), (CString)tempPrice.c_str(), (CString)tempStock.c_str());
			VM.BeverageAdd(temp);

			m_textMessage = _T("적용하였습니다.");
		}

		m_handlerMode = FALSE;
		UpdateData(false);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



void CMFCApplicationVendingMachineDlg::OnBnClickedRadiohandler()
{
	m_handlerMode = FALSE;
}


void CMFCApplicationVendingMachineDlg::OnBnClickedRadiocustomer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_handlerMode = TRUE;
}
