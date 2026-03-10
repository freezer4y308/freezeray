#include <windows.h>
#include <filesystem>
#include <iostream>
#include <vector>
#include "config.hpp"
#include "fmt/base.h"
#include "fmt/format.h"
#include "fmt/color.h"
#include <system_error>
#include "../flogcat/flogcat.hpp"

namespace fs = std::filesystem;
const std::string b = "configs";
const std::string a = "amnezia-box.exe";
bool clear = 0;

std::vector<std::string> jsonFiles;

bool freezerayConfigs::ifCoreExists() {
    if (std::filesystem::exists(a)) {
        return 0;
    }
    else {
     fmt::print("[freezeray.config] [FATAL] Core not found. System fault.\n");
     throw fmt::system_error(errno, "Core not found\n");

    }

}
char freezerayConfigs::IfFolderExist() {
    jsonFiles.clear();

    try {
        if (std::filesystem::exists(b) && fs::is_directory(b) && !fs::is_empty(b) && clear == 0) {
            fmt::print("[freezeray.config] [INFO] All requirements are met, towarding to next directory.\n");
            flogcat::AddToLog("[freezeray.config] [INFO] All requirements are met, towarding to next directory.\n");
            fs::path path = fs::current_path();
            fs::path path2 = "configs";
            fs::path path3 = path / path2;
            // Проверяем только .json файлы
            for (const auto& entry : fs::directory_iterator(path3)) {
                if (entry.is_regular_file() && entry.path().extension() == ".json") {
                    jsonFiles.push_back(entry.path().string());
                }
                clear = true;
            }

            if (jsonFiles.empty()) {
                fmt::print(fg(fmt::color::yellow),
                    "[freezeray.config] [WARNING] No JSON files found in directory.\n");
                flogcat::AddToLog("freezeray.config] [WARNING] No JSON files found in directory.\n");

                return 2;
            }
            return 0;
        }

        if (fs::exists(b) && fs::is_empty(b) && fs::is_directory(b)) {
            fmt::print("[freezeray.config] Directory is empty. Pass.\n");
            return 2;
        }

        else if (!std::filesystem::exists(b)) {
            fmt::print("[freezeray.config] [WARNING] Directory not found. Creating.\n");
            try {
                fs::create_directory(b);
            }
            catch (std::filesystem::filesystem_error const& exit) {
                fmt::print("[freezeray.config] [PANIC] Filesystem error. Error: {}\n", exit.what());
            }
            return 2;
        }
        else if (clear != 0) {
            fmt::print("[freezeray.config] [INFO] Configs was successfully refreshed\n");
            flogcat::AddToLog("[freezeray.config] [INFO] Configs was successfully refreshed\n");
            fs::path path = fs::current_path();
            fs::path path2 = "configs"; 
            fs::path path3 = path / path2;

            // Проверяем только .json файлы
            for (const auto& entry : fs::directory_iterator(path3)) {
                if (entry.is_regular_file() && entry.path().extension() == ".json") {
                    jsonFiles.push_back(entry.path().string());
                }
            }
            return 0;
        }
    }
    catch (const std::exception& e) {
        fmt::print("[freezeray.config] [FATAL] Exception: {}\n", e.what());
        return -1;
    }

    return 0;
}

const std::vector<std::string>& freezerayConfigs::GetJsonFiles() {
    return jsonFiles;
}

/* Чем гуще лес, if else if else 

$$$$$$$$$$$x::                           .;X&&&&
$$$$$$$$$X:                                :$&&&
$$$$$$$:.                                    :x$
$$$$$X;               :;::;:.  ....           .+
$$$Xx+.              ..;xXx;:;XXx+;:..         .
$$X;::             ::;+x$&&&&&&&&$$Xx;:.
$$$;.            :+xX$$&&&&&&&&&&$$$Xxx+:      .
$$XX;        :;xXX$&&&&&&&&&&&&&&&&$$Xx+;      .
$$$$;       .;xxXX$$$&&&&&&&&&&&X;......:.     ;
$$$x        :+;..:;++++X$&&&&&$$$XXXXXx+..     .
$$$$.       ;+;xX$$$$XXXXX$&&$xx+;. .:;++:.    .
$$$$x.      ;+xxx;:.  xxxXx$$X++xX;.;+;:;;.   .;
$$$XX+.     ;xxx++xXXXX$&$xX$$x+X$$XXxxxx+:   .;
$$$$XXx;.   ;xXXX$$$$&&&$XXX$&$+xX$$$$$$Xx;   .+
$$$$$$Xxx;. :xX$&&&&&&&&$XXX$&$x+x$&&&&$$x;  ;.+
$$$$$$$Xxx. :+X$&&&&&&&&XxX$&&&Xx+x$&&&&$x;;x; $
$$$$$$$$XX$X;;x$&&&&&&&$XXX$&&&&x++X$$&$$x::. +&
$$$$$&&&&$+x$;xX$&&&&&$$XxxxX$Xx;xXXX$$$Xx.  X&&
$$$$$$&&&&$+  +X$$$$$$$$$$$$XxxxXXXXxxX$X+. +$&&
$$$$$$&&&&&X: .xX$$$x++XX$$$&&&$Xx+;x$$$x: :&&&&
$$$$$$&&&&&&&+ :xX$&$$Xxx+xxXXxxx+xxX$Xx:  x&&&&
$$$$$$&&&&&&&&$x++xX$$$X$$$XXXXXXXXxXX+:  ;&&&&&
$$$$$$$$&&&&&&&&&$;+xXX$$$$$&&&$$$XXx+.::.&&&&&&
$$$$$$$$$&&&&&&&&&+;:;xX$$$&&&&&$$Xx::++;.X&&&&&
$$$$$$$$$$&&&&&&&&&:;;:;x$$$$$XXxx:.;xxx+;+&&&&&
XXX$$$$$$$$$&&&&&&&X;;;;;::::::::;+xxxxxx+;+$&&&


*/