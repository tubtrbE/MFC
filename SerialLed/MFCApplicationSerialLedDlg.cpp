
// MFCApplicationSerialLedDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplicationSerialLed.h"
#include "MFCApplicationSerialLedDlg.h"
#include "afxdialogex.h"

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


// CMFCApplicationSerialLedDlg 대화 상자



CMFCApplicationSerialLedDlg::CMFCApplicationSerialLedDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATIONSERIALLED_DIALOG, pParent)
	, m_combo_baudrate(_T(""))
	, m_str_comport(_T(""))
	, m_led1(_T(""))
	, m_led2(_T(""))
	, m_led3(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationSerialLedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOBAUD, m_combo_baudrate_list);
	DDX_CBString(pDX, IDC_COMBOBAUD, m_combo_baudrate);
	DDX_Control(pDX, IDC_COMBOCOM, m_combo_comport_list);
	DDX_CBString(pDX, IDC_COMBOCOM, m_str_comport);
	DDX_Text(pDX, IDC_EDITLED1STATE, m_led1);
	DDX_Text(pDX, IDC_EDITLED2STATE, m_led2);
	DDX_Text(pDX, IDC_EDITLED3STATE, m_led3);

}

BEGIN_MESSAGE_MAP(CMFCApplicationSerialLedDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONOPEN, &CMFCApplicationSerialLedDlg::OnBnClickedButtonopen)
	ON_BN_CLICKED(IDC_BUTTONCLEAR, &CMFCApplicationSerialLedDlg::OnBnClickedButtonclear)
	ON_BN_CLICKED(IDC_BUTTONLED1, &CMFCApplicationSerialLedDlg::OnBnClickedButtonled1)
	ON_BN_CLICKED(IDC_BUTTONLED2, &CMFCApplicationSerialLedDlg::OnBnClickedButtonled2)
	ON_BN_CLICKED(IDC_BUTTONLED3, &CMFCApplicationSerialLedDlg::OnBnClickedButtonled3)
	ON_CBN_SELCHANGE(IDC_COMBOCOM, &CMFCApplicationSerialLedDlg::OnCbnSelchangeComboComport)
	ON_CBN_SELCHANGE(IDC_COMBOBAUD, &CMFCApplicationSerialLedDlg::OnCbnSelchangeComboBaudrate)
END_MESSAGE_MAP()


// CMFCApplicationSerialLedDlg 메시지 처리기

BOOL CMFCApplicationSerialLedDlg::OnInitDialog()
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
	m_combo_comport_list.AddString(_T("COM1"));
	m_combo_comport_list.AddString(_T("COM2"));
	m_combo_comport_list.AddString(_T("COM3"));
	m_combo_comport_list.AddString(_T("COM4"));
	m_combo_comport_list.AddString(_T("COM5"));
	m_combo_comport_list.AddString(_T("COM6"));
	m_combo_comport_list.AddString(_T("COM7"));
	m_combo_comport_list.AddString(_T("COM8"));
	m_combo_comport_list.AddString(_T("COM9"));
	m_combo_comport_list.AddString(_T("COM10"));

	m_combo_baudrate_list.AddString(_T("9600"));
	m_combo_baudrate_list.AddString(_T("19200"));
	m_combo_baudrate_list.AddString(_T("115200"));


	comport_state = false;
	GetDlgItem(IDC_BUTTONOPEN)->SetWindowText(_T("OPEN"));
	m_str_comport = _T("COM8");
	m_combo_baudrate = _T("115200");

	GetDlgItem(IDC_BUTTONLED1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTONLED2)->EnableWindow(false);
	GetDlgItem(IDC_BUTTONLED3)->EnableWindow(false);
	UpdateData(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}



void CMFCApplicationSerialLedDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplicationSerialLedDlg::OnPaint()
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
HCURSOR CMFCApplicationSerialLedDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CMFCApplicationSerialLedDlg::OnBnClickedButtonopen()
{
	// TODO: Add your control notification handler code here
	if (comport_state)
	{
		if (m_comm)        //컴포트가존재하면
		{
			m_comm->Close();
			m_comm = NULL;
			AfxMessageBox(_T("COM 포트닫힘"));
			comport_state = false;
			GetDlgItem(IDC_BUTTONOPEN)->SetWindowText(_T("OPEN"));
			GetDlgItem(IDC_BUTTONLED1)->EnableWindow(false);
			GetDlgItem(IDC_BUTTONLED2)->EnableWindow(false);
			GetDlgItem(IDC_BUTTONLED3)->EnableWindow(false);
			m_led1 = _T("");
			m_led2 = _T("");
			m_led3 = _T("");

			CString str;
			str = "LED00";
			str += "\r\n";
			m_comm->Send(str, str.GetLength());
			UpdateData(false);
		}
	}
	else
	{
		m_comm = new CSerialComm(_T("\\\\.\\") + m_str_comport, m_combo_baudrate, _T("None"), _T("8 Bit"), _T("1 Bit"));         // initial Comm port
		if (m_comm->Create(GetSafeHwnd()) != 0) //통신포트를열고윈도우의핸들을넘긴다.
		{
			AfxMessageBox(_T("COM 포트열림"));
			comport_state = true;
			GetDlgItem(IDC_BUTTONOPEN)->SetWindowText(_T("CLOSE"));
			GetDlgItem(IDC_BUTTONLED1)->EnableWindow(true);
			GetDlgItem(IDC_BUTTONLED2)->EnableWindow(true);
			GetDlgItem(IDC_BUTTONLED3)->EnableWindow(true);
			m_led1 = "<LED11>";
			m_led2 = "<LED21>";
			m_led3 = "<LED31>";

			CString str;
			str = "LED01";
			str += "\r\n";
			m_comm->Send(str, str.GetLength());
			UpdateData(false);
		}
		else
		{
			AfxMessageBox(_T("ERROR!"));
		}

	}
}

// LED turn off 기능 추가
void CMFCApplicationSerialLedDlg::OnBnClickedButtonclear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_led1 = "<LED10>";
	m_led2 = "<LED20>";
	m_led3 = "<LED30>";

	CString str;
	str = "LED00";
	str += "\r\n";
	m_comm->Send(str, str.GetLength());
	UpdateData(false);
}


void CMFCApplicationSerialLedDlg::OnBnClickedButtonled1()
{
	UpdateData(true);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_led1 == "<LED10>") {
		m_led1 = "<LED11>";
	}
	else {
		m_led1 = "<LED10>";
	}

	CString str;
	str = m_led1;
	str += "\r\n";
	m_comm->Send(str, str.GetLength());

	UpdateData(false);

}


void CMFCApplicationSerialLedDlg::OnBnClickedButtonled2()
{
	UpdateData(true);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_led2 == "<LED20>") {
		m_led2 = "<LED21>";
	}
	else {
		m_led2 = "<LED20>";
	}
	CString str;
	str = m_led2;
	str += "\r\n";
	m_comm->Send(str, str.GetLength());

	UpdateData(false);
}


void CMFCApplicationSerialLedDlg::OnBnClickedButtonled3()
{
	UpdateData(true);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_led3 == "<LED30>") {
		m_led3 = "<LED31>";
	}
	else {
		m_led3 = "<LED30>";
	}
	CString str;
	str = m_led3;
	str += "\r\n";
	m_comm->Send(str, str.GetLength());

	UpdateData(false);
}


void CMFCApplicationSerialLedDlg::OnCbnSelchangeComboComport()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}


void CMFCApplicationSerialLedDlg::OnCbnSelchangeComboBaudrate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}
