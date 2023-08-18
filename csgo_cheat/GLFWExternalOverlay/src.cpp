// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs


#include <Windows.h>
#include "GL/glew.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#include "helper.h"
#include "utilities.h"
#include "WorldToScreen.h"
#include "tools.h"
#include "offsets.h"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> 


#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Main code
int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;



    const char* glsl_version = "#version 130";
  


    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize OpgenGL Loader");
    }


    GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
    if (!Monitor)
    {
        return 0;
    }

    glfwWindowHint(GLFW_FLOATING, true);
    glfwWindowHint(GLFW_MAXIMIZED, true);
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);
   

    int width = glfwGetVideoMode(Monitor)->width;
    int height = glfwGetVideoMode(Monitor)->height;

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(width, height, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (window == nullptr)
        return 1;

    glfwSetWindowAttrib(window, GLFW_DECORATED, false);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

   

    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;    
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    

    // Our state
    bool show_another_window = false;
    bool bMenuVisible = true;
    bool enable_enemy_esp = false;
    bool enable_team_esp = false;
    bool enable_enemy_healthbar = false;
    bool enable_enemy_armorbar = false;
    bool enable_team_healthbar = false;
    bool enable_team_armorbar = false;
    bool enable_fov = false;
    bool enable_no_flash = false;
    bool enable_thirdperson = false;
    float color_team_box[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
    float color_enemy_box[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
    float color_team_snaplines[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
    float color_enemy_snaplines[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
    bool enable_enemy_snaplines = false;
    bool enable_team_snaplines = false;
    bool enable_bhop = false;
    bool enable_radar = false;
    bool enable_triggerbot = false;
    bool enable_viewmodel_fov = false;
    int fov_value = 90;
    int viewmodel_fov_value = 90;

   


    DWORD procId = GetProcId(L"csgo.exe");

    if (procId)
        std::cout << "Process Found:" << procId << std::endl;

    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);

    

    game.module_base = GetModuleBaseAddr(procId, L"client.dll");
    plr.local_player = Memory::RPM<uintptr_t>(hProc, (game.module_base + hazedumper::signatures::dwLocalPlayer));
    game.entity_list = Memory::RPM<uintptr_t>(hProc, (game.module_base + hazedumper::signatures::dwEntityList));
    


    // Main loop
#ifdef __EMSCRIPTEN__
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(window))
#endif
    {

        
        glfwPollEvents();

        // Start the Dear ImGui frame
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            bMenuVisible = !bMenuVisible;


            if (bMenuVisible)
            {
                ShowMenu(window);
            }
            else
            {
                HideMenu(window);
            }
        }


        if(bMenuVisible)
        {
            //Draw menu
            ImGui::Begin("xphax", NULL, ImGuiWindowFlags_AlwaysAutoResize);

            ImGui::Checkbox("Team Box", &enable_team_esp);
            ImGui::Checkbox("Team Health Bar", &enable_team_healthbar);
            ImGui::Checkbox("Team Armor Bar", &enable_team_armorbar);


            ImGui::Checkbox("Enemy Box", &enable_enemy_esp);
            ImGui::Checkbox("Enemy Health Bar", &enable_enemy_healthbar);
            ImGui::Checkbox("Enemy Armor Bar", &enable_enemy_armorbar);



            ImGui::Checkbox("Enable Custom Fov", &enable_fov);
            if (enable_fov)
            {
                ImGui::SliderInt("Fov", &fov_value, 50, 200);
            }

            ImGui::Checkbox("Enable Custom Viewmodel Fov", &enable_viewmodel_fov);
            if (enable_viewmodel_fov)
            {
                ImGui::SliderInt("Viewmodel FOV", &viewmodel_fov_value, 50, 200);
            }

            ImGui::Checkbox("Thirdperson", &enable_thirdperson);

            ImGui::Checkbox("No Flash", &enable_no_flash);
            ImGui::ColorEdit4("Team Esp Color", color_team_box, 0);
            ImGui::ColorEdit4("Enemy Esp Color", color_enemy_box, 0);


            ImGui::Checkbox("Team Snaplines", &enable_team_snaplines);
            ImGui::Checkbox("Enemy Snaplines", &enable_enemy_snaplines);
            ImGui::ColorEdit4("Team Snaplines Color", color_team_snaplines, 0);
            ImGui::ColorEdit4("Enemy Snaplines Color", color_enemy_snaplines, 0);

            ImGui::Checkbox("Triggerbot", &enable_triggerbot);
            ImGui::Checkbox("Bhop",&enable_bhop);
            ImGui::Checkbox("Radar", &enable_radar);

            
        }
        else
        {

        }

        if (enable_triggerbot)
        {
            uintptr_t crosshair_id = Memory::RPM<uintptr_t>(hProc, (plr.local_player + hazedumper::netvars::m_iCrosshairId));

            if (crosshair_id > 0 && GetAsyncKeyState(VK_SHIFT))
            {
                Memory::WPM<uintptr_t>(hProc, (game.module_base + hazedumper::signatures::dwForceAttack), 6);
            }
        }
       
        if (enable_bhop)
        {
            uintptr_t flag = Memory::RPM<uintptr_t>(hProc, (plr.local_player + hazedumper::netvars::m_fFlags));
            if (GetAsyncKeyState(VK_SPACE) && flag & (1 << 0))
            {
                Memory::WPM<uintptr_t>(hProc, (game.module_base + hazedumper::signatures::dwForceJump), 6);
            }
        }

        plr.matrix = Memory::RPM<ViewMatrix>(hProc, (game.module_base + hazedumper::signatures::dwViewMatrix));
        plr.team_id = Memory::RPM<uintptr_t>(hProc, (plr.local_player + hazedumper::netvars::m_iTeamNum));


        for (unsigned int i = 1; i < 32; ++i)
        {
            
            entity.entity_base = Memory::RPM<uintptr_t>(hProc, (game.module_base + hazedumper::signatures::dwEntityList) + i * 0x10);

            if (entity.entity_base == NULL) continue;

            entity.health = Memory::RPM<uintptr_t>(hProc, (entity.entity_base + hazedumper::netvars::m_iHealth));
            entity.armor = Memory::RPM<uintptr_t>(hProc, (entity.entity_base + hazedumper::netvars::m_ArmorValue));

            if (entity.health <= 0) continue;

            if (enable_radar)
            {
                Memory::WPM<uintptr_t>(hProc, (entity.entity_base + hazedumper::netvars::m_bSpotted), 1);
            }

            entity.life_state = Memory::RPM<uintptr_t>(hProc, (entity.entity_base + hazedumper::netvars::m_lifeState));
            entity.team_id = Memory::RPM<uintptr_t>(hProc, (entity.entity_base + hazedumper::netvars::m_iTeamNum));
            entity.dormant = Memory::RPM<uintptr_t>(hProc, (entity.entity_base + hazedumper::signatures::m_bDormant));

            if (entity.dormant == 1) continue;

            entity.vec_origin = Memory::RPM<Vec3>(hProc, (entity.entity_base + hazedumper::netvars::m_vecOrigin));
            entity.head_origin;
            entity.feet_coords;
            entity.head_coords;

            entity.head_origin.X = entity.vec_origin.X;
            entity.head_origin.Y = entity.vec_origin.Y;
            entity.head_origin.Z = entity.vec_origin.Z + 75.0f;

            
            

            if (!WorldToScreen(entity.vec_origin, entity.feet_coords, plr.matrix.Matrix)) continue;

            if (!WorldToScreen(entity.head_origin , entity.head_coords , plr.matrix.Matrix)) continue;

            if (enable_enemy_esp)
            {
                if (plr.team_id != entity.team_id)
                {
                    glColor4f(color_enemy_box[0], color_enemy_box[1], color_enemy_box[2], color_enemy_box[3]);
                    DrawBox(entity.feet_coords, entity.head_coords);
                }
            }

            if (enable_team_esp)
            {
                if (plr.team_id == entity.team_id)
                {

                    glColor4f(color_team_box[0], color_team_box[1], color_team_box[2], color_team_box[3]);
                    DrawBox(entity.feet_coords, entity.head_coords);
                }
            }

            if (enable_team_snaplines)
            {
                if (plr.team_id == entity.team_id)
                {

                    glColor4f(color_team_snaplines[0], color_team_snaplines[1], color_team_snaplines[2], color_team_snaplines[3]);
                    DrawSnapLines(entity.feet_coords);
                }
            }

            if (enable_enemy_snaplines)
            {
                if (plr.team_id != entity.team_id)
                {

                    glColor4f(color_enemy_snaplines[0], color_enemy_snaplines[1], color_enemy_snaplines[2], color_enemy_snaplines[3]);
                    DrawSnapLines(entity.feet_coords);
                }
            }


            if (enable_enemy_healthbar)
            {
                if (plr.team_id != entity.team_id)
                {
                    DrawHealthBar(entity.feet_coords, entity.head_coords, entity.health);
                }
            }

            if (enable_team_healthbar)
            {
                if (plr.team_id == entity.team_id)
                {
                    DrawHealthBar(entity.feet_coords, entity.head_coords, entity.health);
                }
            }

            if (enable_team_armorbar)
            {
                if (plr.team_id == entity.team_id)
                {
                    DrawArmorBar(entity.feet_coords, entity.head_coords, entity.armor);
                }
            }

            if (enable_enemy_armorbar)
            {
                if (plr.team_id != entity.team_id)
                {
                    DrawArmorBar(entity.feet_coords, entity.head_coords, entity.armor);
                }
            }

            if (enable_viewmodel_fov)
            {
                
                Memory::WPM<int>(hProc, (plr.local_player + hazedumper::netvars::m_iFOV), viewmodel_fov_value);
            }

            if (enable_fov)
            {
                Memory::WPM<int>(hProc, (plr.local_player + hazedumper::netvars::m_iDefaultFOV), fov_value);
            }

            if (enable_no_flash)
            {

                Memory::WPM<uintptr_t>(hProc, (plr.local_player + hazedumper::netvars::m_flFlashDuration), 0);
                Memory::WPM<uintptr_t>(hProc, (plr.local_player + hazedumper::netvars::m_flFlashMaxAlpha), 0);

            }

            if (enable_thirdperson)
            {
                Memory::WPM<uintptr_t>(hProc, (plr.local_player + hazedumper::netvars::m_iObserverMode), 1);
            }
            else 
            {
                Memory::WPM<uintptr_t>(hProc, (plr.local_player + hazedumper::netvars::m_iObserverMode), 0);
            }
            
            
            

        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}