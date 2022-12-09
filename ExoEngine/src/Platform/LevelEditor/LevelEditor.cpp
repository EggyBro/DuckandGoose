/*!*************************************************************************
****
\file LevelEditor.cpp
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: csd2400
\par Section: a
\par Milestone 2
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
#include <imgui/ImGuizmo.h>

#include "LevelEditor.h"
#include "ExoEngine/Timer/Time.h"
#include "ExoEngine/Timer/Fps.h"
#include "Platform/Graphics/Renderer.h"
#include "Platform/Graphics/Graphics.h"
#include "Picker.h"

#include "Platform/Graphics/FrameBuffer.h"
#include "ExoEngine/Log.h"
#include "ExoEngine/Audio/AudioEngine.h"

#include "ExoEngine/ECS/Components/Components.h"
#include "ExoEngine/ECS/SceneManager.h"
#include "ExoEngine/Log.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>


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

    static int current_sound = 0;
    /*!*************************************************************************
    Init loop for levelEditor sets context for ImGui
    ****************************************************************************/
    void LevelEditor::Init(Window* window)
    {
        m_window = window;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

        ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 450");

        LoadAudioFromFile();

        LoadSceneFromFile();
    }
    /*!*************************************************************************
    Update loop for level editor, poll events and set new frames
    ****************************************************************************/
    void LevelEditor::Update()
    {

        //MainMenuBar();
        if (p_Input->KeyPressed(GLFW_KEY_P))
        {
            show_window = !show_window;
        }
        if (!p_Editor->show_window)
        {
            glViewport(0, 0, m_window->Getter().m_Width, m_window->Getter().m_Height);
            EM::Graphic::camera.Resize(static_cast<float>(m_window->Getter().m_Width), static_cast<float>(m_window->Getter().m_Height));
        }
        if (show_window)
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            Docking();
            MainMenuBar();
            LoadSaveScene();
            Profiler();
            //ImGui::ShowDemoWindow(); //keep it for now as we need it for future reference
            ContentBrowser();
            Logger();
            Hierarchy();
            Inspector();
            SceneViewer();
            AudioManager();
        }

    }

    /*!*************************************************************************
   Render interface onto frame
   ****************************************************************************/

    void LevelEditor::Draw()
    {
        ImGui::Render();
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

    /*!*************************************************************************
    End instance of the level editor
    ****************************************************************************/
    void LevelEditor::End()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        p_Audio->Release();
    }

    /*!*************************************************************************
    Load file paths for scene from assets folder
    ****************************************************************************/
    void LevelEditor::LoadSceneFromFile()
    {
        std::string path = "Assets/Scene";
        for (auto const& dir_entry : std::filesystem::directory_iterator{ path })
        {
            //Checks if the given file status or path corresponds to a regular file
            if (!dir_entry.is_regular_file())
            {
                continue;
            }

            mFileList.emplace_back(dir_entry);
            // used to Load Scene
            mScenefile.emplace_back(dir_entry.path().filename().string());
        }
    }

    /*!*************************************************************************
    Load file paths for textures from assets folder
    ****************************************************************************/
    void LevelEditor::LoadTextureFromFile()
    {
        std::string path = "Assets/Textures";
        for (auto const& dir_entry : std::filesystem::directory_iterator{ path })
        {
            //Checks if the given file status or path corresponds to a regular file
            if (!dir_entry.is_regular_file())
            {
                continue;
            }

            mTextureFileList.emplace_back(dir_entry);
            // used to Load Scene
            mTextureFile.emplace_back(dir_entry.path().filename().string());
        }
    }

    /*!*************************************************************************
   Loads audio filepaths for audio files from assets folder
   ****************************************************************************/
    void LevelEditor::LoadAudioFromFile()
    {
        std::string audio_path = "Assets/metadigger";
        for (auto const& dir_entry : std::filesystem::directory_iterator{ audio_path }) //iterate files in metadigger file
        {
            //checks if given file status or path corresponds to a regular file
            if (!dir_entry.is_regular_file())
            {
                continue;
            }

            mAudioFileList.emplace_back(dir_entry);
            // used to load audio
            mAudioFile.emplace_back(dir_entry.path().filename().string());

        }
    }
    /*!*************************************************************************
    Menu bar located in the top left side of the window is used to toggle between
    opening and closing the editor
    ****************************************************************************/
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
            ImGui::EndMainMenuBar();
        }
    }

    /*!*************************************************************************
   Load and save scenes by serialising and deserializing data from JSON files
   ****************************************************************************/
    void LevelEditor::LoadSaveScene()
    {
        std::vector<const char*> filenames;
        const size_t arrSize = 100;
        const char* fileList[arrSize];
        std::string path = "Assets/Scene/";
        for (auto& item : mScenefile)
        {
            filenames.push_back(item.c_str());
        }

        std::copy(filenames.begin(), filenames.end(), fileList);

        for (size_t i = filenames.size(); i < arrSize; i++)
        {
            fileList[i] = "EMPTY";
        }

        ImGui::Begin("Save / Load");
        ImGui::Combo("##LoadFile", &mSelectedFile, fileList, static_cast<int>(filenames.size()), static_cast<int>(filenames.size()));
        if (mSelectedFile < 0)
        {
            ImGui::End();
            return;
        }
        if (ImGui::Button("LOAD"))
        {
            p_Scene->DeserializeFromFile(path + mFileList[mSelectedFile].path().filename().string());
        }
        ImGui::SameLine();
        ImGui::Button("SAVE");
        if (ImGui::IsItemClicked())
        {
            p_Scene->SerializeToFile(path + mFileList[mSelectedFile].path().filename().string());
        }

        ImGui::End();
    }

    /*!*************************************************************************
    Scene viewer
    ****************************************************************************/
    void LevelEditor::SceneViewer()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Scene");

        //vp = viewport
        auto vpMinRegion = ImGui::GetWindowContentRegionMin();
        auto vpMaxRegion = ImGui::GetWindowContentRegionMax();
        auto vpOffset = ImGui::GetWindowPos();

        mViewportBounds[0] = { vpMinRegion.x + vpOffset.x, vpMinRegion.y + vpOffset.y };
        mViewportBounds[1] = { vpMaxRegion.x + vpOffset.x, vpMaxRegion.y + vpOffset.y };

        //for scrolling purpose
        mViewportFocused = ImGui::IsWindowFocused();
        mViewportSize = { ImGui::GetContentRegionAvail() };


        uint64_t textureID = p_FrameBuffer->GetColorAttachmentRendererID();
        ImGui::Image((void*)(intptr_t)textureID, mViewportSize,
            ImVec2{ 0, 1 }, ImVec2{ 1, 0 });


        //gizmos
        if (p_Input->isKeyPressed(GLFW_KEY_1) && !ImGuizmo::IsUsing())
        {
            mGizmoType = ImGuizmo::OPERATION::TRANSLATE;
        }
        else if (p_Input->isKeyPressed(GLFW_KEY_2) && !ImGuizmo::IsUsing())
        {
            mGizmoType = ImGuizmo::OPERATION::ROTATE;
        }
        else if (p_Input->isKeyPressed(GLFW_KEY_3) && !ImGuizmo::IsUsing())
        {
            mGizmoType = ImGuizmo::OPERATION::SCALE;
        }
        ImGuizmo::BeginFrame();
        if (selectedEntity >= 0 && p_ecs.HaveComponent<Transform>(selectedEntity))//have selected entity
        {
            ImGuizmo::SetOrthographic(true);


            ImGuizmo::SetRect(
                mViewportBounds[0].x,
                mViewportBounds[0].y,
                mViewportBounds[1].x - mViewportBounds[0].x,
                mViewportBounds[1].y - mViewportBounds[0].y
            );

            glm::mat4 cameraProj = EM::Graphic::camera.GetProjectionMatrix();
            glm::mat4 cameraView = EM::Graphic::camera.GetViewMatrix();
            glm::mat4 transform{ 1.0f }; // identity matrix

            auto& trans = p_ecs.GetComponent<Transform>(selectedEntity);

            transform = glm::translate(glm::mat4{ 1.0f }, glm::vec3(trans.GetPos().x, trans.GetPos().y, 0.0f))
                * glm::rotate(glm::mat4(1.0f), glm::radians(trans.GetRot()), glm::vec3(0.0f, 0.0f, 1.0f))
                * glm::scale(glm::mat4(1.f), { trans.GetScale().x,trans.GetScale().y ,1.0f });

            ImGuizmo::SetDrawlist();
            // Draw ImGuizmo (renders every frame)
            ImGuizmo::Manipulate(glm::value_ptr(cameraView)
                , glm::value_ptr(cameraProj), (ImGuizmo::OPERATION)mGizmoType,
                ImGuizmo::WORLD, glm::value_ptr(transform));

            if (ImGuizmo::IsUsing())
            {
                glm::vec3 decompTrans, decompRot, decompScale;

                ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform),
                    glm::value_ptr(decompTrans),
                    glm::value_ptr(decompRot),
                    glm::value_ptr(decompScale));
                // change size 
                trans.SetPos(decompTrans[0], decompTrans[1]);
                trans.SetRot(decompRot[2]);
                trans.SetScale(decompScale[0], decompScale[1]);

            }
        }

        ImGui::End();
        ImGui::PopStyleVar();
        if (p_ecs.GetTotalEntities() != 0 && p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT) && !ImGuizmo::IsOver() && mViewportFocused)
        {

            std::multimap<float, Transform*> sortedMultimap;
            for (Entity entity = 0; entity < p_ecs.GetTotalEntities(); entity++)
            {
                if (p_ecs.HaveComponent<Transform>(entity)) {
                    sortedMultimap.insert({ p_ecs.GetComponent<Transform>(entity).GetRot(),
                                  &p_ecs.GetComponent<Transform>(entity) });
                }

            }

            selectedEntity = (Entity)Picker::Pick(&EM::Graphic::camera, sortedMultimap);

            //std::cout << selectedEntity << std::endl;
            if (selectedEntity == -1)//no entity selected will remain to the previous selected entity
            {
                selectedEntity = MAX_ENTITIES - 1; //to be fixed
            }
        }
    }

    /*!*************************************************************************
   View various assets from the assets folders from the level editor
   ****************************************************************************/
    void LevelEditor::ContentBrowser()
    {
        if (show_window)
        {
            ImGui::Begin("Content Browser");
            if (m_CurrentDirectory != std::filesystem::path(mAssetsPath))
            {
                if (ImGui::ImageButton((void*)(intptr_t)ResourceManager::GetIcon("BackIcon")->GetRendererID(),
                    { 25.f,25.f }, { 0, 1 }, { 1, 0 }))
                {
                    m_CurrentDirectory = m_CurrentDirectory.parent_path();
                }
            }

            for (auto& Directory : std::filesystem::directory_iterator(m_CurrentDirectory))
            {
                const auto& directorypath = Directory.path(); //the path for folders in Assets(assets/fonts)

                std::string filename = directorypath.filename().string(); //just the name of the folders(fonts, icons, metadigger etc)
                ImGui::PushID(filename.c_str());
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

                if (Directory.is_directory())
                {
                    ImGui::ImageButton((void*)(intptr_t)ResourceManager::GetIcon("FolderIcon")->GetRendererID(),
                        { 128.f,128.f }, { 0, 1 }, { 1, 0 });
                }

                //Press into the folder
                ImGui::PopStyleColor();
                if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    if (Directory.is_directory())
                        m_CurrentDirectory /= directorypath.filename();
                }

                ImGui::TextWrapped(filename.c_str()); ImGui::NextColumn(); //indicate the folder name
                ImGui::PopID();
            }

            ImGui::End();

            ImGui::Begin(m_CurrentDirectory.filename().string().c_str(), (bool*)0, ImGuiWindowFlags_HorizontalScrollbar);
            if (m_CurrentDirectory.filename() == "Textures")
            {
                for (auto& [name, texObj] : ResourceManager::textures)
                {
                    ImGui::Image((void*)(intptr_t)texObj->GetRendererID(),
                        ImVec2(128 * static_cast<float>(texObj->GetWidth()) / static_cast<float>(texObj->GetHeight()), 128),
                        ImVec2(0.0f, 1.0f),
                        ImVec2(1.0f, 0.0f));

                    if (ImGui::IsItemHovered())
                    {
                        ImGui::BeginTooltip();
                        std::string str = name + " " + "(" + std::to_string(texObj->GetWidth()) + "x" +
                            std::to_string(texObj->GetHeight()) + ")";
                        ImGui::Text(str.c_str());
                        ImGui::EndTooltip();
                    }

                    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
                    {
                        ImGui::SetDragDropPayload("Textures", &name, sizeof(name));
                        ImGui::Image((void*)(intptr_t)texObj->GetRendererID(),
                            ImVec2(128 * static_cast<float>(texObj->GetWidth()) / static_cast<float>(texObj->GetHeight()), 128),
                            ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
                        ImGui::EndDragDropSource();
                    }
                }
            }
            else if (m_CurrentDirectory.filename() == "Icons")
            {
                for (auto& [name, texObj] : ResourceManager::Icons)
                {
                    ImGui::SameLine();
                    ImGui::Image((void*)(intptr_t)texObj->GetRendererID(),
                        ImVec2(128 * static_cast<float>(texObj->GetWidth()) / static_cast<float>(texObj->GetHeight()), 128),
                        ImVec2(0.0f, 1.0f),
                        ImVec2(1.0f, 0.0f));

                    if (ImGui::IsItemHovered())
                    {
                        ImGui::BeginTooltip();
                        std::string str = name + " " + "(" + std::to_string(texObj->GetWidth()) + "x" +
                            std::to_string(texObj->GetHeight()) + ")";
                        ImGui::Text(str.c_str());
                        ImGui::EndTooltip();
                    }
                }

            }
            ImGui::End();
        }

    }
    /*!*************************************************************************
   Logger, can toggle between types of messages you want to view
   ****************************************************************************/
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

                    if (p_Audio->GetPlayingChannels() > 0)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
                        ImGui::Text("Audio Channel %d is played", p_Audio->GetPlayingChannels());
                        ImGui::PopStyleColor();
                    }
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

    /*!*************************************************************************
   Docking allows us to dock the ImGui windows to the edges of the scene
   ****************************************************************************/
    void LevelEditor::Docking()
    {
        //Set docking flags
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


    /*!*************************************************************************
    Profiler displays information about the users system such as

    Renderer and version of renderer (GPU)

    FPS

    Rendered info e.g. Quads, vertices, indices drawn etc.
    ****************************************************************************/
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

            mSystemRunTime[0] = Timer::GetInstance().GetDT(Systems::COLLISION) / Timer::GetInstance().GetGlobalDT();
            mSystemRunTime[1] = Timer::GetInstance().GetDT(Systems::GRAPHIC) / Timer::GetInstance().GetGlobalDT();
            mSystemRunTime[2] = Timer::GetInstance().GetDT(Systems::PHYSICS) / Timer::GetInstance().GetGlobalDT();
            mSystemRunTime[3] = Timer::GetInstance().GetDT(Systems::LOGIC) / Timer::GetInstance().GetGlobalDT();
            mSystemRunTime[4] = Timer::GetInstance().GetDT(Systems::API) / Timer::GetInstance().GetGlobalDT();

            ImGui::Text("COLLISION");
            ImGui::SameLine(80);
            ImGui::ProgressBar(mSystemRunTime[0], ImVec2(-1.0f, 0.0f));
            ImGui::Text("GRAPHIC");
            ImGui::SameLine(80);
            ImGui::ProgressBar(mSystemRunTime[1], ImVec2(-1.0f, 0.0f));
            ImGui::Text("PHYSICS");
            ImGui::SameLine(80);
            ImGui::ProgressBar(mSystemRunTime[2], ImVec2(-1.0f, 0.0f));
            ImGui::Text("LOGIC");
            ImGui::SameLine(80);
            ImGui::ProgressBar(mSystemRunTime[3], ImVec2(-1.0f, 0.0f));
            ImGui::Text("API");
            ImGui::SameLine(80);
            ImGui::ProgressBar(mSystemRunTime[4], ImVec2(-1.0f, 0.0f));

            ImGui::End();


        }
    }

    /*!*************************************************************************
  // Create, destroy and clone entities in the hirarchy window
  ****************************************************************************/
    void LevelEditor::Hierarchy()
    {
        if (show_window)
        {
            ImGui::Begin("Hierarchy");
            if (ImGui::Button("Create Entity") && p_ecs.GetTotalEntities() != MAX_ENTITIES)
            {
                p_ecs.AddComponent<NameTag>(p_ecs.CreateEntity(), NameTagComponent);
            }

            if (p_ecs.GetTotalEntities() > 0)
            {
                ImGui::SameLine();
                if (ImGui::Button("Destroy Entity"))
                {
                    if (selectedEntity != MAX_ENTITIES)
                    {
                        p_ecs.DestroyEntity(selectedEntity);
                    }
                    //selectedEntity = {}; // when the entity is destroy there is no current selected entity
                }
                ImGui::SameLine();
                if (ImGui::Button("Clone Entity") && p_ecs.GetTotalEntities() != 0)// there is entity alive
                {
                    if (selectedEntity != MAX_ENTITIES)
                    {
                        Entity CloneEntity = p_ecs.CloneEntity(selectedEntity);
                        selectedEntity = CloneEntity; // when the entity is destroy there is no current selected entity
                    }
                }

                auto aliveTotal = p_ecs.GetTotalEntities();
                Entity aliveCount = 0;
                Entity iterEntity = 0;
                while (aliveCount < aliveTotal)
                {
                    if (p_ecs.HaveComponent<NameTag>(iterEntity))
                    {
                        const auto& tag = p_ecs.GetComponent<NameTag>(iterEntity).GetNameTag();

                        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow;
                        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)iterEntity, flags, tag.c_str());

                        if (ImGui::IsItemClicked())
                            selectedEntity = iterEntity;

                        if (opened)
                            ImGui::TreePop();

                        aliveCount++;
                    }

                    iterEntity++;
                }
            }

            if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
                selectedEntity = {};
            ImGui::End();
        }

    }

    /*!*************************************************************************
   Inspector allows us to manipulate the entity properties, modifying scale,
   rotation and position of the object.
   ****************************************************************************/
    void LevelEditor::Inspector()
    {
        if (show_window)
        {
            ImGui::Begin("Inspector");
            if (selectedEntity != MAX_ENTITIES && p_ecs.GetTotalEntities() != 0)// if the selectedEntityExist
            {
                //create component for the selected entity 
                if (ImGui::Button("Add Component"))
                    ImGui::OpenPopup("Add Component");

                if (ImGui::BeginPopup("Add Component"))
                {

                    if (ImGui::MenuItem("Transform"))
                    {
                        if (!p_ecs.HaveComponent<Transform>(selectedEntity))
                            p_ecs.AddComponent<Transform>(selectedEntity, TransformComponent);
                        ImGui::CloseCurrentPopup();
                    }
                    if (ImGui::MenuItem("Sprite"))
                    {
                        if (!p_ecs.HaveComponent<Sprite>(selectedEntity))
                            p_ecs.AddComponent<Sprite>(selectedEntity, SpriteComponent);
                        ImGui::CloseCurrentPopup();
                    }
                    if (ImGui::MenuItem("Collider"))
                    {
                        if (!p_ecs.HaveComponent<Collider>(selectedEntity))
                            p_ecs.AddComponent<Collider>(selectedEntity, ColliderComponent);
                        ImGui::CloseCurrentPopup();
                    }
                    if (ImGui::MenuItem("RigidBody"))
                    {
                        if (!p_ecs.HaveComponent<RigidBody>(selectedEntity))
                            p_ecs.AddComponent<RigidBody>(selectedEntity, RigidBodyComponent);
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
                        ImGui::DragFloat("##PositionX", (float*)&Position.x, 0.005f); ImGui::SameLine(); //char name , pass float pointer to position vec2D which hold x and y, the scaling value in imgui
                        ImGui::PushID(1);
                        ImGui::Text("Y"); ImGui::SameLine();
                        ImGui::DragFloat("##PositionY", (float*)&Position.y, 0.005f);
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
                        auto& sprite = p_ecs.GetComponent<Sprite>(selectedEntity);
                        ImGui::Checkbox("SpriteSheet", &sprite.mIsSpriteSheet); ImGui::SameLine();
                        ImGui::Checkbox("Animation", &sprite.mIsanimated);
                        ImGui::Text("Coordinates: "); ImGui::SameLine();
                        ImGui::Text("X"); ImGui::SameLine();
                        ImGui::DragFloat("##X", (float*)&sprite.GetIndex().x, 0.5f); ImGui::SameLine();
                        ImGui::PushID(2);
                        ImGui::Text("Y"); ImGui::SameLine();
                        ImGui::DragFloat("##Y", (float*)&sprite.GetIndex().y, 0.5f);
                        ImGui::PopID();
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

                        if (ImGui::BeginDragDropTarget())
                        {
                            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Textures"))
                            {
                                texturePath = *(const std::string*)payload->Data;
                            }
                            ImGui::EndDragDropTarget();
                        }
                        if (sprite.mIsanimated)
                        {
                            ImGui::Text("DisplayTime"); ImGui::SameLine();
                            ImGui::DragFloat("##DisplayTime", (float*)&sprite.GetDisplayTime(), 0.005f);
                        }
                        if (sprite.mIsSpriteSheet)
                        {
                            ImGui::Text("UVCoordinates: "); ImGui::SameLine();
                            ImGui::Text("U"); ImGui::SameLine();
                            ImGui::DragFloat("##U", (float*)&sprite.GetUVCoor().x, 0.5f); ImGui::SameLine();
                            ImGui::PushID(2);
                            ImGui::Text("V"); ImGui::SameLine();
                            ImGui::DragFloat("##V", (float*)&sprite.GetUVCoor().y, 0.5f);
                            ImGui::PopID();
                        }
                    }
                }
                //Collider Component
                if (p_ecs.HaveComponent<Collider>(selectedEntity))
                {
                    if (ImGui::CollapsingHeader("Collider", ImGuiTreeNodeFlags_None))
                    {
                        //selection for collider type
                        auto& colliderType = p_ecs.GetComponent<Collider>(selectedEntity).GetCollider();

                        int colliderIndex = static_cast<int>(colliderType);
                        const char* colliderNames = "none\0circle\0line\0rect\0button";
                        ImGui::Text("Collider Type"); ImGui::SameLine();
                        ImGui::Combo("##test", &colliderIndex, colliderNames);
                        colliderType = static_cast<Collider::ColliderType>(colliderIndex);

                        //positioning the offset
                        auto& colliderOffset = p_ecs.GetComponent<Collider>(selectedEntity).GetOffset();
                        ImGui::PushItemWidth(100.0f);

                        ImGui::Text("OffSet   "); ImGui::SameLine();
                        ImGui::Text("X"); ImGui::SameLine();

                        ImGui::DragFloat("##colliderOffsetX", (float*)&colliderOffset.x, 0.05f); ImGui::SameLine();
                        ImGui::PushID(1);
                        ImGui::Text("Y"); ImGui::SameLine();
                        ImGui::DragFloat("##colliderOffsetY", (float*)&colliderOffset.y, 0.05f);
                        ImGui::PopID();

                        //size of the collider
                        if (p_ecs.GetComponent<Collider>(selectedEntity).GetCollider() == Collider::ColliderType::circle)
                        {
                            auto& colliderSize = p_ecs.GetComponent<Collider>(selectedEntity).GetRad();
                            ImGui::Text("Radius   "); ImGui::SameLine();
                            ImGui::DragFloat("##Radius", (float*)&colliderSize, 0.05f);
                        }
                        else if (p_ecs.GetComponent<Collider>(selectedEntity).GetCollider() == Collider::ColliderType::rect)
                        {
                            auto& colliderSize = p_ecs.GetComponent<Collider>(selectedEntity);
                            ImGui::Text("Minimum "); ImGui::SameLine();
                            ImGui::Text("X"); ImGui::SameLine();
                            ImGui::DragFloat("##MinimumX", (float*)&colliderSize.GetMin().x, 0.05f); ImGui::SameLine();
                            ImGui::Text("Y"); ImGui::SameLine();
                            ImGui::DragFloat("##MininmumY", (float*)&colliderSize.GetMin().y, 0.05f);

                            ImGui::Text("Maximum "); ImGui::SameLine();
                            ImGui::Text("X"); ImGui::SameLine();
                            ImGui::DragFloat("##MaximumX", (float*)&colliderSize.GetMax().x, 0.05f); ImGui::SameLine();
                            ImGui::Text("Y"); ImGui::SameLine();
                            ImGui::DragFloat("##MaximumY", (float*)&colliderSize.GetMax().y, 0.05f);
                        }
                    }
                }
                //Rigid Component
               /* if (p_ecs.HaveComponent<RigidBody>(selectedEntity))
                {
                    if (ImGui::CollapsingHeader("RigidBody", ImGuiTreeNodeFlags_None))
                    {
                        //velocity
                        auto& velocity = p_ecs.GetComponent<RigidBody>(selectedEntity).GetVel();
                        ImGui::PushItemWidth(100.0f);
                        ImGui::Text("Velocity   "); ImGui::SameLine();
                        ImGui::Text("X"); ImGui::SameLine();
                        ImGui::DragFloat("##VelocityX", (float*)&velocity.x, 0.005f); ImGui::SameLine();
                        ImGui::PushID(3);
                        ImGui::Text("Y"); ImGui::SameLine();
                        ImGui::DragFloat("##VelocityY", (float*)&velocity.y, 0.005f);
                        ImGui::PopID();

                        //Direction
                        auto& direction = p_ecs.GetComponent<RigidBody>(selectedEntity).GetDir();
                        ImGui::PushItemWidth(100.0f);
                        ImGui::Text("Direction  "); ImGui::SameLine();
                        ImGui::Text("X"); ImGui::SameLine();
                        ImGui::DragFloat("##DirectionX", (float*)&direction.x, 0.005f); ImGui::SameLine();
                        ImGui::PushID(4);
                        ImGui::Text("Y"); ImGui::SameLine();
                        ImGui::DragFloat("##DirectionY", (float*)&direction.y, 0.005f);
                        ImGui::PopID();

                        //GetFricition
                        auto& friction = p_ecs.GetComponent<RigidBody>(selectedEntity).GetFriction();
                        ImGui::Text("Friction   "); ImGui::SameLine();
                        ImGui::DragFloat("##Friction", (float*)&friction, 1.0f);

                        //GetRestitution
                        auto& Restitution = p_ecs.GetComponent<RigidBody>(selectedEntity).GetRestitution();
                        ImGui::Text("Restitution"); ImGui::SameLine();
                        ImGui::DragFloat("##Restitution", (float*)&Restitution, 1.0f);
                    }
                }*/
                if (ImGui::Button("Delete Component"))
                    ImGui::OpenPopup("Delete Component");

                if (ImGui::BeginPopup("Delete Component"))
                {
                    if (ImGui::MenuItem("Transform") && p_ecs.HaveComponent<Transform>(selectedEntity))
                    {
                        p_ecs.RemoveComponent<Transform>(selectedEntity);
                        ImGui::CloseCurrentPopup();
                    }
                    if (ImGui::MenuItem("Sprite") && p_ecs.HaveComponent<Sprite>(selectedEntity))
                    {
                        p_ecs.RemoveComponent<Sprite>(selectedEntity);
                        ImGui::CloseCurrentPopup();
                    }
                    if (ImGui::MenuItem("Collider") && p_ecs.HaveComponent<Collider>(selectedEntity))
                    {
                        p_ecs.RemoveComponent<Collider>(selectedEntity);
                        ImGui::CloseCurrentPopup();
                    }
                    if (ImGui::MenuItem("RigidBody") && p_ecs.HaveComponent<RigidBody>(selectedEntity))
                    {
                        p_ecs.RemoveComponent<RigidBody>(selectedEntity);
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::EndPopup();
                }
            }
            ImGui::End();
        } //end of show_window

    }



    /*!*************************************************************************
     Audio manager allows users to select and play, pause and test different
     audios in the editor
    ****************************************************************************/
    void LevelEditor::AudioManager()
    {
        if (show_window)
        {
            std::vector<const char*> audiofilenames;
            const size_t arraysize = 100;
            const char* audioFileList[arraysize];
            std::string audioPath = "Assets/metadigger/";
            static int currentfile = 0;

            for (auto& item : mAudioFile)
            {
                audiofilenames.push_back(item.c_str());
            }

            std::copy(audiofilenames.begin(), audiofilenames.end(), audioFileList);

            for (size_t i = audiofilenames.size(); i < arraysize; i++)
            {
                audioFileList[i] = "EMPTY";
            }

            ImGui::Begin("Audio Manager");

            ImGui::Combo("##LoadFile", &currentfile, audioFileList, static_cast<int>(audiofilenames.size()), static_cast<int>(audiofilenames.size()));

            static bool pauseButton = false;

            if (ImGui::Button("Play Audio"))
            {
                ImGui::SameLine();
                ImGui::Text("Playing!");
                current_sound = p_Audio->PlaySound(audioPath + mAudioFileList[currentfile].path().filename().string(), 50.f);
                //playinglist.emplace_back(std::to_string(current_sound).c_str());
            }

            for (auto i = p_Audio->ChannelMap.begin(); i != p_Audio->ChannelMap.end(); i++)
            {
                //print out text indicating channel number
                ImGui::Text("Playing Channel %s", std::to_string(i->first).c_str());

                if (ImGui::Button("Pause Audio"))
                {
                    p_Audio->PauseSound(i->first);
                }

                ImGui::SameLine();

                if (ImGui::Button("Unpause Audio"))
                {
                    p_Audio->UnpauseSound(i->first);
                }

                if (ImGui::Button("Stop Audio"))
                {
                    p_Audio->StopChannel(i->first);
                }

            }

            if (ImGui::Button("Delete Audio"))
            {
                std::filesystem::remove(mAudioFileList[currentfile].path());
                mAudioFileList.erase(mAudioFileList.begin() + currentfile);
                // used to load audio
                mAudioFile.erase(mAudioFile.begin() + currentfile);
            }

            static int item_current = 1;

            //set voulume slider
            static float f1 = 0.0f;
            ImGui::SliderFloat("Master Volume", &f1, 0.0f, 1.0f, "Min - Max %.3f");
            p_Audio->SetVolume(current_sound, 1 / (f1 + 1));

            static float f2 = 0.0f;
            ImGui::SliderFloat("BGM Volume", &f2, 0.0f, 1.0f, "Min - Max %.3f");
            if (f2 > f1)
            {
                f2 = f1;
            }

            static float f3 = 0.0f;
            ImGui::SliderFloat("SFX Volume", &f3, 0.0f, 1.0f, "Min - Max %.3f");
            if (f3 > f1)
            {
                f3 = f1;
            }

            ImGui::End();
        }
    }

    /*!*************************************************************************
    using std::filesystem we insert the file path if audio assets into the editor
    ****************************************************************************/
    void LevelEditor::insertAudioFilePath(std::string in)
    {
        //create new directory entry
        //insert entry into mAudioFileList
        //insert path into mAudioFile
        auto const& dir_entry = std::filesystem::directory_entry{ in };
        mAudioFileList.emplace_back(dir_entry);
        mAudioFile.emplace_back(dir_entry.path().filename().string());
    }

    /*!*************************************************************************
   using std::filesystem we insert the file path if texture assets into the editor
   ****************************************************************************/
    void LevelEditor::insertTextureFilePath(std::string in)
    {
        auto const& dir_entry = std::filesystem::directory_entry{ in };
        mTextureFileList.emplace_back(dir_entry);
        mTextureFile.emplace_back(dir_entry.path().filename().string());
    }
}