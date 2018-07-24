#include "simple_client.h"
#include  <tchar.h>

enum { 
	ID_CMD_REFRESH = 0 ,
	ID_SHOW_DEV_TOOLS
};

SimpleClient::SimpleClient()
{
	hWnd_ = NULL;
}


SimpleClient::~SimpleClient()
{
}

void SimpleClient::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	m_cefBrowser = browser;
}


bool SimpleClient::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
	CefProcessId source_process,
	CefRefPtr<CefProcessMessage> message)
{
	const std::string& messageName = message->GetName();
	if (messageName == "login_msg")
	{
		// extract message
		CefRefPtr<CefListValue> args = message->GetArgumentList();
		CefString strUser = args->GetString(0);
		CefString strPassword = args->GetString(1);
		TCHAR szLog[256] = { 0 };
		_stprintf_s(szLog, 256, L"BrowserProcess, user - %s, password - %s\r\n", strUser.c_str(), strPassword.c_str());
		OutputDebugString(szLog);

		//send reply to render process
		CefRefPtr<CefProcessMessage> outMsg = CefProcessMessage::Create("login_reply");

		// Retrieve the argument list object.
		CefRefPtr<CefListValue> replyArgs = outMsg->GetArgumentList();

		// Populate the argument values.
		replyArgs->SetSize(1);
		replyArgs->SetInt(0, 0);

		// Send the process message to the renderer process.
		browser->SendProcessMessage(PID_RENDERER, outMsg);

		return true;
	}
	return false;
}

bool SimpleClient::OnBeforePopup(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	const CefString& target_url,
	const CefString& target_frame_name,
	WindowOpenDisposition target_disposition,
	bool user_gesture,
	const CefPopupFeatures& popupFeatures,
	CefWindowInfo& windowInfo,
	CefRefPtr<CefClient>& client,
	CefBrowserSettings& settings,
	bool* no_javascript_access)
{
	switch (target_disposition)
	{
	case WOD_NEW_FOREGROUND_TAB:
	case WOD_NEW_BACKGROUND_TAB:
	case WOD_NEW_POPUP:
	case WOD_NEW_WINDOW:
		browser->GetMainFrame()->LoadURL(target_url);
		return true; //cancel create
	}

	return false;
}

void SimpleClient::OnBeforeDownload(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefDownloadItem> download_item,
	const CefString& suggested_name,
	CefRefPtr<CefBeforeDownloadCallback> callback)
{
	callback->Continue(download_item->GetURL(), true);
}

void SimpleClient::OnDownloadUpdated(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefDownloadItem> download_item,
	CefRefPtr<CefDownloadItemCallback> callback)
{
	if (download_item->IsComplete())
	{
		// MessageBox.Show("���سɹ�");
		OutputDebugString(L"���سɹ�");
		if (browser->IsPopup() && !browser->HasDocument())
		{
			//browser->GetHost()->ParentWindowWillClose();
			browser->GetHost()->CloseBrowser(true);
		}
	}
	else
	{
		// ���ȡ��Ӧ����ת��һ����ҳ
		browser->GoBack();
	}
}

bool SimpleClient::OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
	const CefKeyEvent& event,
	CefEventHandle os_event,
	bool* is_keyboard_shortcut)
{
	if (event.windows_key_code == 116)//F5ˢ��
		browser->Reload();
	else if (event.windows_key_code == 123)
	{


	}
	return false;
}

bool SimpleClient::OnKeyEvent(CefRefPtr<CefBrowser> browser,
	const CefKeyEvent& event,
	CefEventHandle os_event) {
	return false;
}

// �Ҽ��˵�
void SimpleClient::OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefContextMenuParams> params,
	CefRefPtr<CefMenuModel> model)
{
	if (model->GetCount() > 0) {// ˢ�²˵�
		model->AddSeparator();
		model->AddItem(ID_CMD_REFRESH, __TEXT("ˢ��"));
		model->AddItem(ID_SHOW_DEV_TOOLS, __TEXT("������ѡ��"));
	}
}

bool SimpleClient::OnContextMenuCommand(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefContextMenuParams> params,
	int command_id, EventFlags event_flags)
{
	switch (command_id)
	{
	case ID_CMD_REFRESH:
		browser->Reload();
		break;
	case ID_SHOW_DEV_TOOLS:
	{
		ShowDevelopTools(browser, CefPoint(0, 0));
		break;
	}
	default:
		break;
	}
	return false;
}

// ����ѡ��
void SimpleClient::ShowDevelopTools(CefRefPtr<CefBrowser> browser, const CefPoint& inspect_element_at)
{
	CefWindowInfo windowInfo;	CefBrowserSettings settings;	windowInfo.SetAsPopup(browser->GetHost()->GetWindowHandle(), "DevTools");	browser->GetHost()->ShowDevTools(windowInfo, this, settings, CefPoint());
}

void SimpleClient::CloseDevelopTools(CefRefPtr<CefBrowser> browser)
{
	browser->GetHost()->CloseDevTools();
}

// close browser
bool SimpleClient::DoClose(CefRefPtr<CefBrowser> browser)
{
	// ͬһ��browser�����ж����������ڣ����µ��Ӵ��ڴ����ӣ��������ڵ�ǰ������ת��
	// ��ʱ����ֵ���ܱ�������һЩ���⴦��
	/*if (CefCurrentlyOn(TID_UI))
	{
		return true;
	}*/
	return false;
}

void SimpleClient::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	if (hWnd_ == browser->GetHost()->GetWindowHandle())
	{
		m_cefBrowser = NULL;
	}
}