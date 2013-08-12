#include "stdafx.h"
#include<boost/python.hpp>
#include "duilib-python.h"

namespace bp = boost::python;

struct controlui_to_py {
	static PyObject *convert( const PControlUI &s );
	static PyTypeObject const* get_pytype();
};

struct controlui_from_py {
	static void *convertible( PyObject *object );
	static void construct( PyObject *object, boost::python::converter::rvalue_from_python_stage1_data *data );
};

void python_controlui_registration() {
	static bool executed = false;
	if ( !executed ) {
		executed = true;
		using namespace boost::python;

		converter::registry::push_back(
			controlui_from_py::convertible, controlui_from_py::construct,
			type_id< PControlUI >()
			);
		to_python_converter< PControlUI, controlui_to_py, false >();
	}
}

PyObject *controlui_to_py::convert( const PControlUI &s ) {
	return PyLong_FromLong( (long)s);
}
PyTypeObject const *controlui_to_py::get_pytype() {
	return &PyLong_Type;
}

void *controlui_from_py::convertible( PyObject *object ) {
	return object;
}

void controlui_from_py::construct( PyObject *object, boost::python::converter::rvalue_from_python_stage1_data *data ) {
	int pControl = PyLong_AsLong(object);
	
	void *storage = reinterpret_cast<
		boost::python::converter::rvalue_from_python_storage< PControlUI >*
	>( data )->storage.bytes;
	new (storage) long( pControl );
	data->convertible = storage;
}

