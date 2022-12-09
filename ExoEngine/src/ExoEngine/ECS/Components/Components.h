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
#define TransformComponent EM::Transform::Transform()
#define RigidBodyComponent EM::RigidBody::RigidBody()
#define ColliderComponent EM::Collider::Collider()
#define NameTagComponent EM::NameTag::NameTag()
#define SpriteComponent EM::Sprite::Sprite()
#define LogicComponent EM::Logic::Logic()
#define TagComponent EM::Tag::Tag()
#define AudioComponent EM::Audio::Audio()