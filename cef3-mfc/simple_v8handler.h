#include "include/cef_v8.h"
#include "include/cef_app.h"

class SimpleV8Handler : public CefV8Handler
{
public:
	SimpleV8Handler(CefRefPtr<CefApp> app);
	~SimpleV8Handler();
	virtual bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, 
		const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) override;
public:
	CefRefPtr<CefApp> app;
	IMPLEMENT_REFCOUNTING(SimpleV8Handler);
};

