#define _CRT_SECURE_NO_WARNINGS // Fuck "secure warnings"
#include <filesystem>
#include <fmt/base.h>
#include <fmt/chrono.h>
#include <fmt/std.h>
#include <fmt/color.h>
#include <windows.h>
#include <winuser.h>
#include <string>

#define elif else if

/*
Wow, i wrote some sort of "good" code without vibecoding.

*/

using namespace std;

class flogcat {
public:
	static int InitLog();
	static int fsError();
    static int TimeNow(void);
	static int AddToLog(const char* logValue);
};

bool LogsEnabled = 1;

using namespace std::chrono;
time_point now = system_clock::now();


string tim = fmt::format("{:%Y_%m_%d_%H_%M_%S}.log", now);

int flogcat::InitLog() {
		if (std::filesystem::exists("logs")) {
            fmt::print("[freezeray.logcat] [INFO] flogcat started\n");
            flogcat::AddToLog("[freezeray.logcat] [INFO] flogcat started\n");
		}
		else {
			try {
                
				fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow),
                    "[freezeray.logcat] [WARNING] logs does not exist. Creating.\n");
				std::filesystem::create_directory("logs");
                
                return 0;
			}
			catch (std::filesystem::filesystem_error const& exit) {
				fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
                    "[freezeray.logcat] [ERROR] Filesystem error. Error: {}\n", exit.what());
                flogcat::fsError();

			}
		}
}
int flogcat::fsError() {
    int msgboxID = MessageBox(
        NULL,
        (LPCWSTR)L"Filesystem error! Can't open logs\nDo you want to try again?", // description
        (LPCWSTR)L"[freezeray.error]", // title
        MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
    );

    switch (msgboxID)
    {
    case IDCANCEL:
        exit(-18);
        break;
    case IDTRYAGAIN:
        flogcat::InitLog();
        break;
    case IDCONTINUE:
        LogsEnabled = 0;
        break;
    }

    return msgboxID;
}


int flogcat::AddToLog(const char* logValue) {
    if (logValue == NULL) {
        return 1;
    }

    if (LogsEnabled == 1) {
        std::filesystem::path path{ "logs" };
        path /= tim;

        std::filesystem::create_directories(path.parent_path());

        std::ofstream ofs(path, std::ios::app);  
        ofs << logValue;
        ofs.close();
        return 0;
    }

    else if (LogsEnabled == 0) {
        return 0;
    }

    return 0;
}