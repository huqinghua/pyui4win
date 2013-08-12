#include "StdAfx.h"

extern void python_duistring_registration();
extern void python_controlui_registration();
void duilib_registration()
{
	python_duistring_registration();
	python_controlui_registration();
}