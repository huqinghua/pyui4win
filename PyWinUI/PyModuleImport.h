#pragma once


class PyLog
{
public:
	static void LogText(LPCSTR pstrText)
	{
		LOGA(pstrText);
	}
};

class PyScript
{
public:
	std::string RunPy(std::string pyModule, std::string pyFunc);
};

void PyExtentInit();

class PyTest
{
public:
	void Test(PyLog* log)
	{
		log->LogText("from python");
	}
};


