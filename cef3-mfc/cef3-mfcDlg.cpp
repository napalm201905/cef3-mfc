
// cef3-mfcDlg.cpp : 实现文件
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


// Ccef3mfcDlg 对话框



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


// Ccef3mfcDlg 消息处理程序

BOOL Ccef3mfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MAXIMIZE);

	// TODO: 在此添加额外的初始化代码
	CefWindowInfo window_info;

	CRect rt;

	GetWindowRect(&rt);

	window_info.SetAsChild(this->GetSafeHwnd(), rt);

	CefRefPtr<SimpleHandler> handler(new SimpleHandler(true));

	// 特殊的CEF browser 在此设置
	CefBrowserSettings browser_settings;
	char * code = "UTF-8";
	cef_string_t encode = {};
	cef_string_utf8_to_utf16(code, strlen(code), &encode);
	browser_settings.default_encoding = encode;

	// 设置窗口标题
	WCHAR window_name[1024];
	//GetPrivateProfileStringW(L"core", L"title", L"", window_name, 1024, L".\\config.ini");
	//cef_string_wide_to_utf16(window_name, wcslen(window_name), &window_info.window_name);

	// 设置访问地址
	//char url[1024];
	//GetPrivateProfileStringA("core", "urlRoot", "", url, 1024, ".\\config.ini");


	std::string url;
	url = "file:///www/index.html";

	// 查找是否存在ini文件，若不存在，则生成一个新的默认的ini文件
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Ccef3mfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Ccef3mfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ccef3mfcDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CefShutdown();
	CDialogEx::OnClose();
}
