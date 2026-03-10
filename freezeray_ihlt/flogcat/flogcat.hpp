#pragma once
#pragma lastest

using namespace std;

class flogcat {
public:
	static int InitLog();
	static int fsError();
	static int AddToLog(const char* logValue);
};
