/*!*************************************************************************
****
\file Input.cpp
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: CSD2400 / GAM200
\par Section: a
\date 9-28-2022
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

    /*!*************************************************************************
    Store key pressed input feedback in vector m_reset
    ****************************************************************************/
    bool InputSystem::KeyPressed(const int& key)
    {
       // m_reset.push_back(key);

        return m_KeyStatus[key] == GLFW_PRESS;
    }

    /*!*************************************************************************
    Store key hold input feedback status in m_KeyStatus
    ****************************************************************************/
    bool InputSystem::KeyHold(const int& key)
    {
        return m_KeyStatus[key] == GLFW_REPEAT || m_KeyStatus[key] == GLFW_PRESS;
    }

    /*!*************************************************************************
    Store key released input feedback in both vector m_reset and m_KeyStatus
    ****************************************************************************/
    bool InputSystem::KeyReleased(const int& key)
    {
       // m_reset.push_back(key);
        return m_KeyStatus[key] == GLFW_RELEASE;
    }

    /*!*************************************************************************
    Set keystatus based on keypressed
    ****************************************************************************/
    void InputSystem::SetKeyStatus(keycode key, keystatus status)
    {
        m_reset.emplace_back(key);
        m_KeyStatus[key] = status;
    }

    /*!*************************************************************************
    Resets m_reset vector and m_KeyStatus map to empty
    ****************************************************************************/
    void InputSystem::ResetPressedKey()
    {
        for (auto& key : m_reset) 
        {
            if (m_KeyStatus[key] == GLFW_PRESS)
                m_KeyStatus[key] = GLFW_REPEAT;
        }


        m_reset.clear();
    }

    /*!*************************************************************************
    Store mouse input feedback if mouse is pressed
    ****************************************************************************/
    bool InputSystem::MousePressed(const int& key)
    {
        return m_MouseStatus[key] == GLFW_PRESS;
    }

    /*!*************************************************************************
    Store mouse input feedback if mouse is held
    ****************************************************************************/
    bool InputSystem::MouseHold(const int& key)
    {
        return m_MouseStatus[key] == GLFW_PRESS || m_MouseStatus[key] == GLFW_REPEAT;
    }

    /*!*************************************************************************
    Store mouse input feedback if mouse is released
    ****************************************************************************/
    bool InputSystem::MouseIsReleased(const int& key)
    {
        return m_MouseStatus[key] == GLFW_RELEASE;
    }

    /*!*************************************************************************
    Set mouse status
    ****************************************************************************/
    void InputSystem::SetMouseStatus(mousecode key, mousestatus status)
    {
        m_MouseStatus[key] = status;
    }

    /*!*************************************************************************
    Reset mouse input status in m_MouseStatus to 0
    ****************************************************************************/
    void InputSystem::ResetPressedMouse()
    {
        for (auto& [key, status] : m_MouseStatus)
            status = -1;
    }

    /*!*************************************************************************
    Checks if key is pressed by finding m_KeyStatus
    ****************************************************************************/
    bool InputSystem::isKeyPressed(keycode key)
    {
        auto it = m_KeyStatus.find(key);
        if (it != m_KeyStatus.end())
            return it->second == GLFW_PRESS; //find the key in the map and execute the order
        
        return false;
    }
}