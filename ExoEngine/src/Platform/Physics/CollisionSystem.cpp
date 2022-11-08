/*!*************************************************************************
****
\file			CollisionSystem.cpp
\author			Tan Ek Hern
\par DP email:	t.ekhern@digipen.edu
\par Course:	Gam200
\section		A
\date			14-10-2022
\brief			This file contains the necessary function definitions for
                collision

****************************************************************************
***/
#include "empch.h"
#include "CollisionSystem.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
#include "ExoEngine/ECS/Components/Components.h"

namespace EM {
    //extern ECS ecs;
    void CollisionSystem::Init() {
        //check which component has collision and add it to array
        //assign collider to rigidbody component
    }
    void CollisionSystem::Update(float dt) {
        //iterate through array of entities
        int k = 0;
        for (auto const& i : mEntities) {
            auto& trans1 = p_ecs.GetComponent<Transform>(i);
            vec2D ent1pos = trans1.GetPos();
            //make j index i+1
            int l = 0;
            for (auto const& j : mEntities) {
                if (i != j && l > k) {
                    //auto& trans1 = p_ecs.GetComponent<Transform>(i);
                    auto& trans2 = p_ecs.GetComponent<Transform>(j);
                    //vec2D ent1pos = trans1.GetPos();
                    vec2D ent2pos = trans2.GetPos();
                    //do a distance check disqualifier
                    //std::cout << "Distance: " << squaredistance(ent1pos, ent2pos) << "\n";
                    if (ent2pos.x - ent1pos.x < 1 && ent2pos.x - ent1pos.x > -1 && ent2pos.y - ent1pos.y < 1 && ent2pos.y - ent1pos.y > -1) {
                        //check entity 1 and 2 collider
                        auto& rigid1 = p_ecs.GetComponent<RigidBody>(i);
                        auto& rigid2 = p_ecs.GetComponent<RigidBody>(j);

                        auto& col1 = p_ecs.GetComponent<Collider>(i);
                        auto& col2 = p_ecs.GetComponent<Collider>(j);

                        Collider::ColliderType e1 = col1.GetCollider();
                        Collider::ColliderType e2 = col2.GetCollider();
                        //apply collision based on entity 1 and 2 collider types
                        //apply appropriate collision response
                        if (e1 == Collider::ColliderType::circle) {
                            circle_bound ent1;
                            ent1.center = ent1pos;
                            ent1.radius = col1.GetMax().x - ent1pos.x;
                            if (e2 == Collider::ColliderType::circle) {
                                circle_bound ent2;
                                ent1.center = ent2pos;
                                ent1.radius = col2.GetMax().x - ent2pos.x;
                                vec2D ent1colpt;
                                vec2D ent2colpt;
                                float coltime;
                                if (ecm.objCollision(ent1, rigid1.GetVel(), ent2, rigid2.GetVel(), ent1colpt, ent2colpt, coltime)) {
                                    std::cout << "hit\n";
                                    vec2D colnorm = ent1colpt - ent2pos;
                                    Normalize(colnorm, colnorm);
                                    vec2D ent1newvel = rigid1.GetVel();
                                    vec2D ent2newvel = rigid2.GetVel();
                                    vec2D ent1nextpos = rigid1.GetNextPos();
                                    vec2D ent2nextpos = rigid2.GetNextPos();
                                    //ecm.circleBounce(colnorm, coltime, rigid1.GetVel(), ent1colpt, rigid2.GetVel(), ent2colpt, ent1newvel, ent1nextpos, ent2newvel, ent2nextpos);
                                    rigid1.SetVel(ent1newvel);
                                    rigid2.SetVel(ent2newvel);
                                    rigid1.SetNextPos(ent1nextpos);
                                    rigid2.SetNextPos(ent2nextpos);
                                }
                            }
                            else if (e2 == Collider::ColliderType::line) {
                                wall wall2;
                                wall2.p0 = col2.GetMin();
                                wall2.p1 = col2.GetMax();
                                vec2D temp = wall2.p1 - wall2.p0;
                                wall2.normal.x = temp.y;
                                wall2.normal.y = -temp.x;
                                Normalize(wall2.normal, wall2.normal);
                                vec2D colpt;
                                vec2D colnorm;
                                vec2D entnextpos = rigid1.GetNextPos();
                                float coltime;
                                if (ecm.wallCollision(ent1, entnextpos, wall2, colpt, colnorm, coltime)) {
                                    std::cout << "hit\n";
                                    vec2D reflectiondir;
                                    //ecm.wallBounce(colpt, colnorm, entnextpos, reflectiondir);
                                    rigid1.SetNextPos(entnextpos);
                                }
                            }
                            else if (e2 == Collider::ColliderType::rect) {
                                if (ecm.boundingBoxCircle(ent1, col2.GetMax(), col2.GetMin())) {
                                    std::cout << "hit\n";
                                    //hit detected. take damage
                                }
                            }
                        }
                        else if (e1 == Collider::ColliderType::line) {
                            if (e2 == Collider::ColliderType::circle) {
                                wall wall2;
                                wall2.p0 = col1.GetMin();
                                wall2.p1 = col1.GetMax();
                                vec2D temp = wall2.p1 - wall2.p0;
                                wall2.normal.x = temp.y;
                                wall2.normal.y = -temp.x;
                                Normalize(wall2.normal, wall2.normal);
                                circle_bound ent1;
                                ent1.center = ent2pos;
                                ent1.radius = col2.GetMax().x - ent2pos.x;
                                vec2D colpt;
                                vec2D colnorm;
                                vec2D entnextpos = rigid2.GetNextPos();
                                float coltime;
                                if (ecm.wallCollision(ent1, entnextpos, wall2, colpt, colnorm, coltime)) {
                                    std::cout << "hit\n";
                                    vec2D reflectiondir;
                                    //ecm.wallBounce(colpt, colnorm, entnextpos, reflectiondir);
                                    rigid2.SetNextPos(entnextpos);
                                }
                            }
                        }
                        else if (e1 == Collider::ColliderType::rect) {
                            if (e2 == Collider::ColliderType::circle) {
                                circle_bound ent1;
                                ent1.center = ent2pos;
                                ent1.radius = col2.GetMax().x - ent2pos.x;
                                if (ecm.boundingBoxCircle(ent1, col1.GetMax(), col1.GetMin())) {
                                    std::cout << "hit\n";
                                    //hit detected. take damage
                                }
                            }
                            else if (e2 == Collider::ColliderType::rect) {
                                if (ecm.boundingBoxCollision(col1.GetMax(), col1.GetMin(), rigid1.GetVel(), col2.GetMax(), col2.GetMin(), rigid2.GetVel(), dt)) {
                                    std::cout << "hit\n";
                                    //parry mechanics? 
                                }
                            }
                        }
                    }
                }
                l++;
            }
            k++;
        }
    }
    void CollisionSystem::End() {
        //remove all entities from array
    }
}