/*!*****************************************************************************
\file physics.h
\author Tan Ek Hern, Lau Yong Hui
\par DP email: t.ekhern@digipen.edu, l.yonghui@digipen.edu
\par Course: csd2125
\par Section: a
\par 
\date 14-10-2022
\brief  This file contains the function definitions for calculating acceleration
        and deceleration as well as detecting collision
 
 Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
*******************************************************************************/
#include "empch.h"
#include "physics.h"
#include "Vmath.h"

namespace EM {
    /*!*************************************************************************
    This function takes in the current velocity of the object and applies acceleration
    to it and multiplying said acceleration by the frame time to ensure consistent
    acceleration regardless of frame rate
    ****************************************************************************/
    vec2D entityPhysics::accelent(vec2D& entvel, vec2D applied, float dt) {
        entvel += applied * dt;
        entvel = entvel * 0.99f * dt;
        return entvel;
    }
    /*!*************************************************************************
    This function takes in the current velocity of the object and applies deceleration
    to it and multiplying said deceleration by the frame time to ensure consistent
    acceleration regardless of frame rate
    ****************************************************************************/
    vec2D entityPhysics::friction(vec2D& entvel, float dt) {
        entvel -= entvel * 8.5f * dt;
        return entvel;
    }
    /*!*************************************************************************
    This function takes in the current velocity of the object and applies gravity
    to it and multiplying said acceleration by the frame time to ensure consistent
    acceleration regardless of frame rate
    ****************************************************************************/
    vec2D entityPhysics::gravity(vec2D& entvel, float dt) {
        entvel.y -= 9.8f * dt;
        return entvel;
    }
    /*!*************************************************************************
    This function is a simple static circle to circle collision detection function
    that returns a boolean inditating whether collision was detected or not
    ****************************************************************************/
    int entityCollision::simpleCircleCircle(vec2D ent1, vec2D ent2, float rad1, float rad2) {
        if (distance(ent1, ent2) <= (rad1+rad2)) {
            return 1;
        }
        else {
            return 0;
        }
    }
    /*!*************************************************************************
    This function is a simple static circle to line collision detection function
    that returns a boolean inditating whether collision was detected or not
    ****************************************************************************/
    int entityCollision::simpleCircleLine(vec2D ent1, float rad1, vec2D max1, vec2D min1) {
        vec2D lineNormal = vec2D();
        lineNormal.x = max1.y - min1.y;
        lineNormal.y = min1.x - max1.x;
        vec2D straightLine = ent1 - min1;
        float straightDist = dotProduct(straightLine, lineNormal);
        if (straightDist <= rad1) {
            return 1;
        }
        else {
            return 0;
        }
    }
    /*!*************************************************************************
    This function is a simple static circle to point collision detection function
    that returns a boolean inditating whether collision was detected or not
    ****************************************************************************/
    int entityCollision::simpleCirclePoint(vec2D ent1, float rad1, vec2D pt1) {
        if (distance(ent1, pt1) <= rad1) {
            return 1;
        }
        else {
            return 0;
        }
    }
    /*!*************************************************************************
    This function is a simple static circle to AABB collision detection function
    that returns a boolean inditating whether collision was detected or not
    ****************************************************************************/
    int entityCollision::simpleCircleRect(vec2D ent1, float rad1, vec2D max1, vec2D min1, vec2D center) {
        UNREFERENCED_PARAMETER(min1);
        vec2D dist = vec2D();
        dist.x = center.x - ent1.x;
        dist.y = center.y - ent1.y;
        if (dist.x > (rad1+max1.x-center.x) || dist.x < -(rad1+max1.x-center.x) || dist.y > (rad1+max1.y-center.y) || dist.y < -(rad1+max1.y-center.y)) {
            return 0;
        }
        /*vec2D topleft = vec2D(min1.x, max1.y);
        vec2D bottomright = vec2D(max1.x, min1.y);
        if (distance(ent1, max1) > rad1 || distance(ent1, min1) > rad1 || distance(ent1, topleft) > rad1 || distance(ent1, bottomright) > rad1) {
            return 0;
        }*/
        return 1;
    }
    /*!*************************************************************************
    This function is a simple static AABB to AABB collision detection function
    that returns a boolean inditating whether collision was detected or not
    ****************************************************************************/
    int entityCollision::simpleRectRect(vec2D max1, vec2D min1, vec2D max2, vec2D min2) {
        
        if (!(min1.x > max2.x || min2.x > max1.x || max1.y < min2.y || max2.y < min1.y)) {
            return true;
        }
        else
            return false;
    }
    /*!*************************************************************************
    This function is a simple static circle to playable area AABB collision detection 
    function that returns a boolean inditating whether collision was detected or not
    ****************************************************************************/
    int entityCollision::simpleBoxCircle(vec2D ent1, float rad1, vec2D min1, vec2D max1) {
        if ((ent1.x - min1.x) <= rad1 || (max1.x - ent1.x) <= rad1 || (ent1.y - min1.y) <= rad1 || (max1.y - ent1.y) <= rad1) {
            return 1;
        }
        else {
            return 0;
        }
    }
    /*!*************************************************************************
    This function is a possible function to declare in the event that the game 
    requires the calculation of knockback upon some event.
    ****************************************************************************/
    void Knockback()
    {

    }
}