// This file implements the IDebugProperty Interface and Gateway for Python.
// Generated by makegw.py

#include "stdafx.h"
#include "PythonCOM.h"
#include "PythonCOMServer.h"
#include "PyIDebugProperties.h"

#define SET_INC_NONE(x) {Py_INCREF(Py_None);(x)=Py_None;}

PyObject *PyObject_FromDebugPropertyInfo(const DebugPropertyInfo *p)
{
	PyObject *obRet = PyTuple_New(6);
	PyObject *ob;
	if (p->m_dwValidFields & DBGPROP_INFO_NAME) {
		ob = PyWinObject_FromBstr(p->m_bstrName, TRUE);
		if (ob==NULL) goto error;
	} else
		SET_INC_NONE(ob);
	PyTuple_SET_ITEM(obRet, 0, ob);
	if (p->m_dwValidFields & DBGPROP_INFO_TYPE) {
		ob = PyWinObject_FromBstr(p->m_bstrType, TRUE);
		if (ob==NULL) goto error;
	} else
		SET_INC_NONE(ob);
	PyTuple_SET_ITEM(obRet, 1, ob);
	if (p->m_dwValidFields & DBGPROP_INFO_VALUE) {
		ob = PyWinObject_FromBstr(p->m_bstrValue, TRUE);
		if (ob==NULL) goto error;
	} else
		SET_INC_NONE(ob);
	PyTuple_SET_ITEM(obRet, 2, ob);
	if (p->m_dwValidFields & DBGPROP_INFO_FULLNAME) {
		ob = PyWinObject_FromBstr(p->m_bstrFullName, TRUE);
		if (ob==NULL) goto error;
	} else
		SET_INC_NONE(ob);
	PyTuple_SET_ITEM(obRet, 3, ob);
	if (p->m_dwValidFields & DBGPROP_INFO_ATTRIBUTES) {
		ob = PyInt_FromLong(p->m_dwAttrib);
		if (ob==NULL) goto error;
	} else
		SET_INC_NONE(ob);
	PyTuple_SET_ITEM(obRet, 4, ob);
	if (p->m_dwValidFields & DBGPROP_INFO_DEBUGPROP) {
		ob = PyCom_PyObjectFromIUnknown(p->m_pDebugProp, IID_IDebugProperty, /* bAddRef = */ FALSE);
		if (ob==NULL) goto error;
	} else
		SET_INC_NONE(ob);
	PyTuple_SET_ITEM(obRet, 5, ob);
	return obRet;
error:
	Py_XDECREF(obRet);
	return NULL;
}

BOOL PyObject_AsDebugPropertyInfo(PyObject *ob, DebugPropertyInfo *p)
{
	memset(p, 0, sizeof(*p));
	if (!PySequence_Check(ob)) {
		PyErr_SetString(PyExc_TypeError, "DebugProperty object must be a sequence");
		return FALSE;
	}
	int len = PySequence_Length(ob);
	if (len<1) {
		PyErr_SetString(PyExc_ValueError, "DebugProperty sequence must be at least 1");
		return FALSE;
	}
	PyObject *thisOb = PySequence_GetItem(ob, 0);
	if (thisOb==NULL) goto error;

	if (!PyWinObject_AsBstr(thisOb, &p->m_bstrName, TRUE))
		goto error;
	if (thisOb != Py_None) p->m_dwValidFields |= DBGPROP_INFO_NAME;
	Py_DECREF(thisOb);

	if (len<2) return TRUE;
	thisOb = PySequence_GetItem(ob, 1);
	if (thisOb==NULL) goto error;
	if (!PyWinObject_AsBstr(thisOb, &p->m_bstrType, TRUE))
		goto error;
	if (thisOb != Py_None) p->m_dwValidFields |= DBGPROP_INFO_TYPE;
	Py_DECREF(thisOb);

	if (len<3) return TRUE;
	thisOb = PySequence_GetItem(ob, 2);
	if (thisOb==NULL) goto error;
	if (!PyWinObject_AsBstr(thisOb, &p->m_bstrValue, TRUE))
		goto error;
	if (thisOb != Py_None) p->m_dwValidFields |= DBGPROP_INFO_VALUE;
	Py_DECREF(thisOb);

	if (len<4) return TRUE;
	thisOb = PySequence_GetItem(ob, 3);
	if (thisOb==NULL) goto error;
	if (!PyWinObject_AsBstr(thisOb, &p->m_bstrFullName, TRUE))
		goto error;
	if (thisOb != Py_None) p->m_dwValidFields |= DBGPROP_INFO_FULLNAME;
	Py_DECREF(thisOb);

	if (len<5) return TRUE;
	thisOb = PySequence_GetItem(ob, 4);
	if (thisOb==NULL) goto error;
	if (thisOb == Py_None)
		;
	else if (PyInt_Check(thisOb)) {
		p->m_dwAttrib = PyInt_AsLong(thisOb);
		p->m_dwValidFields |= DBGPROP_INFO_ATTRIBUTES;
	} else {
		PyErr_SetString(PyExc_TypeError, "Tuple item 5 (attributes) must be an integer or None");
		goto error;
	}
	Py_DECREF(thisOb);

	if (len<6) return TRUE;
	thisOb = PySequence_GetItem(ob, 5);
	if (thisOb==NULL) goto error;
	if (!PyCom_InterfaceFromPyInstanceOrObject(thisOb, IID_IDebugProperty, (void **)&p->m_pDebugProp, TRUE))
		goto error;
	if (thisOb != Py_None) p->m_dwValidFields |= DBGPROP_INFO_DEBUGPROP;
	Py_DECREF(thisOb);
	return TRUE;
error:
	Py_XDECREF(thisOb);
	if (p->m_bstrName) SysFreeString(p->m_bstrName);
	if (p->m_bstrType) SysFreeString(p->m_bstrType);
	if (p->m_bstrValue) SysFreeString(p->m_bstrValue);
	if (p->m_bstrFullName) SysFreeString(p->m_bstrFullName);
	if (p->m_pDebugProp) p->m_pDebugProp->Release();
	return FALSE;
}


// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyIDebugProperty::PyIDebugProperty(IUnknown *pdisp):
	PyIUnknown(pdisp)
{
	ob_type = &type;
}

PyIDebugProperty::~PyIDebugProperty()
{
}

/* static */ IDebugProperty *PyIDebugProperty::GetI(PyObject *self)
{
	return (IDebugProperty *)PyIUnknown::GetI(self);
}

// @pymethod |PyIDebugProperty|GetPropertyInfo|Description of GetPropertyInfo.
PyObject *PyIDebugProperty::GetPropertyInfo(PyObject *self, PyObject *args)
{
	IDebugProperty *pIDP = GetI(self);
	if ( pIDP == NULL )
		return NULL;
	// @pyparm int|dwFieldSpec||Description for dwFieldSpec
	// @pyparm int|nRadix||Description for nRadix
	DWORD dwFieldSpec;
	UINT nRadix;
	if ( !PyArg_ParseTuple(args, "ii:GetPropertyInfo", &dwFieldSpec, &nRadix) )
		return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	DebugPropertyInfo propertyInfo;
	hr = pIDP->GetPropertyInfo( dwFieldSpec, nRadix, &propertyInfo );
	PY_INTERFACE_POSTCALL;

	if ( FAILED(hr) )
		return OleSetOleError(hr);

	return PyObject_FromDebugPropertyInfo(&propertyInfo);

}

// @pymethod |PyIDebugProperty|GetExtendedInfo|Description of GetExtendedInfo.
PyObject *PyIDebugProperty::GetExtendedInfo(PyObject *self, PyObject *args)
{
	PyErr_SetString(PyExc_RuntimeError, "GetExtendedInfo is not implemented");
	return NULL;
/***
	IDebugProperty *pIDP = GetI(self);
	if ( pIDP == NULL )
		return NULL;
	// @pyparm int|cInfos||Description for cInfos
// *** The input argument rgguidExtendedInfo of type "GUID __RPC_FAR *" was not processed ***
//     The type 'GUID' (rgguidExtendedInfo) is unknown.
	ULONG cInfos;
	VARIANT rgvar;
	if ( !PyArg_ParseTuple(args, "i:GetExtendedInfo", &cInfos) )
		return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIDP->GetExtendedInfo( cInfos, rgguidExtendedInfo, &rgvar );
	PY_INTERFACE_POSTCALL;

	if ( FAILED(hr) )
		return OleSetOleError(hr);
	PyObject *obrgvar;

	PyObject *pyretval = Py_BuildValue("O", obrgvar);
	Py_XDECREF(obrgvar);
	return pyretval;
**/
}

// @pymethod |PyIDebugProperty|SetValueAsString|Description of SetValueAsString.
PyObject *PyIDebugProperty::SetValueAsString(PyObject *self, PyObject *args)
{
	IDebugProperty *pIDP = GetI(self);
	if ( pIDP == NULL )
		return NULL;
	// @pyparm <o unicode>|pszValue||Description for pszValue
	// @pyparm int|nRadix||Description for nRadix
	PyObject *obpszValue;
	LPOLESTR pszValue;
	UINT nRadix;
	if ( !PyArg_ParseTuple(args, "Oi:SetValueAsString", &obpszValue, &nRadix) )
		return NULL;
	BOOL bPythonIsHappy = TRUE;
	if (!PyCom_BstrFromPyObject(obpszValue, &pszValue)) bPythonIsHappy = FALSE;
	if (!bPythonIsHappy) return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIDP->SetValueAsString( pszValue, nRadix );
	PY_INTERFACE_POSTCALL;
	SysFreeString(pszValue);

	if ( FAILED(hr) )
		return OleSetOleError(hr);
	Py_INCREF(Py_None);
	return Py_None;

}

// @pymethod |PyIDebugProperty|EnumMembers|Description of EnumMembers.
PyObject *PyIDebugProperty::EnumMembers(PyObject *self, PyObject *args)
{
	IDebugProperty *pIDP = GetI(self);
	if ( pIDP == NULL )
		return NULL;
	// @pyparm int|dwFieldSpec||Description for dwFieldSpec
	// @pyparm int|nRadix||Description for nRadix
	// @pyparm <o PyIID>|refiid||Description for refiid
	PyObject *obrefiid;
	DWORD dwFieldSpec;
	UINT nRadix;
	IID refiid;
	IEnumDebugPropertyInfo * ppepi;
	if ( !PyArg_ParseTuple(args, "iiO:EnumMembers", &dwFieldSpec, &nRadix, &obrefiid) )
		return NULL;
	BOOL bPythonIsHappy = TRUE;
	if (!PyWinObject_AsIID(obrefiid, &refiid)) bPythonIsHappy = FALSE;
	if (!bPythonIsHappy) return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIDP->EnumMembers( dwFieldSpec, nRadix, refiid, &ppepi );
	PY_INTERFACE_POSTCALL;

	if ( FAILED(hr) )
		return OleSetOleError(hr);
	PyObject *obppepi;

	obppepi = PyCom_PyObjectFromIUnknown(ppepi, IID_IEnumDebugPropertyInfo, FALSE);
	PyObject *pyretval = Py_BuildValue("O", obppepi);
	Py_XDECREF(obppepi);
	return pyretval;
}

// @pymethod |PyIDebugProperty|GetParent|Description of GetParent.
PyObject *PyIDebugProperty::GetParent(PyObject *self, PyObject *args)
{
	IDebugProperty *pIDP = GetI(self);
	if ( pIDP == NULL )
		return NULL;
	IDebugProperty * ppDebugProp;
	if ( !PyArg_ParseTuple(args, ":GetParent") )
		return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIDP->GetParent( &ppDebugProp );
	PY_INTERFACE_POSTCALL;

	if ( FAILED(hr) )
		return OleSetOleError(hr);
	PyObject *obppDebugProp;

	obppDebugProp = PyCom_PyObjectFromIUnknown(ppDebugProp, IID_IDebugProperty, FALSE);
	PyObject *pyretval = Py_BuildValue("O", obppDebugProp);
	Py_XDECREF(obppDebugProp);
	return pyretval;
}

// @object PyIDebugProperty|Description of the interface
static struct PyMethodDef PyIDebugProperty_methods[] =
{
	{ "GetPropertyInfo", PyIDebugProperty::GetPropertyInfo, 1 }, // @pymeth GetPropertyInfo|Description of GetPropertyInfo
	{ "GetExtendedInfo", PyIDebugProperty::GetExtendedInfo, 1 }, // @pymeth GetExtendedInfo|Description of GetExtendedInfo
	{ "SetValueAsString", PyIDebugProperty::SetValueAsString, 1 }, // @pymeth SetValueAsString|Description of SetValueAsString
	{ "EnumMembers", PyIDebugProperty::EnumMembers, 1 }, // @pymeth EnumMembers|Description of EnumMembers
	{ "GetParent", PyIDebugProperty::GetParent, 1 }, // @pymeth GetParent|Description of GetParent
	{ NULL }
};

PyComTypeObject PyIDebugProperty::type("PyIDebugProperty",
		&PyIUnknown::type,
		sizeof(PyIDebugProperty),
		PyIDebugProperty_methods,
		GET_PYCOM_CTOR(PyIDebugProperty));
// ---------------------------------------------------
//
// Gateway Implementation

STDMETHODIMP PyGDebugProperty::GetPropertyInfo(
		/* [in] */ DWORD dwFieldSpec,
		/* [in] */ UINT nRadix,
		/* [out] */ DebugPropertyInfo __RPC_FAR * pPropertyInfo)
{
	PY_GATEWAY_METHOD;
	PyObject *result;
	HRESULT hr=InvokeViaPolicy("GetPropertyInfo", &result, "ii", dwFieldSpec, nRadix);
	if (FAILED(hr)) return hr;
	// Process the Python results, and convert back to the real params
	if (!PyObject_AsDebugPropertyInfo(result, pPropertyInfo))
		hr = PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
	Py_DECREF(result);
	return hr;
}

STDMETHODIMP PyGDebugProperty::GetExtendedInfo(
		/* [in] */ ULONG cInfos,
		/* [size_is][in] */ GUID __RPC_FAR * rgguidExtendedInfo,
		/* [size_is][out] */ VARIANT __RPC_FAR * rgvar)
{
	return E_NOTIMPL;
/***
	PY_GATEWAY_METHOD;
// *** The input argument rgguidExtendedInfo of type "GUID __RPC_FAR *" was not processed ***
//   - None will always be passed to the Python function as a placeholder
//   - The type 'GUID' (rgguidExtendedInfo) is unknown.
	PyObject *result;
	HRESULT hr=InvokeViaPolicy("GetExtendedInfo", &result, "iz", cInfos, NULL);
	if (FAILED(hr)) return hr;
	// Process the Python results, and convert back to the real params
	PyObject *obrgvar;
	if (!PyArg_Parse(result, "O" , &obrgvar)) return PyCom_HandlePythonFailureToCOM();
	BOOL bPythonIsHappy = TRUE;
	if ( !PyCom_VariantFromPyObject(obrgvar, rgvar) )
		bPythonIsHappy = FALSE;
	if (!bPythonIsHappy) hr = PyCom_HandlePythonFailureToCOM();
	Py_DECREF(result);
	return hr;
***/
}

STDMETHODIMP PyGDebugProperty::SetValueAsString(
		/* [in] */ LPCOLESTR pszValue,
		/* [in] */ UINT nRadix)
{
	PY_GATEWAY_METHOD;
	PyObject *obpszValue;
	obpszValue = PyWinObject_FromOLECHAR(pszValue);
	HRESULT hr=InvokeViaPolicy("SetValueAsString", NULL, "Oi", obpszValue, nRadix);
	Py_XDECREF(obpszValue);
	return hr;
}

STDMETHODIMP PyGDebugProperty::EnumMembers(
		/* [in] */ DWORD dwFieldSpec,
		/* [in] */ UINT nRadix,
		/* [in] */ REFIID refiid,
		/* [out] */ IEnumDebugPropertyInfo __RPC_FAR *__RPC_FAR * ppepi)
{
	PY_GATEWAY_METHOD;
	if (ppepi==NULL) return E_POINTER;
	PyObject *obrefiid;
	obrefiid = PyWinObject_FromIID(refiid);
	PyObject *result;
	HRESULT hr=InvokeViaPolicy("EnumMembers", &result, "iiO", dwFieldSpec, nRadix, obrefiid);
	Py_XDECREF(obrefiid);
	if (FAILED(hr)) return hr;
	// Process the Python results, and convert back to the real params
	PyObject *obppepi;
	if (!PyArg_Parse(result, "O" , &obppepi)) return PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
	BOOL bPythonIsHappy = TRUE;
	if (!PyCom_InterfaceFromPyInstanceOrObject(obppepi, IID_IEnumDebugPropertyInfo, (void **)ppepi, TRUE /* bNoneOK */))
		 bPythonIsHappy = FALSE;
	if (!bPythonIsHappy) hr = PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
	Py_DECREF(result);
	return hr;
}

STDMETHODIMP PyGDebugProperty::GetParent(
		/* [out] */ IDebugProperty __RPC_FAR *__RPC_FAR * ppDebugProp)
{
	PY_GATEWAY_METHOD;
	if (ppDebugProp==NULL) return E_POINTER;
	PyObject *result;
	HRESULT hr=InvokeViaPolicy("GetParent", &result);
	if (FAILED(hr)) return hr;
	// Process the Python results, and convert back to the real params
	PyObject *obppDebugProp;
	if (!PyArg_Parse(result, "O" , &obppDebugProp)) return PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
	BOOL bPythonIsHappy = TRUE;
	if (!PyCom_InterfaceFromPyInstanceOrObject(obppDebugProp, IID_IDebugProperty, (void **)ppDebugProp, TRUE /* bNoneOK */))
		 bPythonIsHappy = FALSE;
	if (!bPythonIsHappy) hr = PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
	Py_DECREF(result);
	return hr;
}
