#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengles2.h>
#include <SDL3/SDL_opengl.h>
#include "main.hpp"
#include <windows.h>
#include "../idk/ltt.h"
#include <filesystem>
#include "../config/config.hpp"
#include "../idk/IconsFontAwesome7.h"
#include "../idk/IconsMaterialSymbols.h"
#include <io.h>
#include <fcntl.h>
#include <iostream>

static bool its_showtime = 0;


void menubar() {
    extern int init_main();
    extern void settings(bool* p_open);
    static bool show_settings = false;
    if (ImGui::BeginMainMenuBar()) {
        ImGui::PushFont(font);

        if (ImGui::BeginMenu("\uf02d Proxy")) {
            if (ImGui::MenuItem("\uf067 Add config...")) {}
            if (ImGui::MenuItem("\uf0ea Use config from clipboard...", "Ctrl+V")) {
                OpenClipboard(NULL);
                auto clipboardData = GetClipboardData(CF_UNICODETEXT);
                std::cout << clipboardData << "\n";
                CloseClipboard();
               

            }
            if (ImGui::MenuItem("\uead2 Restart service", "Ctrl+R")) {}
            if (ImGui::MenuItem("\ueb90 Restart program", "F5")) {
                system("x64\\Debug\\freezeray_ihlt.exe");
                exit(0);
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("\uf013 Settings")) {
            if (ImGui::MenuItem("General")) { show_settings = true; }
            if (ImGui::MenuItem("Keybinds", "Alt+F4")) {}
            if (ImGui::MenuItem("Change Theme")) {}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("\ued0a Donate")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("\uead2 Update")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("\U000F06B0 Help")) {
            if (ImGui::MenuItem("\uead2 Software info")) {
                its_showtime = 1;
            }
 
            ImGui::EndMenu();
        }

 if (ImGui::BeginMenu("\ueb9b DEBUG")) {
            ImGui::ShowDemoWindow();
            ImGui::EndMenu();
        }
 ImGui::PopFont();
        ImGui::EndMainMenuBar();
    }




    if (its_showtime) {
        ImGui::Begin("About", &its_showtime);
        ImGui::Text("freezeray v1.0.0-alpha1");

        ImGui::End();
    }
}