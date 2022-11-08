/*!*************************************************************************
****
\file LevelEditor.cpp
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: csd2400
\par Section: a
\par Milestone 1
\date 28-9-2022
\brief  This program utilises Dear ImGui and OpenGL to create a editor interface
        to allow us to edit object, create entities and modify the
        properties of the components and save them accordingly.
****************************************************************************
***/

#include "empch.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "LevelEditor.h"
#include "ExoEngine/Timer/Time.h"
#include "ExoEngine/Timer/Fps.h"
#include "Platform/Graphics/Renderer.h"

#include "Platform/Graphics/FrameBuffer.h"
#include "ExoEngine/Log.h"
#include "ExoEngine/Audio/AudioEngine.h"

#include "ExoEngine/Log.h"
#include "ExoEngine/ECS/Components/Components.h"
#include <glm/gtc/type_ptr.hpp>

namespace EM {

    std::unique_ptr<LevelEditor> LevelEditor::m_instance{ nullptr };

    std::unique_ptr<LevelEditor>& LevelEditor::GetInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = std::make_unique<LevelEditor>();
        }
        return m_instance;
    }

    bool color_picker = false;
    bool drop_menu = false;
    bool logger = false;
    static bool show_window = true;
    std::vector<int> soundlist;

    // Init for levelEditor sets context for ImGui 
    void LevelEditor::Init(Window* window)
    {
        m_window = window;
        /*GLFWwindow* m_window = glfwGetCurrentContext();
        glfwMakeContextCurrent(m_window);*/
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

        ////can be removed not important
        //ImFont* font1 = io.Fonts->AddFontFromFileTTF("Assets/fonts/ArialItalic.ttf", 20); //modify the font in each of the tabs

        ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 450");

        soundlist.push_back({ p_Audio->PlaySound("C:\\Users\\mattc\\Downloads\\Exomata_X\\Exomata\\Exomata\\Assets\\metadigger\\FStep1.wav", 50.f) });
        soundlist.push_back({ p_Audio->PlaySound("C:\\Users\\mattc\\Downloads\\Exomata_X\\Exomata\\Exomata\\Assets\\metadigger\\FStep2.wav", 50.f) });
        soundlist.push_back({ p_Audio->PlaySound("C:\\Users\\mattc\\Downloads\\Exomata_X\\Exomata\\Exomata\\Assets\\metadigger\\FStep3.wav", 50.f) });
        soundlist.push_back({ p_Audio->PlaySound("C:\\Users\\mattc\\Downloads\\Exomata_X\\Exomata\\Exomata\\Assets\\metadigger\\FStep4.wav", 50.f) });
        soundlist.push_back({ p_Audio->PlaySound("C:\\Users\\mattc\\Downloads\\Exomata_X\\Exomata\\Exomata\\Assets\\metadigger\\FStep5.wav", 50.f) });

        soundlist.push_back({ p_Audio->PlaySound("C:\\Users\\mattc\\Downloads\\Exomata_X\\Exomata\\Exomata\\Assets\\metadigger\\Whoosh1.wav", 50.f) });
        soundlist.push_back({ p_Audio->PlaySound("C:\\Users\\mattc\\Downloads\\Exomata_X\\Exomata\\Exomata\\Assets\\metadigger\\Whoosh2.wav", 50.f) });
        soundlist.push_back({ p_Audio->PlaySound("C:\\Users\\mattc\\Downloads\\Exomata_X\\Exomata\\Exomata\\Assets\\metadigger\\Whoosh3.wav", 50.f) });
        soundlist.push_back({ p_Audio->PlaySound("C:\\Users\\mattc\\Downloads\\Exomata_X\\Exomata\\Exomata\\Assets\\metadigger\\Whoosh4.wav", 50.f) });
        soundlist.push_back({ p_Audio->PlaySound("C:\\Users\\mattc\\Downloads\\Exomata_X\\Exomata\\Exomata\\Assets\\metadigger\\Whoosh5.wav", 100.f) });

        soundlist.push_back({ p_Audio->PlaySound("C:\\Users\\mattc\\Downloads\\Exomata_X\\Exomata\\Exomata\\Assets\\test.wav", 50.f) });

        p_Audio->PauseSound(soundlist[0]);
        p_Audio->PauseSound(soundlist[1]);
        p_Audio->PauseSound(soundlist[2]);
        p_Audio->PauseSound(soundlist[3]);
        p_Audio->PauseSound(soundlist[4]);

        p_Audio->PauseSound(soundlist[5]);
        p_Audio->PauseSound(soundlist[6]);
        p_Audio->PauseSound(soundlist[7]);
        p_Audio->PauseSound(soundlist[8]);
        p_Audio->PauseSound(soundlist[9]);

        p_Audio->PauseSound(soundlist[10]);

    }

    //  Update loop for level editor, poll events and set new frames
    void LevelEditor::Update()
    {
        Timer::GetInstance().Start(Systems::GRAPHIC);
        Timer::GetInstance().GetDT(Systems::GRAPHIC);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuiIO& io = ImGui::GetIO();

        docking();
        MainMenuBar();
        Profiler();
        ImGui::ShowDemoWindow();
        DropDownMenu();
        Logger();
        Hierarchy();
        Inspector();
        Audio();
        Timer::GetInstance().Update(Systems::GRAPHIC);
    }
    //  Render interface onto frame

    void LevelEditor::Draw()
    {
        ImGui::Render();
        //ImGui::EndFrame();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            auto* mWindow = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(mWindow);
        }

    }

    //  End instance
    void LevelEditor::End()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void LevelEditor::MainMenuBar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Editor Control"))
            {
                if (ImGui::MenuItem("Open"))
                {
                    show_window = true;
                }

                ImGui::Separator();

                if (ImGui::MenuItem("Close"))
                {
                    show_window = false;
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }



    //  This dropdown menu holds check boxes, sliders dropdown menus etc. This was used to learn how to implement
    //  Widgets, boxes and other useful tools in ImGui, which will be developed in the future 
    void LevelEditor::DropDownMenu()
    {
        if (show_window)
        {
            if (ImGui::Begin("Drop down menu")) //main box for color picker window
            {
                ImGui::Text("Hello");
            }
            ImGui::End();
        }
    }

    // Logger, can toggle between types of messages you want to view
    void LevelEditor::Logger()
    {
        if (show_window)
        {

            if (ImGui::Begin("Logger"))
            {
                static bool info = true;
                ImGui::Checkbox("Info       ", &info);

                ImGui::SameLine();

                static bool warning = true;
                ImGui::Checkbox("warning    ", &warning);

                ImGui::SameLine();

                static bool error = true;
                ImGui::Checkbox("error", &error);

                static bool system = true;
                ImGui::Checkbox("system     ", &system);

                ImGui::SameLine();

                static bool log = true;
                ImGui::Checkbox("log        ", &log);

                ImGui::SameLine();

                static bool fatal = true;
                ImGui::Checkbox("fatal", &fatal);

                if (info)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
                    ImGui::Text(Log::GetImguiLog().c_str());
                    ImGui::PopStyleColor();
                }

                if (warning)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
                    ImGui::Text("This is an Warning Message");
                    ImGui::PopStyleColor();
                }

                if (error)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
                    ImGui::Text("This is an Error Message");
                    ImGui::PopStyleColor();
                }

                if (system)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(52, 67, 235, 255));
                    ImGui::Text("This is an System Message");
                    ImGui::PopStyleColor();
                }

                if (log)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(52, 222, 235, 255));
                    ImGui::Text("This is an Log Message");
                    ImGui::PopStyleColor();
                }

                if (fatal)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
                    ImGui::Text("This is an Fatal Message");
                    ImGui::PopStyleColor();
                }
            }
            ImGui::End();
        }
    }

    //Docking function is based off of ImGui demo's ShowExampleAppDockSpace function which will allow tools to dock with the sides of the
    //level editor. However, as of now it is not yet functional as I have yet to fix the frame layering to allow this function to work
    void LevelEditor::docking()
    {
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
            ImGuiWindowFlags_NoBackground;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("DockSpace", 0, window_flags);

        ImGui::PopStyleVar(3);

        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

        ImGui::End();

    }

    void LevelEditor::Profiler()
    {
        if (show_window)
        {
            ImGui::Begin("Profiler");
            //Opengl information
            ImGui::Text("Opengl Information ");
            ImGui::Text("Vendor: %s", glGetString(GL_VENDOR));
            ImGui::Text("Renderer: %s", glGetString(GL_RENDERER));
            ImGui::Text("Version: %s", glGetString(GL_VERSION));
            ImGui::Text("\n");

            // how much time per frame and Fps
            ImGui::Text("Application average % .3f ms / frame(% .3f FPS)", 1000.0f / FramePerSec::GetInstance().GetFps(), FramePerSec::GetInstance().GetFps());

            //Renderering Information
            ImGui::Text("\n");
            auto Infos = Renderer::GetInfo();
            ImGui::Text("Renderer Information");
            ImGui::Text("Draw Calls: %d", Infos.n_DrawCalls);
            ImGui::Text("Quads: %d", Infos.n_Quad);
            ImGui::Text("Vertices: %d", Infos.TotalVertexUsed());
            ImGui::Text("Indices: %d", Infos.TotalIndexUsed());

            ImGui::Checkbox("Show physics colliders", &mDebugDraw);
            //Todo show the each system consume how much at runtime
            ImGui::End();

         
        }
    }

    void LevelEditor::Hierarchy()
    {
        ImGui::Begin("Hierarchy");
        if (ImGui::Button("Create Entity"))
        {
            selectedEntity = p_ecs.CreateEntity();
            p_ecs.AddComponent<NameTag>(selectedEntity, NameTagComponent);
        }
       
        if (p_ecs.GetTotalEntities() != 0 && p_ecs.GetTotalRegisteredComponents()!=0)
        {
            ImGui::SameLine();
            if (ImGui::Button("Destroy Entity") /*&& selectedEntity!= 0*/)
            {
                if (selectedEntity != MAX_ENTITIES)
                {
                    p_ecs.DestroyEntity(selectedEntity);
                }
                selectedEntity = MAX_ENTITIES; // when the entity is destroy there is no current selected entity
            }
            ImGui::SameLine();
            if (ImGui::Button("Clone Entity") /*&& selectedEntity!= 0*/)
            {
                Entity CloneEntity = p_ecs.CloneEntity(selectedEntity);
                selectedEntity = CloneEntity; // when the entity is destroy there is no current selected entity
            }
            Entity e = 0;
            Entity livingCount = 0;
            while (livingCount < p_ecs.GetTotalEntities())
            {
                if (p_ecs.HaveComponent<NameTag>(e))
                {
                    ++livingCount;
                    const auto& tag = p_ecs.GetComponent<NameTag>(e).GetNameTag();

                    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow;
                    bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)e, flags, tag.c_str());

                    if (ImGui::IsItemClicked())
                        selectedEntity = e;

                    if (opened)
                        ImGui::TreePop();
                }
                ++e;
            }
        }
        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
            selectedEntity = MAX_ENTITIES;
        ImGui::End();

    }

    void LevelEditor::Inspector()
    {
        ImGui::Begin("Inspector");
        if (selectedEntity != MAX_ENTITIES)// if the selectedEntityExist
        {
            //create component for the selected entity 
            if (ImGui::Button("Add Component"))
                ImGui::OpenPopup("Add Component");

            if (ImGui::BeginPopup("Add Component"))
            {
                if (ImGui::MenuItem("NameTag"))
                {
                    p_ecs.AddComponent<NameTag>(selectedEntity, NameTagComponent);
                    ImGui::CloseCurrentPopup();
                }
                if (ImGui::MenuItem("Transform"))
                {
                    p_ecs.AddComponent<Transform>(selectedEntity, TransformComponent);
                    ImGui::CloseCurrentPopup();
                }
                if (ImGui::MenuItem("Sprite"))
                {
                    p_ecs.AddComponent<Sprite>(selectedEntity, SpriteComponent);
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
            //Check and change the name of the Entity
            if (p_ecs.HaveComponent<NameTag>(selectedEntity))
            {
                if (ImGui::CollapsingHeader("Name", ImGuiTreeNodeFlags_None))
                {
                    auto& name = p_ecs.GetComponent<NameTag>(selectedEntity).GetNameTag();
                    char buffer[256];
                    memset(buffer, 0, sizeof(buffer));
                    strcpy_s(buffer, sizeof(buffer), name.c_str());
                    if (ImGui::InputText("name", buffer, sizeof(buffer)))
                    {
                        name = std::string(buffer);
                    }

                }
            }
            //If Entity have Transform Component
            if (p_ecs.HaveComponent<Transform>(selectedEntity)) 
            {
                if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_None))
                {
                    //position
                    auto& Position = p_ecs.GetComponent<Transform>(selectedEntity).GetPos();
                    ImGui::PushItemWidth(100.0f);
                    ImGui::Text("Position"); ImGui::SameLine();
                    ImGui::Text("X"); ImGui::SameLine();                    //set a "x" to indicate x-axis
                    ImGui::DragFloat("##Position", (float*)&Position.x, 0.005f); ImGui::SameLine(); //char name , pass float pointer to position vec2D which hold x and y, the scaling value in imgui
                    ImGui::PushID(1);
                    ImGui::Text("Y"); ImGui::SameLine();
                    ImGui::DragFloat("##Position", (float*)&Position.y, 0.005f);
                    ImGui::PopID();

                    //scale
                    auto& Scale = p_ecs.GetComponent<Transform>(selectedEntity).GetScale();
                    ImGui::Text("Scale   "); ImGui::SameLine();
                    ImGui::Text("X"); ImGui::SameLine();                    //set a "x" to indicate x-axis
                    ImGui::DragFloat("##Scale", (float*)&Scale.x, 0.005f); ImGui::SameLine(); //char name , pass float pointer to position vec2D which hold x and y, the scaling value in imgui
                    ImGui::PushID(2);
                    ImGui::Text("Y"); ImGui::SameLine();
                    ImGui::DragFloat("##Scale", (float*)&Scale.y, 0.005f);
                    ImGui::PopID();
                    //EM_EXO_INFO("Scale(x:{0}, y:{1})", Scale.x, Scale.y);

                    //rotation
                    auto& rotation = p_ecs.GetComponent<Transform>(selectedEntity).GetRot();
                    ImGui::Text("Rotation Z"); ImGui::SameLine();
                    ImGui::DragFloat("##", (float*)&rotation, 1.0f);
                    //EM_EXO_INFO("Rotation(z:{0})", rotation);
                }
            }
            //Sprite Component
            if (p_ecs.HaveComponent<Sprite>(selectedEntity))
            {
                if (ImGui::CollapsingHeader("Sprite", ImGuiTreeNodeFlags_None))
                {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4());
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
                    ImGui::Button("Image : "); ImGui::SameLine(80.0f);
                    ImGui::PopStyleColor(3);
                    auto& texturePath = p_ecs.GetComponent<Sprite>(selectedEntity).GetTexture();
                    ImGui::SetNextItemWidth(140.0f);

                    if (ImGui::BeginCombo("##sprite", texturePath.c_str()))
                    {
                        for (auto& [str, tex] : ResourceManager::textures)
                        {
                            if (ImGui::Selectable(str.c_str()))
                            {
                                texturePath = str;
                                EM_EXO_INFO("Loaded {0} Sprite", texturePath.c_str());
                            }
                        }
                        ImGui::EndCombo();
                    }
                }
            }
        }
        ImGui::End();

    }

    void LevelEditor::Audio()
    {
        if (show_window)
        {
            ImGui::Begin("Audio Manager");

            const char* items[] = { "FStep1", "FStep2", "FStep3", "FStep4", "FStep5", "Whoosh1", "Whoosh2", "Whoosh3", "Whoosh4", "Whoosh5", "test" };
            static int item_current = 0;
            //static const char* current_item = NULL;

            ImGui::Combo("Load Sound", &item_current, items, IM_ARRAYSIZE(items));

            static int play_clicked = 0;
            static int pause_clicked = 0;
            static int stop_clicked = 0;

            //play audio file based on sound selected 
            if (ImGui::Button("Play Sound"))
                play_clicked++;

            if ((play_clicked & 1))
            {
                ImGui::SameLine();
                ImGui::Text("Playing!");
                pause_clicked = 0;
                stop_clicked = 0;
                p_Audio->UnpauseSound(soundlist[item_current]);

            }

            //pause audio file based on sound selected 
            if (ImGui::Button("Pause Sound"))
                pause_clicked++;

            if (pause_clicked & 1)
            {
                ImGui::SameLine();
                ImGui::Text("Paused!");
                play_clicked = 0;
                stop_clicked = 0;
                p_Audio->PauseSound(soundlist[item_current]);
            }

            if (ImGui::Button("Stop Sound"))
                stop_clicked++;

            if (stop_clicked & 1)
            {
                ImGui::SameLine();
                ImGui::Text("Stopped!");
                play_clicked = 0;
                pause_clicked = 0;
            }

            //set voulume slider
            static float f1 = 0.0f;
            ImGui::SliderFloat("Set Volume", &f1, 0.0f, 1.0f, "%.3f");
            p_Audio->SetVolume(item_current, f1);
            ImGui::End();

        }
    }
}
