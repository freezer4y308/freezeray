#define _HAS_STD_BYTE 0
#include "main.hpp"
#include "init.hpp"
#include "..\config\config.hpp"
#include "../flogcat/flogcat.hpp"
#include "..\config\parseYaml.hpp"


void define() {

}

int init_main()
{
    freezerayConfigs::ifCoreExists();

    flogcat::InitLog();

    fyamlparser::YAMLLoadFiles();

    freezerayConfigs::IfFolderExist();

   // mainFunction();

     init::InitGUI();

    return 0;
}