/*!*************************************************************************
****
\file Input.cpp
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: csd2400
\par Section: a
\par Milestone 1
\date 28-9-2022
\brief  The input manager is responsible for retrieving keyboard and mouse input,
the input systems provides us with a way to fetch information on inputs in a simple
and effective manner. Allowing the user to view whether the keys or mouse are pressed,
released or being held.

****************************************************************************
***/
#include "empch.h"
#include "Input.h"

#include<GLFW/glfw3.h>

namespace EM {
    
    std::unique_ptr<InputSystem> m_Instance;
    std::unique_ptr<InputSystem>& InputSystem::GetInstance()
    {
        if (!m_Instance)
        {
            m_Instance = std::make_unique<InputSystem>();
        }
        return m_Instance;
    }
    bool InputSystem::KeyPressed(const int& key)
    {
        m_reset.push_back(key);

        return m_KeyStatus[key] == GLFW_PRESS;
    }
    bool InputSystem::KeyHold(const int& key)
    {
        return m_KeyStatus[key] == GLFW_REPEAT || m_KeyStatus[key] == GLFW_PRESS;
    }
    bool InputSystem::KeyReleased(const int& key)
    {
        m_reset.push_back(key);
        return m_KeyStatus[key] == GLFW_RELEASE;
    }
    void InputSystem::SetKeyStatus(keycode key, keystatus status)
    {
        m_KeyStatus[key] = status;
    }
    void InputSystem::ResetPressedKey()
    {
        for (auto& key : m_reset)
            m_KeyStatus[key] = -1;

        m_reset.clear();
    }
    bool InputSystem::MousePressed(const int& key)
    {
        return m_MouseStatus[key] == GLFW_PRESS;
    }
    bool InputSystem::MouseHold(const int& key)
    {
        return m_MouseStatus[key] == GLFW_PRESS || m_MouseStatus[key] == GLFW_REPEAT;
    }
    bool InputSystem::MouseIsReleased(const int& key)
    {
        return m_MouseStatus[key] == GLFW_RELEASE;
    }
    void InputSystem::SetMouseStatus(mousecode key, mousestatus status)
    {
        m_MouseStatus[key] = status;
    }
    void InputSystem::ResetPressedMouse()
    {
        for (auto& [key, status] : m_MouseStatus)
            status = -1;
    }
    //use it for player
    bool InputSystem::isKeyPressed(keycode key)
    {
        auto it = m_KeyStatus.find(key);
        if (it != m_KeyStatus.end())
            return it->second; //find the key in the map and execute the order
        
        return false;
    }
}