// USB_I2C_SRF08Dlg.h : header file
//

#if !defined(AFX_USB_I2C_SRF08DLG_H__A7B2F0A6_E746_11DA_A115_0008A144568C__INCLUDED_)
#define AFX_USB_I2C_SRF08DLG_H__A7B2F0A6_E746_11DA_A115_0008A144568C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUSB_I2C_SRF08Dlg dialog

class CUSB_I2C_SRF08Dlg : public CDialog
{
// Construction
public:
	CUSB_I2C_SRF08Dlg(CWnd* pParent = NULL);	// standard constructor

	void SetupCommPort( LPCTSTR comport);

// Dialog Data
	//{{AFX_DATA(CUSB_I2C_SRF08Dlg)
	enum { IDD = IDD_USB_I2C_SRF08_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUSB_I2C_SRF08Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUSB_I2C_SRF08Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCom1();
	afx_msg void OnCom2();
	afx_msg void OnCom3();
	afx_msg void OnCom4();
	afx_msg void OnCom5();
	afx_msg void OnCom6();
	afx_msg void OnCom7();
	afx_msg void OnCom8();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USB_I2C_SRF08DLG_H__A7B2F0A6_E746_11DA_A115_0008A144568C__INCLUDED_)
