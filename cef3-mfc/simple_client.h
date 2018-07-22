#pragma once
#include "include/cef_client.h"
class SimpleClient : public CefClient, 
					 public CefLifeSpanHandler, 
					 public CefDownloadHandler, 
				     public CefKeyboardHandler, 
					 public CefContextMenuHandler
{
public:
	SimpleClient();
	~SimpleClient();

	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE
	{
		return this;
	}

	// CefLifeSpanHandler methods:
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;

	CefRefPtr<CefBrowser> GetBrowser() { return m_cefBrowser; }
	
	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message) override;

	virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& target_url,
		const CefString& target_frame_name,
		WindowOpenDisposition target_disposition,
		bool user_gesture,
		const CefPopupFeatures& popupFeatures,
		CefWindowInfo& windowInfo,
		CefRefPtr<CefClient>& client,
		CefBrowserSettings& settings,
		bool* no_javascript_access) override;

	// download
	virtual CefRefPtr<CefDownloadHandler> GetDownloadHandler() { return this; }
	virtual void OnBeforeDownload(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDownloadItem> download_item,
		const CefString& suggested_name,
		CefRefPtr<CefBeforeDownloadCallback> callback) OVERRIDE;
	virtual void OnDownloadUpdated(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDownloadItem> download_item,
		CefRefPtr<CefDownloadItemCallback> callback) OVERRIDE;

	//F5ˢ�¹���
	virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() //ʵ��  
	{
		return this;
	}
	virtual bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
		const CefKeyEvent& event,
		CefEventHandle os_event,
		bool* is_keyboard_shortcut) OVERRIDE;
	virtual bool OnKeyEvent(CefRefPtr<CefBrowser> browser,
		const CefKeyEvent& event,
		CefEventHandle os_event) OVERRIDE;

	//����Ҽ��˵�
	virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() //ʵ��  
	{
		return this;
	}
	virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefContextMenuParams> params,
		CefRefPtr<CefMenuModel> model) OVERRIDE;

	virtual bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefContextMenuParams> params,
		int command_id,
		EventFlags event_flags) OVERRIDE;

	// show dev tools
	void ShowDevelopTools(CefRefPtr<CefBrowser> browser, const CefPoint& inspect_element_at);
	void CloseDevelopTools(CefRefPtr<CefBrowser> browser);

	// close browser
	bool SimpleClient::DoClose(CefRefPtr<CefBrowser> browser);
	void SimpleClient::OnBeforeClose(CefRefPtr<CefBrowser> browser);

private:
	CefRefPtr<CefBrowser> m_cefBrowser;

	HWND hWnd_; //������Ϣ�ľ��

	IMPLEMENT_REFCOUNTING(SimpleClient);

};

