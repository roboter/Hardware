// USB_I2C_SRF08Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "USB_I2C_SRF08.h"
#include "USB_I2C_SRF08Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define I2CD_CMD	0x53		// direct I2C control command
#define I2C_CMD		0x55		// registered I2C control command
#define CM01_CMD	0x5a		// CM01 command 

enum cmds { nop=0, VERSION, NEW_ADDRESS, BATTERY,
			SCAN1, SCAN2, SCAN3, SCAN4, SCAN6, SCAN8, SCAN12, SCAN16,
};

HANDLE hCom;
int Addr=0;
BYTE CommPort=0;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUSB_I2C_SRF08Dlg dialog

CUSB_I2C_SRF08Dlg::CUSB_I2C_SRF08Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUSB_I2C_SRF08Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUSB_I2C_SRF08Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUSB_I2C_SRF08Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUSB_I2C_SRF08Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUSB_I2C_SRF08Dlg, CDialog)
	//{{AFX_MSG_MAP(CUSB_I2C_SRF08Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_COM1, OnCom1)
	ON_BN_CLICKED(IDC_COM2, OnCom2)
	ON_BN_CLICKED(IDC_COM3, OnCom3)
	ON_BN_CLICKED(IDC_COM4, OnCom4)
	ON_BN_CLICKED(IDC_COM5, OnCom5)
	ON_BN_CLICKED(IDC_COM6, OnCom6)
	ON_BN_CLICKED(IDC_COM7, OnCom7)
	ON_BN_CLICKED(IDC_COM8, OnCom8)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUSB_I2C_SRF08Dlg message handlers

BOOL CUSB_I2C_SRF08Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
 	CWinApp* App = AfxGetApp( ); 
   	CommPort = App->GetProfileInt("SETTINGS","COMPORT",0);
	switch(CommPort) {
		case 1:	SetupCommPort("COM1");
				((CButton*)GetDlgItem(IDC_COM1))->SetCheck(1);
				break;
		case 2:	SetupCommPort("COM2");
				((CButton*)GetDlgItem(IDC_COM2))->SetCheck(1);
				break;
		case 3:	SetupCommPort("COM3");
				((CButton*)GetDlgItem(IDC_COM3))->SetCheck(1);
				break;
		case 4:	SetupCommPort("COM4");
				((CButton*)GetDlgItem(IDC_COM4))->SetCheck(1);
				break;
		case 5:	SetupCommPort("COM5");
				((CButton*)GetDlgItem(IDC_COM5))->SetCheck(1);
				break;
		case 6:	SetupCommPort("COM6");
				((CButton*)GetDlgItem(IDC_COM6))->SetCheck(1);
				break;
		case 7:	SetupCommPort("COM7");
				((CButton*)GetDlgItem(IDC_COM7))->SetCheck(1);
				break;
		case 8:	SetupCommPort("COM8");
				((CButton*)GetDlgItem(IDC_COM8))->SetCheck(1);
				break;
		default: ((CButton*)GetDlgItem(IDC_COM1))->SetCheck(0);
	}
	SetTimer(1, 600, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUSB_I2C_SRF08Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUSB_I2C_SRF08Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUSB_I2C_SRF08Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUSB_I2C_SRF08Dlg::SetupCommPort( LPCTSTR comport)
{
	DCB dcb;
	COMMTIMEOUTS ct;

	CloseHandle(hCom);
	hCom = CreateFile( comport, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
	GetCommState(hCom, &dcb);
	dcb.BaudRate = CBR_19200;
	dcb.fParity = FALSE;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fDsrSensitivity = FALSE;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	dcb.fAbortOnError = FALSE;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = TWOSTOPBITS;
	SetCommState(hCom, &dcb);
  
	GetCommTimeouts(hCom, &ct);
	ct.ReadIntervalTimeout = 500;
    ct.ReadTotalTimeoutMultiplier =500; 
    ct.ReadTotalTimeoutConstant = 500; 
	SetCommTimeouts(hCom, &ct);

	SetCommMask(hCom, EV_RXCHAR);
}

void CUSB_I2C_SRF08Dlg::OnCom1() 
{
	CommPort = 1;	
	SetupCommPort("COM1");
   	CWinApp* App = AfxGetApp( ); 
   	App->WriteProfileInt("SETTINGS","COMPORT",CommPort);
}

void CUSB_I2C_SRF08Dlg::OnCom2() 
{
	CommPort = 2;	
	SetupCommPort("COM2");
   	CWinApp* App = AfxGetApp( ); 
   	App->WriteProfileInt("SETTINGS","COMPORT",CommPort);
}

void CUSB_I2C_SRF08Dlg::OnCom3() 
{
	CommPort = 3;	
	SetupCommPort("COM3");
   	CWinApp* App = AfxGetApp( ); 
   	App->WriteProfileInt("SETTINGS","COMPORT",CommPort);
}

void CUSB_I2C_SRF08Dlg::OnCom4() 
{
	CommPort = 4;	
	SetupCommPort("COM4");
   	CWinApp* App = AfxGetApp( ); 
   	App->WriteProfileInt("SETTINGS","COMPORT",CommPort);
}

void CUSB_I2C_SRF08Dlg::OnCom5() 
{
	CommPort = 5;	
	SetupCommPort("COM5");
   	CWinApp* App = AfxGetApp( ); 
   	App->WriteProfileInt("SETTINGS","COMPORT",CommPort);
}

void CUSB_I2C_SRF08Dlg::OnCom6() 
{
	CommPort = 6;	
	SetupCommPort("COM6");
   	CWinApp* App = AfxGetApp( ); 
   	App->WriteProfileInt("SETTINGS","COMPORT",CommPort);
}

void CUSB_I2C_SRF08Dlg::OnCom7() 
{
	CommPort = 7;	
	SetupCommPort("COM7");
   	CWinApp* App = AfxGetApp( ); 
   	App->WriteProfileInt("SETTINGS","COMPORT",CommPort);
}

void CUSB_I2C_SRF08Dlg::OnCom8() 
{
	CommPort = 8;	
	SetupCommPort("COM8");
   	CWinApp* App = AfxGetApp( ); 
   	App->WriteProfileInt("SETTINGS","COMPORT",CommPort);
}

void CUSB_I2C_SRF08Dlg::OnTimer(UINT nIDEvent) 
{
static int x=0;
CString s;
DWORD n;
static int search_addr=0xe0;
char cmd[10];
static int idx=1, dir=0, scan=0, old_idx=1, cm02_ver;
BYTE sbuf[100];

	if(CommPort==0) {
		SetDlgItemText( IDC_MSG, "Set Com Port" );
	}	
	else if(cm02_ver==0) {
		sbuf[0] = CM01_CMD;			// send read battery command
		sbuf[1] = VERSION;
		sbuf[2] = 0x00;
		sbuf[3] = 0x00;
	    WriteFile(hCom, &sbuf, 4, &n, NULL);
		ReadFile(hCom, &sbuf, 1, &n, NULL);
		cm02_ver = sbuf[0];
		s.Format("%i", sbuf[0]);
		SetDlgItemText( IDC_USB_I2C_VER, s );
	}
	else if(Addr==0) {			// find srf08
		sbuf[0] = I2C_CMD;			// send sonar read command
		sbuf[1] = search_addr+1;
		sbuf[2] = 0x00;
		sbuf[3] = 0x01;
	    WriteFile(hCom, &sbuf, 4, &n, NULL);
		ReadFile(hCom, &sbuf, 1, &n, NULL);
		if(sbuf[0]<20) {
			Addr = search_addr;
			s.Format("0x%02X ", Addr);
			SetDlgItemText( IDC_SRF08_ADDR, s );
			SetDlgItemText( IDC_MSG, "SRF Found" );
//			((CButton*)GetDlgItem(IDC_UPDATE))->EnableWindow(FALSE);
		}
		else {
			search_addr += 2;
			if(search_addr>0xfe) search_addr = 0xe0;
			s.Format("0x%02X", search_addr);
			SetDlgItemText( IDC_SRF08_ADDR, s );
			SetDlgItemText( IDC_MSG, "Searching" );
		}
		Invalidate(TRUE);
	}
	else {
		sbuf[0] = I2C_CMD;			// send sonar read command
		sbuf[1] = Addr+1;
		sbuf[2] = 0x00;
		sbuf[3] = 0x04;
	    WriteFile(hCom, &sbuf, 4, &n, NULL);

		ReadFile(hCom, &sbuf, 4, &n, NULL);
		s.Format("%i", sbuf[0]);
		SetDlgItemText( IDC_SRF08_VER, s );
		if(sbuf[0]>20) Addr=0;

		s.Format("%i ", sbuf[1]);
		SetDlgItemText( IDC_SRF08_LIGHT, s );

		n = sbuf[2]<<8;
		n |= sbuf[3];
		s.Format("%i", n);
		SetDlgItemText( IDC_SRF08_US, s );
		s.Format("%i", n/58);
		SetDlgItemText( IDC_SRF08_CM, s );
		s.Format("%i", n/148);
		SetDlgItemText( IDC_SRF08_INCH, s );

		sbuf[0] = I2C_CMD;			// send gain limit
		sbuf[1] = Addr;
		sbuf[2] = 0x01;
		sbuf[3] = 0x01;
		sbuf[4] = 20;
	    WriteFile(hCom, &sbuf, 5, &n, NULL);
		ReadFile(hCom, &sbuf, 1, &n, NULL);

		sbuf[0] = I2C_CMD;			// send sonar rangeing (uS) command
		sbuf[1] = Addr;
		sbuf[2] = 0x00;
		sbuf[3] = 0x01;
		sbuf[4] = 0x52;
	    WriteFile(hCom, &sbuf, 5, &n, NULL);
		ReadFile(hCom, &sbuf, 1, &n, NULL);

/*		sbuf[0] = I2CD_CMD;			// send direct to chip write command
		sbuf[1] = 0x40;
		if((x&3)==3) sbuf[2] = 0xfe;
		else sbuf[2] = 0xff;
		x++;
	    WriteFile(hCom, &sbuf, 3, &n, NULL);
		ReadFile(hCom, &sbuf, 1, &n, NULL);

		sbuf[0] = I2CD_CMD;			// send direct to chip read command
		sbuf[1] = 0x41;
	    WriteFile(hCom, &sbuf, 2, &n, NULL);
		ReadFile(hCom, &sbuf, 1, &n, NULL);

		s.Format("0x%x ", sbuf[0]);
		SetDlgItemText( IDC_SRF08_LIGHT, s );
*/
	}
	CDialog::OnTimer(nIDEvent);
}
	