#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengles2.h>
#include <SDL3/SDL_opengl.h>
#include "main.hpp"

void settings(bool* p_open) {
    bool some_bool = false;
    if (!ImGui::Begin("Settings", p_open, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::End();
        return;
    }

    ImGui::Text("This is some useful text.");
    ImGui::Checkbox("Some option", &some_bool);
    ImGui::End(); 
}