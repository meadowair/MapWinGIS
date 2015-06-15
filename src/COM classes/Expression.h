#pragma once
#include "CustomExpression.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

class ATL_NO_VTABLE CExpression :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CExpression, &CLSID_Expression>,
	public IDispatchImpl<IExpression, &IID_IExpression, &LIBID_MapWinGIS, /*wMajor =*/ VERSION_MAJOR, /*wMinor =*/ VERSION_MINOR>
{
public:
	CExpression()
		: _lastErrorPosition(-1)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_EXPRESSION)

	BEGIN_COM_MAP(CExpression)
		COM_INTERFACE_ENTRY(IExpression)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	STDMETHOD(Parse)(BSTR expr, VARIANT_BOOL* retVal);
	STDMETHOD(Evaluate)(VARIANT* result, VARIANT_BOOL* retVal);
	STDMETHOD(get_LastErrorMessage)(BSTR* pVal);
	STDMETHOD(get_LastErrorPosition)(LONG* pVal);
	STDMETHOD(get_NumSupportedFunctions)(LONG* pVal);
	STDMETHOD(get_SupportedFunction)(LONG functionIndex, IFunction** pVal);

private:
	CustomExpression _expression;
	CString _lastErrorMessage;
	int _lastErrorPosition;
};

OBJECT_ENTRY_AUTO(__uuidof(Expression), CExpression)
