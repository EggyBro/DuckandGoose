/*!*****************************************************************************
\file physics.h
\author Tan Ek Hern, Lau Yong Hui
\par DP email: t.ekhern@digipen.edu, l.yonghui@digipen.edu
\par Course: csd2125
\par Section: a
\par 
\date 14-10-2022
\brief  This file contains the function declarations for calculating acceleration
        and deceleration as well as detecting collision
 
*******************************************************************************/
#pragma once

#include "empch.h"
#include "Vmath.h"

namespace EM {
    class entityPhysics {
        public: 
            /*!*************************************************************************
            This function takes in the current velocity of the object and applies acceleration
            to it and multiplying said acceleration by the frame time to ensure consistent
            acceleration regardless of frame rate
            ****************************************************************************/
            vec2D accelent(vec2D& entvel, vec2D applied, float dt);
            /*!*************************************************************************
            This function takes in the current velocity of the object and applies deceleration
            to it and multiplying said deceleration by the frame time to ensure consistent
            acceleration regardless of frame rate
            ****************************************************************************/
            vec2D friction(vec2D& entvel, float dt);
            /*!*************************************************************************
            This function takes in the current velocity of the object and applies gravity
            to it and multiplying said acceleration by the frame time to ensure consistent
            acceleration regardless of frame rate
            ****************************************************************************/
            vec2D gravity(vec2D& entvel, float dt);
    };

    class entityCollision {
        public:
            entityCollision() = default;
            /*Dynamic collision set no longer in use
            bool wallCollision(const circle_bound& circle, const vec2D& entnextpos, const wall& wall, vec2D& colpt, vec2D& colnorm, float& coltime);
            bool edgeCollision(bool willcollide, const circle_bound& circle, const vec2D& entnextpos, const wall& wall, vec2D& colpt, vec2D& colnorm, float& coltime);
            bool objCollision(const circle_bound& ent1, const vec2D& ent1vel, const circle_bound& ent2, const vec2D& ent2vel, vec2D& ent1colpt, vec2D& ent2colpt, float& coltime);
            bool boundingBoxCollision(vec2D max1, vec2D min1, vec2D vel1, vec2D max2, vec2D min2, vec2D vel2, float dt);
            bool boundingBoxCircle(const circle_bound& ent1, vec2D max2, vec2D min2);
            void wallBounce(const vec2D& colpt, const vec2D& ptnorm, vec2D& entnextpos, vec2D& reflectiondir);
            void circleBounce(const vec2D& colnorm, const float coltime, vec2D& ent1vel, vec2D& ent1colpt, vec2D& ent2vel, vec2D& ent2colpt, vec2D& ent1newvel, vec2D& ent1nextpos, vec2D& ent2newvel, vec2D& ent2nextpos);
            void obstacleBounce(const vec2D& colnorm, const vec2D& colpt, vec2D& entnextpos, vec2D& reflectionnorm);*/
    
        public:
            /*!*************************************************************************
            This function is a simple static circle to circle collision detection function
            that returns a boolean inditating whether collision was detected or not
            ****************************************************************************/
            int simpleCircleCircle(vec2D ent1, vec2D ent2, float rad1, float rad2);
            /*!*************************************************************************
            This function is a simple static circle to line collision detection function
            that returns a boolean inditating whether collision was detected or not
            ****************************************************************************/
            int simpleCircleLine(vec2D ent1, float rad1, vec2D max1, vec2D min1);
            /*!*************************************************************************
            This function is a simple static circle to point collision detection function
            that returns a boolean inditating whether collision was detected or not
            ****************************************************************************/
            int simpleCirclePoint(vec2D ent1, float rad1, vec2D pt1);
            /*!*************************************************************************
            This function is a simple static circle to AABB collision detection function
            that returns a boolean inditating whether collision was detected or not
            ****************************************************************************/
            int simpleCircleRect(vec2D ent1, float rad1, vec2D max1, vec2D min1, vec2D center);
            /*!*************************************************************************
            This function is a simple static AABB to AABB collision detection function
            that returns a boolean inditating whether collision was detected or not
            ****************************************************************************/
            int simpleRectRect(vec2D max1, vec2D min1, vec2D max2, vec2D min2);
            /*!*************************************************************************
            This function is a simple static circle to playable area AABB collision detection 
            function that returns a boolean inditating whether collision was detected or not
            ****************************************************************************/
            int simpleBoxCircle(vec2D ent1, float rad1, vec2D min1, vec2D max1);
    };
}