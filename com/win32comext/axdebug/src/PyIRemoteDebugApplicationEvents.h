// This file declares the IRemoteDebugApplicationEvents Interface and Gateway for Python.
// Generated by makegw.py
// ---------------------------------------------------
//
// Interface Declaration

class PyIRemoteDebugApplicationEvents : public PyIUnknown
{
public:
	MAKE_PYCOM_CTOR(PyIRemoteDebugApplicationEvents);
	static IRemoteDebugApplicationEvents *GetI(PyObject *self);
	static PyComTypeObject type;

	// The Python methods
	static PyObject *OnConnectDebugger(PyObject *self, PyObject *args);
	static PyObject *OnDisconnectDebugger(PyObject *self, PyObject *args);
	static PyObject *OnSetName(PyObject *self, PyObject *args);
	static PyObject *OnDebugOutput(PyObject *self, PyObject *args);
	static PyObject *OnClose(PyObject *self, PyObject *args);
	static PyObject *OnEnterBreakPoint(PyObject *self, PyObject *args);
	static PyObject *OnLeaveBreakPoint(PyObject *self, PyObject *args);
	static PyObject *OnCreateThread(PyObject *self, PyObject *args);
	static PyObject *OnDestroyThread(PyObject *self, PyObject *args);
	static PyObject *OnBreakFlagChange(PyObject *self, PyObject *args);

protected:
	PyIRemoteDebugApplicationEvents(IUnknown *pdisp);
	~PyIRemoteDebugApplicationEvents();
};
// ---------------------------------------------------
//
// Gateway Declaration

class PyGRemoteDebugApplicationEvents : public PyGatewayBase, public IRemoteDebugApplicationEvents
{
protected:
	PyGRemoteDebugApplicationEvents(PyObject *instance) : PyGatewayBase(instance) { ; }
	PYGATEWAY_MAKE_SUPPORT(PyGRemoteDebugApplicationEvents, IRemoteDebugApplicationEvents, IID_IRemoteDebugApplicationEvents)

	// IRemoteDebugApplicationEvents
	STDMETHOD(OnConnectDebugger)(
		IApplicationDebugger __RPC_FAR * pad);

	STDMETHOD(OnDisconnectDebugger)(
		void);

	STDMETHOD(OnSetName)(
		LPCOLESTR pstrName);

	STDMETHOD(OnDebugOutput)(
		LPCOLESTR pstr);

	STDMETHOD(OnClose)(
		void);

	STDMETHOD(OnEnterBreakPoint)(
		IRemoteDebugApplicationThread __RPC_FAR * prdat);

	STDMETHOD(OnLeaveBreakPoint)(
		IRemoteDebugApplicationThread __RPC_FAR * prdat);

	STDMETHOD(OnCreateThread)(
		IRemoteDebugApplicationThread __RPC_FAR * prdat);

	STDMETHOD(OnDestroyThread)(
		IRemoteDebugApplicationThread __RPC_FAR * prdat);

	STDMETHOD(OnBreakFlagChange)(
		APPBREAKFLAGS abf,
		IRemoteDebugApplicationThread __RPC_FAR * prdatSteppingThread);

};
