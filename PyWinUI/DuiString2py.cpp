#include "stdafx.h"
#include<boost/python.hpp>

namespace bp = boost::python;

struct duistring_to_pystr {
	static PyObject *convert( const CDuiString &s );
	static PyTypeObject const* get_pytype();
};

struct duistring_from_pystr {
	static void *convertible( PyObject *object );
	static void construct( PyObject *object, boost::python::converter::rvalue_from_python_stage1_data *data );
};

void python_duistring_registration() {
	static bool executed = false;
	if ( !executed ) {
		executed = true;
		using namespace boost::python;

		converter::registry::push_back(
			duistring_from_pystr::convertible, duistring_from_pystr::construct,
			type_id< CDuiString >()
			);
		to_python_converter< CDuiString, duistring_to_pystr, false >();
	}
}

PyObject *duistring_to_pystr::convert( const CDuiString &s ) {
	return PyString_FromString( s.GetData());
}
PyTypeObject const *duistring_to_pystr::get_pytype() {
	return &PyString_Type;
}

void *duistring_from_pystr::convertible( PyObject *object ) {
	if (!PyString_Check(object))  
		return NULL;  
	return object;  
}

void duistring_from_pystr::construct( PyObject *object, boost::python::converter::rvalue_from_python_stage1_data *data ) {
	const char* value = PyString_AsString(object);  
	if (!value)  
		boost::python::throw_error_already_set();  
	void *storage = reinterpret_cast<
		boost::python::converter::rvalue_from_python_storage< CDuiString >*
	>( data )->storage.bytes;
	new (storage) CDuiString( value );
	data->convertible = storage;
}

