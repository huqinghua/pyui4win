#pragma once


class PyLog
{
public:
	void LogText(LPCSTR pstrText)
	{
		//LOGA(pstrText);
	}
};

class PyScript
{
public:
	std::string RunPy(std::string pyModule, std::string pyFunc);
};

void PyExtentInit();
