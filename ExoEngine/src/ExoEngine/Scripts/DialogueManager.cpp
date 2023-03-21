/*!*************************************************************************
****
\file DialogueManager.cpp
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Script for Dialogue Manager

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "DialogueManager.h"

namespace EM
{
    /*!*************************************************************************
    Default constructor for Dialogue Manager
    ****************************************************************************/
    DialogueManager::DialogueManager() : mTextStream{ nullptr }, mTextBuffer{}, mPrintSpeed{ 0.0f } {}

    /*!*************************************************************************
    Returns a new copy of DialogueManager Script
    ****************************************************************************/
    DialogueManager* DialogueManager::Clone() const
    {
        return new DialogueManager(*this);
    }

    /*!*************************************************************************
    Start State of DialogueManager Script
    ****************************************************************************/
    void DialogueManager::Start()
    {

    }

    /*!*************************************************************************
    Update Loop of Dialogue Manager Script
    ****************************************************************************/
    void DialogueManager::Update(float Frametime)
    {
    }

    /*!*************************************************************************
    End State for Dialogue Manager
    ****************************************************************************/
    void DialogueManager::End()
    {
        delete this;
    }

    /*!*************************************************************************
    Returns the name of Script
    ****************************************************************************/
    std::string DialogueManager::GetScriptName()
    {
        return "DialogueManager";
    }
}