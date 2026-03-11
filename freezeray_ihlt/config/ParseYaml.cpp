#include <yaml-cpp/yaml.h>
#include "config.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <stdexcept>
#include <csetjmp>
#include <filesystem>
#include <windows.h>
#include <shellapi.h>
#include "..\main\main.hpp"
#include "parseYaml.hpp"
#include "fmt/base.h"
#include "fmt/color.h"
#include "../flogcat/flogcat.hpp"
#define YAML_CPP_DLL

namespace fs = std::filesystem;

string confname = "config.yml";
bool firstlaunch;
extern bool logsEnabled;
string language;

int fyamlparser::YAMLCheckConfig() {
	if (!fs::is_regular_file(confname) && fs::exists(confname)) {
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
			"[freezeray.yaml] [PANIC] Config file is not a regular file.");
		fyamlparser::fsError();
	}

	if (fs::is_empty(confname) || !fs::exists(confname)) {
		fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow),
			"[freezeray.yaml] [WARNING] Config file is empty or does not exist. Loading defaults.");
		firstlaunch == 1;
		logsEnabled == 1;

		return 1;
	}
}

char fyamlparser::YAMLLoadFiles() {
	int UserIsStupid = 173;
	int isSuccess = fyamlparser::YAMLCheckConfig();

	if (isSuccess == 0) {
		YAML::Node config = YAML::LoadFile(confname);


		/*

		TODO: Punch author of yaml-cpp library because he forced me to make this yanderedev-like if else
		mess. And also authors of C++ because for some reason you can't use strings in switch cases. Well,
		technically, you can use char, but the code just crashes if i use it lmao

		UPD: Oh! Fuck. This lib is hilariously bad, i guess i will switch to something else.

		*/



		if (config["firstlaunch"] = "yes") {
			firstlaunch == true;
		}
		else if (config["firstlaunch"] = "no") {
			firstlaunch == false;
		}
		else {
			firstlaunch == false;
		}


		if (config["logsEnabled"] = "yes") {
			logsEnabled == 1;
		}
		else if (config["logsEnabled"] = "no") {
			logsEnabled == 0;
		}
		else {
			logsEnabled == 0;
		}

		if (config["language"] = "eng") {
			language == "english";
		}
		else {
			language == "english";
		}
		return 0;


	}
	return 0;
}

int fyamlparser::fsError() {
	int msgboxID = MessageBox(
		NULL,
		(LPCWSTR)L"Config file is not a regular file. Panic.", // description
		(LPCWSTR)L"[freezeray.error]", // title
		MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
	);

	switch (msgboxID)
	{
	case IDCANCEL:
		exit(EXIT_FAILURE);
		break;
	case IDTRYAGAIN:
		fyamlparser::YAMLCheckConfig();
		break;
	case IDCONTINUE:
		exit(EXIT_FAILURE);
		break;
	}

	return msgboxID;
}
