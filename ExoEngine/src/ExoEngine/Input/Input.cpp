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

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "Input.h"

#include<GLFW/glfw3.h>

namespace EM {
    
    std::unique_ptr<InputSystem> mInstance;
    std::unique_ptr<InputSystem>& InputSystem::GetInstance()
    {
        if (!mInstance)
        {
            mInstance = std::make_unique<InputSystem>();
        }
        return mInstance;
    }

    /*!*************************************************************************
    Store key pressed input feedback in vector mReset
    ****************************************************************************/
    bool InputSystem::KeyPressed(const int& key)
    {
       // mReset.push_back(key);

        return mKeyStatus[key] == GLFW_PRESS;
    }

    /*!*************************************************************************
    Store key hold input feedback status in mKeyStatus
    ****************************************************************************/
    bool InputSystem::KeyHold(const int& key)
    {
        return mKeyStatus[key] == GLFW_REPEAT || mKeyStatus[key] == GLFW_PRESS;
    }

    /*!*************************************************************************
    Store key released input feedback in both vector mReset and mKeyStatus
    ****************************************************************************/
    bool InputSystem::KeyReleased(const int& key)
    {
       // mReset.push_back(key);
        return mKeyStatus[key] == GLFW_RELEASE;
    }

    /*!*************************************************************************
    Set keystatus based on keypressed
    ****************************************************************************/
    void InputSystem::SetKeyStatus(keycode key, keystatus status)
    {
        mReset.emplace_back(key);
        mKeyStatus[key] = status;
    }

    /*!*************************************************************************
    Resets mReset vector and mKeyStatus map to empty
    ****************************************************************************/
    void InputSystem::ResetPressedKey()
    {
        for (auto& key : mReset) 
        {
            if (mKeyStatus[key] == GLFW_PRESS)
                mKeyStatus[key] = GLFW_REPEAT;
        }


        mReset.clear();
    }

    /*!*************************************************************************
    Store mouse input feedback if mouse is pressed
    ****************************************************************************/
    bool InputSystem::MousePressed(const int& key)
    {
        return mMouseStatus[key] == GLFW_PRESS;
    }

    /*!*************************************************************************
    Store mouse input feedback if mouse is held
    ****************************************************************************/
    bool InputSystem::MouseHold(const int& key)
    {
        return mMouseStatus[key] == GLFW_PRESS || mMouseStatus[key] == GLFW_REPEAT;
    }

    /*!*************************************************************************
    Store mouse input feedback if mouse is released
    ****************************************************************************/
    bool InputSystem::MouseIsReleased(const int& key)
    {
        return mMouseStatus[key] == GLFW_RELEASE;
    }

    /*!*************************************************************************
    Set mouse status
    ****************************************************************************/
    void InputSystem::SetMouseStatus(mousecode key, mousestatus status)
    {
        mMouseStatus[key] = status;
    }

    /*!*************************************************************************
    Reset mouse input status in mMouseStatus to 0
    ****************************************************************************/
    void InputSystem::ResetPressedMouse()
    {
        for (auto& [key, status] : mMouseStatus)
            status = -1;
    }

    /*!*************************************************************************
    Checks if key is pressed by finding mKeyStatus
    ****************************************************************************/
    bool InputSystem::isKeyPressed(keycode key)
    {
        auto it = mKeyStatus.find(key);
        if (it != mKeyStatus.end())
            return it->second == GLFW_PRESS; //find the key in the map and execute the order
        
        return false;
    }
}