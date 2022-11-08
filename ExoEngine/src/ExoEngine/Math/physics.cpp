#include "physics.h"


namespace EM {
    //class functions
    vec2D entityPhysics::accelent(vec2D& entvel, vec2D applied, float dt) {
        entvel += applied * dt;
        entvel = entvel * 0.99f * dt;
        return entvel;
    }
    vec2D entityPhysics::friction(vec2D& entvel, float dt) {
        entvel -= entvel * 9.5f * dt;
        return entvel;
    }
    vec2D entityPhysics::gravity(vec2D& entvel, float dt) {
        entvel.y -= 9.8f * dt;
        return entvel;
    }
    /*wall entityCollision::buildWall(vec2D pt1, vec2D pt2) {
        wall newWall;
        newWall.p0 = pt1;
        newWall.p1 = pt2;
        vec2D temp = newWall.p0 - newWall.p1;
        newWall.normal.x = -temp.y;
        newWall.normal.y = temp.x;
        Normalize(newWall.normal, newWall.normal);
        return newWall;
    }
    circle entityCollision::buildCircle(vec2D pos, float radius) {
        circle newCirc;
        newCirc.center = pos;
        newCirc.radius = radius;
        return newCirc;
    }
    castRay entityCollision::buildRay(vec2D pos, vec2D dir) {
        castRay newCast;
        newCast.pt0 = pos;
        newCast.dir = dir;
        return newCast;
    } NOT FUNCTIONING CURRENTLY--------------------------------------------------------------------------------------------*/
    //circle to wall
    bool entityCollision::wallCollision(const circle_bound&circle, const vec2D &entnextpos, const wall &wall, vec2D &colpt, vec2D &colnorm, float &coltime) {
        float circdot = dotProduct(wall.normal, circle.center);
        float normaldot = dotProduct(wall.normal, wall.p0);

        vec2D circVel = entnextpos - circle.center;
        vec2D circVelNormal;
        circVelNormal.x =  circVel.y;
        circVelNormal.y = -circVel.x;

        vec2D p0plusrad = (wall.p0 + circle.radius * wall.normal);
        vec2D p1plusrad = (wall.p1 + circle.radius * wall.normal);

        if (circdot - normaldot <= -circle.radius) {
            p0plusrad = (wall.p0 - circle.radius * wall.normal);
            p1plusrad = (wall.p1 - circle.radius * wall.normal);

            float dotprod1 = dotProduct(circVelNormal, p0plusrad - circle.center);
            float dotprod2 = dotProduct(circVelNormal, p1plusrad - circle.center);

            if (dotprod1 * dotprod2 < 0) {
                coltime = ((normaldot - circdot) - circle.radius) / (dotProduct(wall.normal, circVel));
                if (coltime >= 0 && coltime <= 1) {
                    colpt = circle.center + (circVel * coltime);
                    colnorm = -wall.normal;
                    return 1;
                }
                else {
                    return edgeCollision(false, circle, entnextpos, wall, colpt, colnorm, coltime);
                }
            }
        }
        else if (circdot - normaldot >= circle.radius) {
            p0plusrad = (wall.p0 + circle.radius * wall.normal);
            p1plusrad = (wall.p1 + circle.radius * wall.normal);

            float dotprod1 = dotProduct(circVelNormal, p0plusrad - circle.center);
            float dotprod2 = dotProduct(circVelNormal, p1plusrad - circle.center);

            if (dotprod1 * dotprod2 < 0) {
                coltime = ((normaldot - circdot) + circle.radius) / (dotProduct(wall.normal, circVel));
                if (coltime >= 0 && coltime <= 1) {
                    colpt = circle.center + (circVel * coltime);
                    colnorm = wall.normal;
                    return 1;
                }
                else {
                    return edgeCollision(false, circle, entnextpos, wall, colpt, colnorm, coltime);
                }
            }
        }
        else {
            return edgeCollision(true, circle, entnextpos, wall, colpt, colnorm, coltime);
        }
        return 0;
    }
    //circle to edge
    bool entityCollision::edgeCollision(bool willcollide, const circle_bound&circle, const vec2D &entnextpos, const wall &wall, vec2D &colpt, vec2D &colnorm,	float &coltime) {
        vec2D circVel = entnextpos - circle.center;
        vec2D normVel;
        Normalize(normVel, circVel);
        vec2D velNormal = vec2D(normVel.y, -normVel.x);
        if (willcollide) {
            if (dotProduct(wall.p0 - circle.center, wall.p1 - wall.p0) > 0) {
                float m = dotProduct(wall.p0 - circle.center, normVel);
                if (m > 0) {
                    float dist0 = dotProduct(wall.p0 - circle.center, velNormal);
                    if (abs(dist0) > circle.radius) {
                        return 0;
                    }
                    float s = sqrt(circle.radius * circle.radius - dist0 * dist0);
                    float ti = (m - s) / length(circVel);
                    if (ti <= 1) {
                        colpt = circle.center + circVel * ti;
                        coltime = ti;
                        Normalize(colnorm, colpt - wall.p0);
                        return 1;
                    }
                }
                return 0;
            }
            else if (dotProduct(wall.p0 - circle.center, wall.p1 - wall.p0) < 0) {
                float m = dotProduct(wall.p1 - circle.center, normVel);
                if (m > 0) {
                    float dist1 = dotProduct(wall.p1 - circle.center, velNormal);
                    if (abs(dist1) > circle.radius) {
                        return 0;
                    }
                    float s = sqrt(circle.radius * circle.radius - dist1 * dist1);
                    float ti = (m - s) / length(circVel);
                    if (ti <= 1) {
                        colpt = circle.center + circVel * ti;
                        coltime = ti;
                        Normalize(colnorm, colpt - wall.p1);
                        return 1;
                    }
                }
            }
        }
        else {
            bool P0Side = false;
            float dist0 = dotProduct(wall.p0 - circle.center, velNormal);
            float dist1 = dotProduct(wall.p1 - circle.center, velNormal);
            if (abs(dist0) > circle.radius && abs(dist1) > circle.radius) {
                return 0;
            }
            else if (abs(dist0) <= circle.radius && abs(dist1) <= circle.radius) {
                float m0 = dotProduct(wall.p0 - circle.center, normVel);
                float m1 = dotProduct(wall.p1 - circle.center, normVel);
                if (abs(m0) < abs(m1)) {
                    P0Side = true;
                }
                else {
                    P0Side = false;
                }
            }
            else if (abs(dist0) <= circle.radius) {
                P0Side = true;
            }
            else {
                P0Side = false;
            }

            if (P0Side) {
                float m = dotProduct(wall.p0 - circle.center, normVel);
                if (m < 0) {
                    return false;
                }
                else {
                    float s = sqrt(circle.radius * circle.radius - dist0 * dist0);
                    float ti = (m - s) / length(circVel);
                    if (ti <= 1) {
                        colpt = circle.center + circVel * ti;
                        coltime = ti;
                        Normalize(colnorm, colpt - wall.p0);
                        return 1;
                    }
                    return 0;
                }
            }
            else {
                float m = dotProduct(wall.p1 - circle.center, normVel);
                if (m < 0) {
                    return false;
                }
                else {
                    float s = sqrt(circle.radius * circle.radius - dist1 * dist1);
                    float ti = (m - s) / length(circVel);
                    if (ti <= 1) {
                        colpt = circle.center + circVel * ti;
                        coltime = ti;
                        Normalize(colnorm, colpt - wall.p1);
                        return 1;
                    }
                    return 0;
                }
            }
        }
        return 0;
    }
    //circle to circle
    bool entityCollision::objCollision(const circle_bound&ent1, const vec2D &ent1vel, const circle_bound&ent2, const vec2D &ent2vel, vec2D &ent1colpt, vec2D &ent2colpt, float &coltime) {
        vec2D relativeVel = ent1vel - ent2vel;
        circle_bound tempCirc;
        tempCirc.center = ent2.center;
        tempCirc.radius = ent1.radius + ent2.radius;
        castRay tempRay;
        tempRay.pt0 = ent1.center;
        tempRay.dir = relativeVel;

        //collision ray-circle
        vec2D rayToCirc = tempCirc.center - tempRay.pt0;
        vec2D normalRay;
        Normalize(normalRay, tempRay.dir);
        float actualdist = length(rayToCirc);
        float vectorDot = dotProduct(rayToCirc, normalRay);
        if (vectorDot < 0 && actualdist > tempCirc.radius) {
            return 0;
        }
        float distOsquared = squarelength(rayToCirc) - (vectorDot * vectorDot);
        if (distOsquared > tempCirc.radius * tempCirc.radius && actualdist > tempCirc.radius) {
            return 0;
        }
        float s = sqrt(tempCirc.radius * tempCirc.radius - distOsquared);
        float ti0 = (vectorDot - s) / length(tempRay.dir);
        float ti1 = (vectorDot + s) / length(tempRay.dir);
        coltime = std::min(ti0, ti1);
        if ((coltime > 1 || coltime < 0)) {
            return 0;
        }
        else {
            ent1colpt = ent1.center + ent1vel * coltime;
            ent2colpt = ent2.center + ent2vel * coltime;
            return 1;
        }
    }
    //AABB Collision
    bool entityCollision::boundingBoxCollision(vec2D max1, vec2D min1, vec2D vel1, vec2D max2, vec2D min2, vec2D vel2, float dt) {
        //Static collision
        if (!(min1.x > max2.x || min2.x > max1.x || max1.y < min2.y || max2.y < min1.y)) {
            return true;
        }
        //dynamic collision
        float tFirst = 0;
        float tLast = dt;//dt
        vec2D relvel = vel2 - vel1;
        vec2D dFirst = min1 - max2;
        vec2D dLast = max1 - min2;
        if (relvel.x < 0) {
            if (min1.x > max2.x) {
                return false;
            }
            if (max1.x < min2.x && dFirst.x / relvel.x > tFirst) {
                tFirst = std::max(dFirst.x / relvel.x, tFirst);
            }
            if (max1.x > min2.x && (dLast.x / relvel.x) < tLast) {
                tLast = std::min(dLast.x / relvel.x, tLast);
            }
        }
        if (relvel.x > 0) {
            if (max1.x < min2.x) {
                return false;
            }
            if (min1.x > max2.x && (dFirst.x / relvel.x) > tFirst) {
                tFirst = std::max(dFirst.x / relvel.x, tFirst);
            }
            if (max1.x > min2.x && dLast.x / relvel.x < tLast) {
                tLast = std::min(dLast.x / relvel.x, tLast);
            }
        }
        if (tFirst > tLast) {
            return false;
        }
        if (relvel.y < 0) {
            if (min1.y > max2.y) {
                return false;
            }
            if (max1.y < min2.y && (dFirst.y / relvel.y) > tFirst) {
                tFirst = std::max((max1.y - min2.y) / relvel.y, tFirst);
            }
            if (max1.y > min2.y && (dLast.y / relvel.y) < tLast) {
                tLast = std::min((min1.y - max2.y) / relvel.y, tLast);
            }

        }
        if (relvel.y > 0) {
            if (max1.y < min2.y) {
                return false;
            }
            if (min1.y > max2.y && (dFirst.y / relvel.y) > tFirst) {
                tFirst = std::max((min1.y - max2.y) / relvel.y, tFirst);
            }
            if (max1.y > min2.y && (dLast.y / relvel.y) < tLast) {
                tLast = std::min((max1.y - min2.y) / relvel.y, tLast);
            }

        }
        if (tFirst > tLast) {
            return false;
        }
        //if all falls through, return no collision
        return false;
    }
    //circle aabb collision
    bool entityCollision::boundingBoxCircle(const circle_bound& ent1, vec2D max2, vec2D min2) {
        if (min2.x - ent1.center.x > ent1.radius || ent1.center.x - max2.x > ent1.radius ||
            min2.y - ent1.center.y > ent1.radius || ent1.center.y - max2.y > ent1.radius) {
            return 0;
        }
        vec2D topleft(min2.x, max2.y);
        vec2D bottomright(max2.x, min2.y);
        if (distance(ent1.center, min2) > ent1.radius && distance(ent1.center, max2) > ent1.radius &&
            distance(ent1.center, topleft) > ent1.radius && distance(ent1.center, bottomright) > ent1.radius) {
            return 0;
        }
        return 1;
    }
    //circle wall reaction
    void entityCollision::wallBounce(const vec2D &colpt, const vec2D &ptnorm, vec2D &entnextpos, vec2D &reflectiondir) {
        vec2D penPoint = entnextpos - colpt;
        float dotprod = 2 * (dotProduct(penPoint, ptnorm));
        entnextpos = colpt + penPoint - (dotprod * ptnorm);
        reflectiondir = entnextpos - colpt;
        Normalize(reflectiondir, reflectiondir);
    }
    //circle circle reaction
    void entityCollision::circleBounce(const vec2D &colnorm, const float coltime, vec2D &ent1vel, vec2D &ent1colpt, vec2D &ent2vel, vec2D &ent2colpt, vec2D &ent1newvel, vec2D &ent1nextpos, vec2D &ent2newvel, vec2D &ent2nextpos) {
        float magA = dotProduct(ent1vel, colnorm);
        float magB = dotProduct(ent2vel, colnorm);
        float forceMagnitude = 2 * (magA - magB) / (1 + 1);
        ent1newvel = ent1vel - (colnorm * forceMagnitude * 1);
        ent2newvel = ent2vel + (colnorm * forceMagnitude * 1);
        ent1nextpos = ent1colpt + ent1newvel * (1 - coltime);
        ent2nextpos = ent2colpt + ent2newvel * (1 - coltime);
    }
    //circle obstacle reaction
    void entityCollision::obstacleBounce(const vec2D &colnorm, const vec2D &colpt, vec2D &entnextpos, vec2D &reflectionnorm) {
        vec2D penPoint = entnextpos - colpt;
        float dotprod = 2 * (dotProduct(penPoint, colnorm));
        entnextpos = colpt + penPoint - (dotprod * colnorm);
        reflectionnorm = entnextpos - colpt;
        Normalize(reflectionnorm, reflectionnorm);
    }
    void accelent(vec2D &entvel, vec2D dir, float mag, float lim) {
        entvel += (dir * mag);
        if (length(entvel) >= lim) {
            entvel = 0.9f * entvel;
        }
    }
    void decelent(vec2D &entvel) {
        if (length(entvel) > 0) {
            entvel -= entvel * 0.5;
        }
    }

    void Knockback()
    {

    }
}