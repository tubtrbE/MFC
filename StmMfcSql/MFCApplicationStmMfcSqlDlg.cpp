
// MFCApplicationStmMfcSqlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplicationStmMfcSql.h"
#include "MFCApplicationStmMfcSqlDlg.h"
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


// CMFCApplicationStmMfcSqlDlg 대화 상자



CMFCApplicationStmMfcSqlDlg::CMFCApplicationStmMfcSqlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATIONSTMMFCSQL_DIALOG, pParent)
	, m_str_comport(_T(""))
	, m_combo_baudrate(_T(""))
	, m_startDate(COleDateTime::GetCurrentTime())
	, m_startTime(COleDateTime::GetCurrentTime())
	, m_endTime(COleDateTime::GetCurrentTime())
	, m_endDate(COleDateTime::GetCurrentTime())
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationStmMfcSqlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOCOM, m_combo_comport_list);
	DDX_Control(pDX, IDC_COMBOBAUD, m_combo_baudrate_list);
	DDX_CBString(pDX, IDC_COMBOCOM, m_str_comport);
	DDX_CBString(pDX, IDC_COMBOBAUD, m_combo_baudrate);
	DDX_Control(pDX, IDC_LISTADC1, m_listAdc1);
	DDX_Control(pDX, IDC_LISTADC2, m_listAdc2);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKERSTARTDATE, m_startDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKERSTARTTIME, m_startTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKERENDTIME, m_endTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKERENDDATE, m_endDate);
	DDX_Control(pDX, IDC_DATETIMEPICKERSTARTDATE, m_startDateCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKERSTARTTIME, m_startTimeCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKERENDDATE, m_endDateCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKERENDTIME, m_endTimeCtrl);
}

BEGIN_MESSAGE_MAP(CMFCApplicationStmMfcSqlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTTONOPEN, &CMFCApplicationStmMfcSqlDlg::OnBnClickedButtonopen)
	ON_CBN_SELCHANGE(IDC_COMBOCOM, &CMFCApplicationStmMfcSqlDlg::OnCbnSelchangeComboComport)
	ON_CBN_SELCHANGE(IDC_COMBOBAUD, &CMFCApplicationStmMfcSqlDlg::OnCbnSelchangeComboBaudrate)
	ON_MESSAGE(WM_MYRECEIVE, &CMFCApplicationStmMfcSqlDlg::OnReceive)
	ON_MESSAGE(WM_MYCLOSE, &CMFCApplicationStmMfcSqlDlg::OnThreadClosed)
	ON_BN_CLICKED(IDC_BUTTONLOAD, &CMFCApplicationStmMfcSqlDlg::OnBnClickedButtonload)
	ON_BN_CLICKED(IDC_BUTTONSEARCH, &CMFCApplicationStmMfcSqlDlg::OnBnClickedButtonsearch)

	ON_WM_TIMER()

	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKERSTARTDATE, &CMFCApplicationStmMfcSqlDlg::OnDtnDatetimechangeDatetimepickerstartdate)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKERSTARTTIME, &CMFCApplicationStmMfcSqlDlg::OnDtnDatetimechangeDatetimepickerstarttime)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKERENDDATE, &CMFCApplicationStmMfcSqlDlg::OnDtnDatetimechangeDatetimepickerenddate)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKERENDTIME, &CMFCApplicationStmMfcSqlDlg::OnDtnDatetimechangeDatetimepickerendtime)
END_MESSAGE_MAP()


// CMFCApplicationStmMfcSqlDlg 메시지 처리기

BOOL CMFCApplicationStmMfcSqlDlg::OnInitDialog()
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

	//////////////////////////////////////////////////////////////////////////
	m_listAdc1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listAdc1.InsertColumn(0, _T("yymmdd"), LVCFMT_CENTER, 100);
	m_listAdc1.InsertColumn(1, _T("hhmmss"), LVCFMT_CENTER, 100);
	m_listAdc1.InsertColumn(2, _T("value"), LVCFMT_CENTER, 100);

	m_listAdc2.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listAdc2.InsertColumn(0, _T("yymmdd"), LVCFMT_CENTER, 100);
	m_listAdc2.InsertColumn(1, _T("hhmmss"), LVCFMT_CENTER, 100);
	m_listAdc2.InsertColumn(2, _T("value"), LVCFMT_CENTER, 100);

	SetTimer(1, 5000, NULL);

	UpdateData(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplicationStmMfcSqlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{

	// if destroy the dialog delete the data over than 10 minute
	CMysqlHandler conn;
	conn.InsertQuery("delete FROM tb_adc1 WHERE TIMESTAMPDIFF(MINUTE, NOW(), TIME) < -10 limit 1000;");
	conn.InsertQuery("delete FROM tb_adc2 WHERE TIMESTAMPDIFF(MINUTE, NOW(), TIME) < -10 limit 1000;");

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

void CMFCApplicationStmMfcSqlDlg::OnPaint()
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
HCURSOR CMFCApplicationStmMfcSqlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplicationStmMfcSqlDlg::OnBnClickedButtonopen()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (comport_state)
	{
		if (m_comm)        //컴포트가존재하면
		{
			AfxMessageBox(_T("COM 포트닫힘"));
			comport_state = false;
			GetDlgItem(IDC_BUTTONOPEN)->SetWindowText(_T("OPEN"));

			m_comm->Close();
			m_comm = NULL;
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

			UpdateData(false);
		}
		else
		{
			AfxMessageBox(_T("ERROR!"));
		}

	}
}



void CMFCApplicationStmMfcSqlDlg::OnCbnSelchangeComboComport()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}


void CMFCApplicationStmMfcSqlDlg::OnCbnSelchangeComboBaudrate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}
//========================================================================================================================================

//Make ADC Value to Query vector group
afx_msg LRESULT CMFCApplicationStmMfcSqlDlg::OnReceive(WPARAM length, LPARAM lpara)
{


	char* data = new char[length + 1];
	if (m_comm)
	{
		m_comm->Receive(data, length);	// Length 길이만큼 데이터 받음.

		int index = -1;
		for (int i = 0; i < (int)length; i++)
		{
			vSerial.push_back(data[i]);
		}

		while (vSerial.size() >= 6) {
			if (vSerial.at(0) == '<') {
				if (vSerial.at(5) == '>') {
					if (vSerial.at(1) == 'A' &&
						(vSerial.at(2) == '1' || vSerial.at(2) == '2') &&
						('0' <= vSerial.at(3) || vSerial.at(3) <= '9') &&
						('0' <= vSerial.at(4) || vSerial.at(4) <= '9')) {

						if (vSerial.at(2) == '1') {
							string temp_str;
							for (int i = 1; i < 5; i++) {
								temp_str += vSerial.at(i);
							}
							vQuery.push_back(MakeQuery(temp_str.c_str()));

						}
						else if (vSerial.at(2) == '2') {
							string temp_str;
							for (int i = 1; i < 5; i++) {
								temp_str += vSerial.at(i);
							}
							vQuery.push_back(MakeQuery(temp_str.c_str()));
						}
						vSerial.erase(vSerial.begin(), vSerial.begin() + 6);
					}
					else {
						vSerial.erase(vSerial.begin(), vSerial.begin() + 6);
					}
				}
				else {
					vSerial.erase(vSerial.begin(), vSerial.begin() + 6);
				}
			}
			else {
				vSerial.erase(vSerial.begin());
			}
		}
	}

	delete[] data;
	UpdateData(false);
	return 0;
}

// SendMessage code
UINT InsertData(LPVOID lpData) {
	CMFCApplicationStmMfcSqlDlg* target = (CMFCApplicationStmMfcSqlDlg*)lpData;
	LPARAM temp = (LPARAM)target;

	// =========================================================================
	// Send Query code
	CMysqlHandler conn;
	//////////////////////
	// 복사본을 보내야 한다. 제거시에 위험이 있기 때문이다.
	// 복사본을 만드는 과정
	vector<string> vCopyQuery;
	vCopyQuery = target->vQuery;
	conn.InsertQuerys(vCopyQuery);
	// 처리후 카피한 쿼리와 해당 쿼리의 사이즈 만큼 제거해준다. 
	target->vQuery.erase(target->vQuery.begin(), target->vQuery.begin() + (int)vCopyQuery.size());
	vCopyQuery.clear();
	vector<string>().swap(vCopyQuery);

	///////////////////////
	SendMessage(target->m_hWnd, WM_QUERY, 0, temp);
	// =========================================================================
	return 0;
}

// Trigger Code
void CMFCApplicationStmMfcSqlDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	AfxBeginThread(InsertData, (LPVOID)this);
	CDialogEx::OnTimer(nIDEvent);
}

afx_msg LRESULT CMFCApplicationStmMfcSqlDlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{
	((CSerialComm*)lpara)->HandleClose();
	delete ((CSerialComm*)lpara);

	return 0;
}
string CMFCApplicationStmMfcSqlDlg::MakeQuery(string package)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Time = COleDateTime::GetCurrentTime();

	CMysqlHandler conn;
	CString result;

	// ex) insert into tb_adc1 VALUES(10,10);
	string text;
	string time;
	COleDateTime Time = COleDateTime::GetCurrentTime();
	int year = Time.GetYear();
	int month = Time.GetMonth();
	int day = Time.GetDay();
	int hour = Time.GetHour();
	int min = Time.GetMinute();
	int sec = Time.GetSecond();

	string str_year = to_string(year);
	string str_month = to_string(month);
	string str_day = to_string(day);
	string str_hour = to_string(hour);
	string str_min = to_string(min);
	string str_sec = to_string(sec);

	string yymmdd = str_year + "-" + str_month + "-" + str_day;
	string hhmmss = str_hour + ":" + str_min + ":" + str_sec;

	string nowTime =  "'" + yymmdd + " " + hhmmss + "'";


	if (package[1] == '1') {
		int value;
		value = (package[2] - '0') * 1000;
		value += (package[3] - '0') * 100;
		string strValue = to_string(value);
		return text = "insert into tb_adc1 VALUES('" + yymmdd + "', '" + hhmmss + "'," + strValue + ",  "+ nowTime + ");";

	}
	else if (package[1] == '2') {
		int value;
		value = (package[2] - '0') * 1000;
		value += (package[3] - '0') * 100;
		string strValue = to_string(value);
		return text = "insert into tb_adc2 VALUES('" + yymmdd + "', '" + hhmmss + "'," + strValue + ",  " + nowTime + ");";
	}
	else {
		AfxMessageBox(_T("error MakeQuery"));
		return 0;
	}
}

//========================================================================================================================================
void CMFCApplicationStmMfcSqlDlg::OnBnClickedButtonload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// delete before list 
	m_listAdc1.DeleteAllItems();
	m_listAdc2.DeleteAllItems();
	CMysqlHandler conn;
	vector<AdcValue*> dlg_Value;

	if (conn.SelectQuery("select * from tb_adc1 ORDER BY time DESC limit 1000", dlg_Value) == true)
	{

	}

	for (int i = 0; i < (int)dlg_Value.size(); i++) {
		CString str1;
		str1.Format(_T("%d"), i + 1);
		m_listAdc1.InsertItem(i, _T(""));
		m_listAdc1.SetItem(i, 0, LVIF_TEXT, (CString)dlg_Value.at(i)->GetYyMmDd().c_str(), NULL, NULL, NULL, NULL);
		m_listAdc1.SetItem(i, 1, LVIF_TEXT, (CString)dlg_Value.at(i)->GetHhMmSs().c_str(), NULL, NULL, NULL, NULL);
		m_listAdc1.SetItem(i, 2, LVIF_TEXT, (CString)dlg_Value.at(i)->GetValue().c_str(), NULL, NULL, NULL, NULL);
	}
	dlg_Value.clear();
	vector<AdcValue*>().swap(dlg_Value);

	if (conn.SelectQuery("select * from tb_adc2 ORDER BY time DESC limit 1000", dlg_Value) == true)
	{

	}

	for (int i = 0; i < (int)dlg_Value.size(); i++) {
		CString str1;
		str1.Format(_T("%d"), i + 1);
		m_listAdc2.InsertItem(i, _T(""));
		m_listAdc2.SetItem(i, 0, LVIF_TEXT, (CString)dlg_Value.at(i)->GetYyMmDd().c_str(), NULL, NULL, NULL, NULL);
		m_listAdc2.SetItem(i, 1, LVIF_TEXT, (CString)dlg_Value.at(i)->GetHhMmSs().c_str(), NULL, NULL, NULL, NULL);
		m_listAdc2.SetItem(i, 2, LVIF_TEXT, (CString)dlg_Value.at(i)->GetValue().c_str(), NULL, NULL, NULL, NULL);
	}
	dlg_Value.clear();
	vector<AdcValue*>().swap(dlg_Value);


	UpdateData(false);
}

void CMFCApplicationStmMfcSqlDlg::OnBnClickedButtonsearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	m_listAdc1.DeleteAllItems();
	m_listAdc2.DeleteAllItems();
	CMysqlHandler conn;
	vector<AdcValue*> dlg_Value;


	CString startDate;
	CString startTime;
	CString startTime_24;

	CString endDate;
	CString endTime;
	CString endTime_24;

	GetDlgItemText(IDC_DATETIMEPICKERSTARTDATE, startDate);
	GetDlgItemText(IDC_DATETIMEPICKERENDDATE, endDate);
	GetDlgItemText(IDC_DATETIMEPICKERSTARTTIME, startTime);
	GetDlgItemText(IDC_DATETIMEPICKERENDTIME, endTime);

	startTime_24 = Make24Time(startTime);
	endTime_24 = Make24Time(endTime);

	CString stemp = startDate + " " + startTime_24;
	CString etemp = endDate + " " + endTime_24;

	if (m_startDate.m_dt <= m_endDate.m_dt) {
		if (m_startDate.m_dt == m_endDate.m_dt &&
			m_startTime.m_dt < m_endTime.m_dt) {
			

			string text;
			//select* from tb_adc1 WHERE DATE(time)  BETWEEN '2022-07-07 19:21:10' AND '2022-07-21 19:21:10';
			text = "select * from tb_adc1 WHERE time  BETWEEN '" + stemp + "' AND '" + etemp + "';";
			if (conn.SelectQuery((char*)text.c_str(), dlg_Value) == true)
			{
				for (int i = 0; i < (int)dlg_Value.size(); i++) {
					CString str1;
					str1.Format(_T("%d"), i + 1);
					m_listAdc1.InsertItem(i, _T(""));
					m_listAdc1.SetItem(i, 0, LVIF_TEXT, (CString)dlg_Value.at(i)->GetYyMmDd().c_str(), NULL, NULL, NULL, NULL);
					m_listAdc1.SetItem(i, 1, LVIF_TEXT, (CString)dlg_Value.at(i)->GetHhMmSs().c_str(), NULL, NULL, NULL, NULL);
					m_listAdc1.SetItem(i, 2, LVIF_TEXT, (CString)dlg_Value.at(i)->GetValue().c_str(), NULL, NULL, NULL, NULL);
				}
				dlg_Value.clear();
				vector<AdcValue*>().swap(dlg_Value);
			}
			else {
				AfxMessageBox(_T("쿼리 실패"));
			}

			text = "select * from tb_adc2 WHERE time  BETWEEN '" + stemp + "' AND '" + etemp + "';";
			if (conn.SelectQuery((char*)text.c_str(), dlg_Value) == true)
			{
				for (int i = 0; i < (int)dlg_Value.size(); i++) {
					CString str1;
					str1.Format(_T("%d"), i + 1);
					m_listAdc2.InsertItem(i, _T(""));
					m_listAdc2.SetItem(i, 0, LVIF_TEXT, (CString)dlg_Value.at(i)->GetYyMmDd().c_str(), NULL, NULL, NULL, NULL);
					m_listAdc2.SetItem(i, 1, LVIF_TEXT, (CString)dlg_Value.at(i)->GetHhMmSs().c_str(), NULL, NULL, NULL, NULL);
					m_listAdc2.SetItem(i, 2, LVIF_TEXT, (CString)dlg_Value.at(i)->GetValue().c_str(), NULL, NULL, NULL, NULL);
				}
				dlg_Value.clear();
				vector<AdcValue*>().swap(dlg_Value);
			}
			else {
				AfxMessageBox(_T("쿼리 실패"));
			}
		}
		else if (m_startDate.m_dt < m_endDate.m_dt){

			string text;
			text = "select * from tb_adc1 WHERE time  BETWEEN '" + stemp + "' AND '" + etemp + "' limit 1000;";
			if (conn.SelectQuery((char*)text.c_str(), dlg_Value) == true)
			{
				for (int i = 0; i < (int)dlg_Value.size(); i++) {
					CString str1;
					str1.Format(_T("%d"), i + 1);
					m_listAdc1.InsertItem(i, _T(""));
					m_listAdc1.SetItem(i, 0, LVIF_TEXT, (CString)dlg_Value.at(i)->GetYyMmDd().c_str(), NULL, NULL, NULL, NULL);
					m_listAdc1.SetItem(i, 1, LVIF_TEXT, (CString)dlg_Value.at(i)->GetHhMmSs().c_str(), NULL, NULL, NULL, NULL);
					m_listAdc1.SetItem(i, 2, LVIF_TEXT, (CString)dlg_Value.at(i)->GetValue().c_str(), NULL, NULL, NULL, NULL);
				}
				dlg_Value.clear();
//				vector<AdcValue*>().swap(dlg_Value);
			}
			else {
				AfxMessageBox(_T("쿼리 실패"));
			}

			text = "select * from tb_adc2 WHERE time  BETWEEN '" + stemp + "' AND '" + etemp + "' limit 1000;";
			if (conn.SelectQuery((char*)text.c_str(), dlg_Value) == true)
			{
				for (int i = 0; i < (int)dlg_Value.size(); i++) {
					CString str1;
					str1.Format(_T("%d"), i + 1);
					m_listAdc2.InsertItem(i, _T(""));
					m_listAdc2.SetItem(i, 0, LVIF_TEXT, (CString)dlg_Value.at(i)->GetYyMmDd().c_str(), NULL, NULL, NULL, NULL);
					m_listAdc2.SetItem(i, 1, LVIF_TEXT, (CString)dlg_Value.at(i)->GetHhMmSs().c_str(), NULL, NULL, NULL, NULL);
					m_listAdc2.SetItem(i, 2, LVIF_TEXT, (CString)dlg_Value.at(i)->GetValue().c_str(), NULL, NULL, NULL, NULL);
				}
				dlg_Value.clear();
				vector<AdcValue*>().swap(dlg_Value);
			}
			else {
				AfxMessageBox(_T("쿼리 실패"));
			}
		}
		else {
			AfxMessageBox(_T("시간범위 오류(시간)"));
		}
	}
	else {
		AfxMessageBox(_T("시간범위 오류(날짜)"));
	}

	UpdateData(FALSE);
}

CString CMFCApplicationStmMfcSqlDlg::Make24Time(CString Time) {
	CString Time_24;
	if (Time.Left(4) == "오후") {
		CString temp = Time.Mid(4);
		string hour = temp.Left(2);
		hour[1] = hour[1] + 2;
		if (hour[0] == '1') {
			hour[0]++;
		}
		else {
			hour[0] = '1';
		}
		return Time_24 = hour.c_str() + temp.Mid(2);
	}
	else if (Time.Left(4) == "오전") {
		return Time_24 = Time.Mid(4);
	}
	else {
		AfxMessageBox(_T("실패"));
		return 0;
	}
}

void CMFCApplicationStmMfcSqlDlg::OnDtnDatetimechangeDatetimepickerstartdate(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);

	*pResult = 0;
}


void CMFCApplicationStmMfcSqlDlg::OnDtnDatetimechangeDatetimepickerenddate(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);


	*pResult = 0;
}
void CMFCApplicationStmMfcSqlDlg::OnDtnDatetimechangeDatetimepickerstarttime(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);


	*pResult = 0;
}

void CMFCApplicationStmMfcSqlDlg::OnDtnDatetimechangeDatetimepickerendtime(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true); 

	*pResult = 0;
}
