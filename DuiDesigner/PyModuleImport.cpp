#include "stdafx.h"


#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

#include<boost/python.hpp>
#include "PyModuleImport.h"
#include "PyException.h"

using namespace std;
using namespace boost::python;


BOOST_PYTHON_MODULE(PyUI)
{
	class_<PyLog>("PyLog")
		.def("LogText", &PyLog::LogText)
		;

	class_<PyScript>("PyScript")
		.def("RunPy", &PyScript::RunPy)
		;
}

void PyExtentInit()
{
	PyImport_AppendInittab("PyUI", initPyUI);
}

std::string PyScript::RunPy(std::string pyModule, std::string pyFunc)
{
	std::string ret = "";

	boost::python::handle<>* _module = NULL; // Module handle.

	try
	{
		_module = new boost::python::handle<>(
			PyImport_ImportModule( pyModule.c_str()));
		ret = boost::python::call_method<std::string>(_module->get(), pyFunc.c_str());
	}
	catch(boost::python::error_already_set const &){  
		ret = parse_python_exception();
		PyLog().LogText(ret.c_str());
		PyErr_Clear();
	}  
	catch (...)
	{
		if (PyErr_Occurred())
		{
			ret = parse_python_exception();
			PyLog().LogText(ret.c_str());
			PyErr_Clear();
		}
	}

	if (_module)
		delete _module;

	return ret;
}