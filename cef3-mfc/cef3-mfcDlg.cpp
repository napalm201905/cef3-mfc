
// cef3-mfcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cef3-mfc.h"
#include "cef3-mfcDlg.h"
#include "afxdialogex.h"

#include "include/cef_app.h"
#include "simple_render.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ccef3mfcDlg �Ի���



Ccef3mfcDlg::Ccef3mfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CEF3MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ccef3mfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ccef3mfcDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_GO, &Ccef3mfcDlg::OnBnClickedBtnGo)
	ON_BN_CLICKED(IDC_BTN_GOFORD, &Ccef3mfcDlg::OnBnClickedBtnGoford)
	ON_BN_CLICKED(IDC_BTN_GOBACK, &Ccef3mfcDlg::OnBnClickedBtnGoback)
END_MESSAGE_MAP()


// Ccef3mfcDlg ��Ϣ�������

BOOL Ccef3mfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MAXIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	CefRefPtr<SimpleClient> client(new SimpleClient());
	m_simpleClient = client;

	CefRefPtr<SimpleRender> app(new SimpleRender());

	CefSettings settings;
	CefSettingsTraits::init(&settings);
	settings.multi_threaded_message_loop = true;
	settings.remote_debugging_port = 8088; // ��������壬�������е��Թ���
	settings.single_process = true;

	CefMainArgs mainArgs;
	CefRefPtr<CefApp> cefApp;

	CefInitialize(mainArgs, settings, cefApp, NULL);

	RECT rect;
	GetClientRect(&rect);
	RECT rectnew = rect;
	rectnew.top = rect.top + 50;
	rectnew.bottom = rect.bottom;
	rectnew.left = rect.left;
	rectnew.right = rect.right;

	CefWindowInfo winInfo;
	winInfo.SetAsChild(GetSafeHwnd(), rectnew);
	
	CefBrowserSettings browserSettings;
	CefBrowserHost::CreateBrowser(winInfo, client, _T("http://www.baidu.com"), browserSettings, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Ccef3mfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Ccef3mfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ccef3mfcDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CefShutdown();
	CDialogEx::OnClose();
}

void Ccef3mfcDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	RECT rect;
	GetClientRect(&rect);

	if (m_simpleClient.get())
	{
		CefRefPtr<CefBrowser> browser = m_simpleClient->GetBrowser();
		if (browser)
		{
			CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
			::MoveWindow(hwnd, 0, 50, rect.right - rect.left, rect.bottom - 50, true);
		}
	}
}

/*
Go��ť
*/
void Ccef3mfcDlg::OnBnClickedBtnGo()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strUrl;
	GetDlgItem(IDC_EDIT_URL)->GetWindowText(strUrl);
	if (strUrl.Trim().IsEmpty())
	{
		AfxMessageBox(_T("��������ַ"));
		return;
	}
	const CefString cefStrUrl(strUrl);
	m_simpleClient->GetBrowser()->GetMainFrame()->LoadURL(cefStrUrl);
}

/*
ǰ����ť
*/
void Ccef3mfcDlg::OnBnClickedBtnGoford()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_simpleClient->GetBrowser()->GoForward();
}

/*
���˰�ť
*/
void Ccef3mfcDlg::OnBnClickedBtnGoback()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_simpleClient->GetBrowser()->GoBack();
}

/*
��Ӧ�س���
*/
BOOL Ccef3mfcDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:    // ���λس�
			OnBnClickedBtnGo();
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
