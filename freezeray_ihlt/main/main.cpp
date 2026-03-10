#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengles2.h>
#include <SDL3/SDL_opengl.h>
#include "main.hpp"
#include <windows.h>
#include "../idk/ltt.h"
#include <filesystem>
#include "../config/config.hpp"
#include "fmt/base.h"
#include "fmt/format.h"
#include "fmt/printf.h"

void AlignForWidth(float width)
{
    float alignment = 0.5f;
    ImGuiStyle& style = ImGui::GetStyle();
    float avail = ImGui::GetContentRegionAvail().x;
    float off = (avail - width) * alignment;
    if (off > 0.0f)
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
}

void main_loop() {
    ImGui::PushFont(font);
    // Create fullscreen dockspace FIRST
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiWindowFlags dockspace_flags = ImGuiWindowFlags_NoDocking;
    dockspace_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
    dockspace_flags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    dockspace_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("DockSpaceWindow", nullptr, dockspace_flags);
    ImGui::PopStyleVar(3);

    ImGuiID dockspace_id = ImGui::GetID("My Dockspace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
    ImGui::End(); 

    auto butt{ SDL_GetGlobalMouseState(nullptr, nullptr) }; /* nullptr nullptr nullptr */

    if (butt & SDL_BUTTON_RMASK) {
        ImGui::OpenPopup("my_file_popup");
    }

    static char returnValue = -1;
    static bool configs_loaded = false;
    if (!configs_loaded) {
        returnValue = 0;
        configs_loaded = true;
    }

        menubar();
        if (ImGui::BeginPopup("my_file_popup", ImGuiWindowFlags_MenuBar))
        {
            if (ImGui::MenuItem("Connect")) {}
            if (ImGui::MenuItem("Disconnect")) {}
            if (ImGui::MenuItem("Delete")) {}
            if (ImGui::MenuItem("Clone")) {}
            if (ImGui::MenuItem("Aw dang it")) {}
            ImGui::EndPopup();
        }

        static bool no_collapse = true;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
        if (no_collapse) window_flags |= ImGuiWindowFlags_NoCollapse;

        if (ImGui::Begin("Console", nullptr, window_flags)) {
            static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
            static char text[] = "[dev build]";
            ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), flags);
        }
        ImGui::End();

        if (ImGui::Begin("Status", nullptr, window_flags)) {
            ImGui::Text("Status: Success i guess");
            ImGui::Text("Status: Success i guess");
            ImGui::Text("Status: Success i guess");
            ImGui::Text("Status: Success i guess");
            ImGui::Text("Status: Success i guess");
            ImGui::Text("Status: Success i guess");
            ImGui::Text("Status: Success i guess");
            ImGui::Text("Status: Success i guess");
        }
        ImGui::End();

        if (ImGui::Begin("Proxies", nullptr, window_flags)) {
            ImGui::SeparatorText("Active configs");
            ImGui::Text("Netgraph");
            ImGui::Text("Status");
            ImGui::SeparatorText("Debug tools");
            ImGui::Text("Debug tools :)");
        }
        ImGui::End();

        if (ImGui::Begin("Statss", nullptr, window_flags)) {
            ImGui::SeparatorText("Active configs");

            const auto& jsonFiles = freezerayConfigs::GetJsonFiles();

            static bool need_refresh = false;
            if (ImGui::Button("Refresh configs")) {
                need_refresh = true;
            }

            if (jsonFiles.empty()) {
                ImGui::Text("No JSON config files found.");
            }
            else {
                for (size_t i = 0; i < jsonFiles.size(); i++) {
                    const auto& filePath = jsonFiles[i];
                    std::filesystem::path p(filePath);
                    std::string fileName = p.filename().string();

                    ImGui::PushID(static_cast<int>(i));
                    if (ImGui::TreeNode("##node", "%s", fileName.c_str())) {
                        ImGui::Text("Path: %s", filePath.c_str());
                        if (ImGui::Button("error")) {
                         // printf("Selected file: %s\n", fileName.c_str());
                         system(("start amnezia-box.exe run -c " + fileName).c_str());
                         
                        // TODO: fix this shitcode
                            
                        }
                        ImGui::TreePop();
                    }
                    ImGui::PopID();
                }
            }

            if (need_refresh) {
                freezerayConfigs::IfFolderExist();
                need_refresh = false;
            }
        }
        ImGui::PopFont();
        ImGui::End();
    }

int main(int argc, char* argv[]) {
        init_main();
        // todo: implement arguments
    return 0;
}