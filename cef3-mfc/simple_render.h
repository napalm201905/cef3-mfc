#include "include/cef_app.h"
#include "include/cef_client.h"
// cef_v8.h
#include "include/cef_v8.h"
#include "simple_v8handler.h"

class SimpleRender : public CefApp, public CefRenderProcessHandler
{
public:
	SimpleRender();
	CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE
	{
		return this;
	}
	void OnContextCreated(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context);

	void OnWebKitInitialized() OVERRIDE;

	bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message) OVERRIDE;

private:
	IMPLEMENT_REFCOUNTING(SimpleRender);
};
