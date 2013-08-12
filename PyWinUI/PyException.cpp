#include "stdafx.h"
#include <exdisp.h>
#include <comdef.h>
#include <string>
#include "WinSys.h"
#include <shellapi.h>
#include "Util.h"

#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

#include <boost/python.hpp>
#include "PyException.h"

std::string parse_python_exception()
{  
	PyObject *type_ptr = NULL, *value_ptr = NULL, *traceback_ptr = NULL;  
	PyErr_Fetch(&type_ptr, &value_ptr, &traceback_ptr);  
	std::string ret("Unfetchable Python error");  
	if(type_ptr != NULL){  
		boost::python::handle<> h_type(type_ptr);  
		boost::python::str type_pstr(h_type);  
		boost::python::extract<std::string> e_type_pstr(type_pstr);  
		if(e_type_pstr.check())  
			ret = e_type_pstr();  
		else  
			ret ="Unknown exception type";  
	}  

	if(value_ptr != NULL){  
		boost::python::handle<> h_val(value_ptr);  
		boost::python::str a(h_val);  
		boost::python::extract<std::string> returned(a);  
		if(returned.check())  
			ret += ": " + returned();  
		else  
			ret += std::string(": Unparseable Python error: ");  
	}  

	if(traceback_ptr != NULL){  
		boost::python::handle<> h_tb(traceback_ptr);  
		boost::python::object tb(boost::python::import("traceback"));  
		boost::python::object fmt_tb(tb.attr("format_tb"));  
		boost::python::object tb_list(fmt_tb(h_tb));  
		boost::python::object tb_str(boost::python::str("\n").join(tb_list));  
		boost::python::extract<std::string> returned(tb_str);  
		if(returned.check())  
			ret +=": " + returned();  
		else  
			ret += std::string(": Unparseable Python traceback");  
	}  
	return ret;  
}
