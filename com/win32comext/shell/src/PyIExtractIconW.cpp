// This file implements the IExtractIconW Interface and Gateway for Python.
// Generated by makegw.py
#include "shell_pch.h"
#include "PyIExtractIconW.h"
// This is a clone of PyIExtractIcon, with simple replacements of
// 'TCHAR' with 'WCHAR' - that is easier than trying to force distutils to
// compile the same .cpp file twice with different settings!

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyIExtractIconW::PyIExtractIconW(IUnknown *pdisp):
	PyIUnknown(pdisp)
{
	ob_type = &type;
}

PyIExtractIconW::~PyIExtractIconW()
{
}

/* static */ IExtractIconW *PyIExtractIconW::GetI(PyObject *self)
{
	return (IExtractIconW *)PyIUnknown::GetI(self);
}

// @pymethod |PyIExtractIconW|Extract|Description of Extract.
PyObject *PyIExtractIconW::Extract(PyObject *self, PyObject *args)
{
	IExtractIconW *pIEI = GetI(self);
	if ( pIEI == NULL )
		return NULL;
	// @pyparm <o unicode>|pszFile||Description for pszFile
	// @pyparm int|nIconIndex||Description for nIconIndex
	// @pyparm int|nIconSize||Description for nIconIndex
	HICON hiconLarge;
	HICON hiconSmall;
	PyObject *obpszFile;
	WCHAR *pszFile;
	UINT nIconIndex;
	UINT nIconSize;
	if ( !PyArg_ParseTuple(args, "Oii:Extract", &obpszFile, &nIconIndex, &nIconSize) )
		return NULL;
	BOOL bPythonIsHappy = TRUE;
	if (!PyWinObject_AsWCHAR(obpszFile, &pszFile)) bPythonIsHappy = FALSE;
	if (!bPythonIsHappy) return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIEI->Extract( pszFile, nIconIndex, &hiconLarge, &hiconSmall, nIconSize );
	PyWinObject_FreeWCHAR(pszFile);
	PY_INTERFACE_POSTCALL;
	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, pIEI, IID_IExtractIconW );
	if (hr==S_FALSE)
		return Py_BuildValue("OO", Py_None, Py_None);
	return Py_BuildValue("ii", hiconLarge, hiconSmall);
	// @rdesc The result is (hicon_large, hicon_small), or
	// (None,None) if the underlying function returns S_FALSE, indicating
	// the calling application should extract it.
}

// @pymethod |PyIExtractIconW|GetIconLocation|Description of GetIconLocation.
PyObject *PyIExtractIconW::GetIconLocation(PyObject *self, PyObject *args)
{
	IExtractIconW *pIEI = GetI(self);
	if ( pIEI == NULL )
		return NULL;
	// @pyparm int|uFlags||Description for uFlags
	// @pyparm int|cchMax|MAX_PATH+MAX_FNAME|Buffer size to allocate for file name
	UINT uFlags;
	INT cchMax = MAX_PATH + _MAX_FNAME;
	if ( !PyArg_ParseTuple(args, "i|i:GetIconLocation", &uFlags, &cchMax))
		return NULL;
	WCHAR *buf = (WCHAR *)malloc(cchMax * sizeof(WCHAR));
	if (!buf)
		return PyErr_NoMemory();
	INT iIndex;
	UINT flags;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIEI->GetIconLocation( uFlags, buf, cchMax, &iIndex, &flags);
	PY_INTERFACE_POSTCALL;
	if ( FAILED(hr) ) {
		free(buf);
		return PyCom_BuildPyException(hr, pIEI, IID_IExtractIconW );
	}
	PyObject *retStr = PyWinObject_FromWCHAR(buf);
	free(buf);
	return Py_BuildValue("iNii", hr, retStr, iIndex, flags);
}

// @object PyIExtractIconW|Description of the interface
static struct PyMethodDef PyIExtractIconW_methods[] =
{
	{ "Extract", PyIExtractIconW::Extract, 1 }, // @pymeth Extract|Description of Extract
	{ "GetIconLocation", PyIExtractIconW::GetIconLocation, 1 }, // @pymeth GetIconLocation|Description of GetIconLocation
	{ NULL }
};

PyComTypeObject PyIExtractIconW::type("PyIExtractIconW",
		&PyIUnknown::type,
		sizeof(PyIExtractIconW),
		PyIExtractIconW_methods,
		GET_PYCOM_CTOR(PyIExtractIconW));
// ---------------------------------------------------
//
// Gateway Implementation
STDMETHODIMP PyGExtractIconW::Extract(
		/* [unique][in] */ LPCWSTR pszFile,
		/* [unique][in] */ UINT nIconIndex,
		/* [out] */ HICON * phiconLarge,
		/* [out] */ HICON * phiconSmall,
		/* [unique][in] */ UINT nIconSize)
{
	PY_GATEWAY_METHOD;
	PyObject *obpszFile;
	obpszFile = PyWinObject_FromWCHAR((LPWSTR)pszFile);
	PyObject *result;
	HRESULT hr=InvokeViaPolicy("Extract", &result, "Oii", obpszFile, nIconIndex, nIconSize);
	Py_XDECREF(obpszFile);
	if (FAILED(hr)) return hr;
	if (PyInt_Check(result) || PyLong_Check(result))
		hr = PyInt_AsLong(result);
	else {
		PyArg_ParseTuple(result, "ii", phiconLarge, phiconSmall);
		hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("Extract");
	}
	Py_DECREF(result);
	return hr;
}

STDMETHODIMP PyGExtractIconW::GetIconLocation(
		/* [unique][in] */ UINT uFlags,
		/* [unique][out] */ LPWSTR szIconFile,
		/* [unique][in] */ UINT cchMax,
		/* [unique][out] */ LPINT piIndex,
		/* [unique][out] */ UINT *pflags)
{
	PY_GATEWAY_METHOD;
	if (cchMax && szIconFile)
		szIconFile[0] = 0;
	*piIndex = 0;
	*pflags = 0;
	PyObject *result;
	HRESULT hr=InvokeViaPolicy("GetIconLocation", &result, "i", uFlags);
	if (FAILED(hr)) return hr;
	PyObject *obFileName;
	// Process the Python results, and convert back to the real params
	if (PyInt_Check(result) || PyLong_Check(result))
		hr = PyInt_AsLong(result);
	else {
		if (PyArg_ParseTuple(result, "Oii", &obFileName, piIndex, pflags)) {
			WCHAR *filename;
			if (PyWinObject_AsWCHAR(obFileName, &filename)) {
				wcsncpy(szIconFile, filename, cchMax);
				PyWinObject_FreeWCHAR(filename);
			}
		}
		hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetIconLocation");
	}
	Py_DECREF(result);
	return hr;
}

