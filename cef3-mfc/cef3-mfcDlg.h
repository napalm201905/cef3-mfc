
// cef3-mfcDlg.h : 头文件
//
#include "simple_client.h"
#pragma once


// Ccef3mfcDlg 对话框
class Ccef3mfcDlg : public CDialogEx
{
// 构造
public:
	Ccef3mfcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CEF3MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CefRefPtr<SimpleClient>  m_simpleClient;
	BOOL PreTranslateMessage(MSG* pMsg);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnGo();
	afx_msg void OnBnClickedBtnGoford();
	afx_msg void OnBnClickedBtnGoback();
};
