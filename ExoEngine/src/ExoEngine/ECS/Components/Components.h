/*!*************************************************************************
****
\file Components.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/09/2022
\brief  This file contains all the Various Components to be used in the ECS
in the future. Currently, Every Component is still handling its own data
by inheriting from an abstract class of IComponent to serialize and
deserialize its data


Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include "Transform.h"
#include "RigidBody.h"
#include "WinData.h"
#include "Collider.h"
#include "NameTag.h"
#include "Sprite.h"
#include "Logic.h"
#include "Tag.h"
#include "Audio.h"


//Macros for creating default values of various components
#define C_TransformComponent EM::Transform::Transform()
#define C_RigidBodyComponent EM::RigidBody::RigidBody()
#define C_ColliderComponent EM::Collider::Collider()
#define C_NameTagComponent EM::NameTag::NameTag()
#define C_SpriteComponent EM::Sprite::Sprite()
#define C_LogicComponent EM::Logic::Logic()
#define C_TagComponent EM::Tag::Tag()
#define C_AudioComponent EM::Audio::Audio()