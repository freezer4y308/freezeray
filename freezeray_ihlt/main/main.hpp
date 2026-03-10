#pragma once
#pragma twice
#define ulong64_t long long
#ifdef __cplusplus
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

int main(int argc, char* argv[]);
void menubar();
void settings(bool* p_open = nullptr);
void debugconsole();
int init_main();
void main_loop();
extern ImFont* font;
void windows();
#endif

