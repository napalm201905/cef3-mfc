
// cef3-mfcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cef3-mfc.h"
#include "cef3-mfcDlg.h"
#include "afxdialogex.h"
#include "simple_handler.h"

#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/wrapper/cef_helpers.h"
#include "simple_app.h"
#include "MyINI.h"

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
	CefWindowInfo window_info;

	CRect rt;

	GetWindowRect(&rt);

	window_info.SetAsChild(this->GetSafeHwnd(), rt);

	CefRefPtr<SimpleHandler> handler(new SimpleHandler(true));

	// �����CEF browser �ڴ�����
	CefBrowserSettings browser_settings;
	char * code = "UTF-8";
	cef_string_t encode = {};
	cef_string_utf8_to_utf16(code, strlen(code), &encode);
	browser_settings.default_encoding = encode;

	// ���ô��ڱ���
	WCHAR window_name[1024];
	//GetPrivateProfileStringW(L"core", L"title", L"", window_name, 1024, L".\\config.ini");
	//cef_string_wide_to_utf16(window_name, wcslen(window_name), &window_info.window_name);

	// ���÷��ʵ�ַ
	//char url[1024];
	//GetPrivateProfileStringA("core", "urlRoot", "", url, 1024, ".\\config.ini");


	std::string url;
	url = "file:///www/index.html";

	// �����Ƿ����ini�ļ����������ڣ�������һ���µ�Ĭ�ϵ�ini�ļ�
	/*CFileFind finder;
	BOOL ifFind = finder.FindFile(_T("config.ini"));
	if (!ifFind)
	{
		WritePrivateProfileStringW(_T("core"), _T("urlRoot"), _T("www.baidu.com"), _T("config.ini"));
	}
	CString str;
	USES_CONVERSION;
	GetPrivateProfileString(_T("core"), _T("urlRoot"), CString("NULL"), str.GetBuffer(MAX_PATH), MAX_PATH, _T("config.ini"));
	std::string url(W2A(str));*/

	CefBrowserHost::CreateBrowser(window_info, handler.get(), url, browser_settings, NULL);

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
