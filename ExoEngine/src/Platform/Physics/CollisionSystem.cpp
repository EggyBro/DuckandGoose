/*!*****************************************************************************
\file CollisionSystem.cpp
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: csd2125
\par Section: a
\par 
\date 14-10-2022
\brief  This file contains the function definitions for the collision system
 
*******************************************************************************/
#include "empch.h"
#include "CollisionSystem.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
#include "ExoEngine/ECS/Components/Components.h"
#include "ExoEngine/Math/Physics.h"

namespace EM {
    /*!*************************************************************************
	This function initialises the system. As there are no data members that require
	initialization, this function is empty
	****************************************************************************/
    void CollisionSystem::Init() {}
    /*!*************************************************************************
	This function runs the logic of the system. It checks the list of entities with
    a collision component in pairs to see which of them are colliding. If two objects
    are colliding, collision response is dictated by the type of collider the object
    has
	****************************************************************************/
    void CollisionSystem::Update(float dt) {
        (void)dt;
        Timer::GetInstance().Start(Systems::COLLISION);
        Timer::GetInstance().GetDT(Systems::COLLISION);
        //iterate through array of entities
        int k = 0;
        for (auto const& i : mEntities) {
            int l = 0;
            for (auto const& j : mEntities) {
                if (i != j && l > k) {
                    auto& col1 = p_ecs.GetComponent<Collider>(i);
                    auto& col2 = p_ecs.GetComponent<Collider>(j);
                    auto& rigid1 = p_ecs.GetComponent<RigidBody>(i);
                    auto& rigid2 = p_ecs.GetComponent<RigidBody>(j);
                    Collider::ColliderType e1 = col1.GetCollider();
                    Collider::ColliderType e2 = col2.GetCollider();
                    col1.SetHit(0);
                    col2.SetHit(0);
                    vec2D offset1 = rigid1.GetNextPos() + col1.GetOffset();
                    vec2D offset2 = rigid2.GetNextPos() + col2.GetOffset();
                    std::cout << (int)e1 << ", " << (int)e2 << "\n";
                    if (col1.GetAlive() && col2.GetAlive())
                    {
                        if (e1 == Collider::ColliderType::circle) {
                            if (e2 == Collider::ColliderType::circle) {
                                if (ecm.simpleCircleCircle(offset1, offset2, col1.GetRad(), col2.GetRad())) {
                                    col1.SetHit(1);
                                    vec2D norm1 = offset1 - offset2;
                                    Normalize(norm1, norm1);
                                    col1.SetNormal(norm1);
                                    col2.SetHit(1);
                                    vec2D norm2 = offset2 - offset1;
                                    Normalize(norm2, norm2);
                                    col2.SetNormal(norm2);
                                    // std::cout << "hit\n";
                                }
                            }
                            if (e2 == Collider::ColliderType::rect) {
                                vec2D max2 = offset2 + col2.GetMax();
                                vec2D min2 = offset2 - col2.GetMin();
                                if (ecm.simpleCircleRect(offset1, col1.GetRad(), max2, min2, offset2)) {
                                    std::cout << "Collision Circle-Rect\n";
                                    col1.SetHit(1);
                                    vec2D norm1 = offset1 - offset2;
                                    Normalize(norm1, norm1);
                                    col1.SetNormal(norm1);
                                    col2.SetHit(1);
                                    vec2D norm2 = offset2 - offset1;
                                    Normalize(norm2, norm2);
                                    col2.SetNormal(norm2);
                                    // std::cout << "hit\n";
                                }
                            }
                        }
                        else if (e1 == Collider::ColliderType::rect) {
                            if (e2 == Collider::ColliderType::circle) {
                                vec2D max1 = offset1 + col1.GetMax();
                                vec2D min1 = offset1 - col1.GetMin();
                                if (ecm.simpleCircleRect(offset2, col2.GetRad(), max1, min1, offset1)) {
                                    std::cout << "Collision Rect-Circle\n";
                                    col1.SetHit(1);
                                    vec2D norm1 = offset1 - offset2;
                                    Normalize(norm1, norm1);
                                    col1.SetNormal(norm1);
                                    col2.SetHit(1);
                                    vec2D norm2 = offset2 - offset1;
                                    Normalize(norm2, norm2);
                                    col2.SetNormal(norm2);
                                    // std::cout << "hit\n";
                                }
                            }
                            if (e2 == Collider::ColliderType::rect) {
                                vec2D max1 = offset1 + col1.GetMax();
                                vec2D min1 = offset1 - col1.GetMin();
                                vec2D max2 = offset2 + col2.GetMax();
                                vec2D min2 = offset2 - col2.GetMin();
                                if (ecm.simpleRectRect(max1, min1, max2, min2)) {
                                    vec2D colmax1 = offset1 + col1.GetMax() * 0.8f;
                                    vec2D colmin1 = offset1 - col1.GetMin() * 0.8f;
                                    vec2D colmax2 = offset2 + col2.GetMax() * 0.8f;
                                    vec2D colmin2 = offset2 - col2.GetMin() * 0.8f;
                                    vec2D line;
                                    if (max1.x >= min2.x && max1.x < colmin2.x) {
                                        line.x = -1.f;
                                    }
                                    else if (max2.x >= min1.x && max2.x < colmin1.x) {
                                        line.x = 1.f;
                                    }
                                    else if (max1.y < colmin2.y && (max1.x > colmin2.x || min1.x < colmax2.x)) {
                                        line.y = -1.f;
                                    }
                                    else if (max2.y < colmin1.y && (max2.x > colmin1.x || min2.x < colmax1.x)) {
                                        line.y = 1.f;
                                    }
                                    col1.SetHit(1);
                                    col1.SetNormal(line);
                                    col2.SetHit(1);
                                    col2.SetNormal(line * -1);
                                    //std::cout << "hit\n";
                                }
                            }
                        }
                    }
                    //playable area bounding box to be implemented
                    else if (e1 == Collider::ColliderType::box) {

                    }
                }
                l++;
            }
            k++;
        }
        Timer::GetInstance().Update(Systems::COLLISION);
    }
    /*!*************************************************************************
	This function ends the system. As there are no data members that require
	initialization, there are no data members that need to be un-initialised. 
	Therefore this function is empty
	****************************************************************************/
    void CollisionSystem::End() {}
}