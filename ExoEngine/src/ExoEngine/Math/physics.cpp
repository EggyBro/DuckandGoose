#include "physics.h"


namespace EM {
    wall buildWall(vec2D pt1, vec2D pt2) {
        wall newWall;
        newWall.p0 = pt1;
        newWall.p1 = pt2;
        vec2D temp = newWall.p0 - newWall.p1;
        newWall.normal.value.x = -temp.value.y;
        newWall.normal.value.y = temp.value.x;
        Normalize(newWall.normal, newWall.normal);
        return newWall;
    }
    circle buildCircle(vec2D pos, float radius) {
        circle newCirc;
        newCirc.center = pos;
        newCirc.radius = radius;
        return newCirc;
    }
    castRay buildRay(vec2D pos, vec2D dir) {
        castRay newCast;
        newCast.pt0 = pos;
        newCast.dir = dir;
        return newCast;
    }
    //circle to wall
    bool wallCollision(const circle &circle, const vec2D &entnextpos, const wall &wall, vec2D &colpt, vec2D &colnorm, float &coltime, bool & edgecheck) {
        float circdot = dotProduct(wall.normal, circle.center);
        float normaldot = dotProduct(wall.normal, wall.p0);

        vec2D circVel = entnextpos - circle.center;
        vec2D circVelNormal;
        circVelNormal.value.x =  circVel.value.y;
        circVelNormal.value.y = -circVel.value.x;

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
    bool edgeCollision(bool willcollide, const circle &circle, const vec2D &entnextpos, const wall &wall, vec2D &colpt, vec2D &colnorm,	float &coltime) {
        vec2D circVel = entnextpos - circle.center;
        vec2D normVel;
        Normalize(normVel, circVel);
        vec2D velNormal = vec2D(normVel.value.y, -normVel.value.x);
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
    bool objCollision(const circle &ent1, const vec2D &ent1vel, const circle &ent2, const vec2D &ent2vel, vec2D &ent1colpt, vec2D &ent2colpt, float &coltime) {
        vec2D relativeVel = ent1vel - ent2vel;
        circle tempCirc;
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
    //cone circle collision
    bool coneCollision(const circle &ent1, const int startAngle, const int endAngle, bool lr, const circle &ent2) {
        vec2D dist0 = ent2.center - ent1.center;
        float startRad = startAngle / 180 * (atan(1) * 4);
        float endRad = endAngle / 180 * (atan(1) * 4);
        vec2D dir1;
        vec2D dir2;
        if (length(dist0) > ent1.radius + ent2.radius) {
            return 0;
        }
        //check if within cone
        if(lr) {
            //get start and end of cone
            dir1.value.x = -cos(startRad);
            dir1.value.y = sin(startRad);
            dir2.value.x = -cos(endRad);
            dir2.value.y = -sin(endRad);
        }
        else {
            //get start and end of cone
            dir1.value.x = cos(startRad);
            dir1.value.y = sin(startRad);
            dir2.value.x = cos(endRad);
            dir2.value.y = -sin(endRad);
        }
        //check if above or below midpoint
        if (atan(dist0.value.y/dist0.value.x) > 0) {
            vec2D dist0Normal;
            dist0Normal.value.x = dir1.value.y;
            dist0Normal.value.y = -dir1.value.x;
            vec2D extended = ent2.center + (ent2.radius * dist0Normal);
            vec2D dist1 = extended - ent1.center;
            if (length(dist1) > ent1.radius || atan(dist1.value.y / dist1.value.x) > startRad) {
                return 0;
            }
        }
        else {
            vec2D dist0Normal;
            dist0Normal.value.x = -dir2.value.y;
            dist0Normal.value.y = dir2.value.x;
            vec2D extended = ent2.center + (ent2.radius * dist0Normal);
            vec2D dist1 = extended - ent1.center;
            if (length(dist1) > ent1.radius || -atan(dist1.value.y / dist1.value.x) > endRad) {
                return 0;
            }
        }
        return 1;
    }
    //AABB Collision
    bool boundingBoxCollision(vec2D max1, vec2D min1, vec2D vel1, vec2D max2, vec2D min2, vec2D vel2) {
        //Static collision
        if (!(min1.value.x > max2.value.x || min2.value.x > max1.value.x || max1.value.y < min2.value.y || max2.value.y < min1.value.y)) {
            return true;
        }
        //dynamic collision
        float tFirst = 0;
        float tLast = 1;
        vec2D relvel = vel2 - vel1;
        vec2D dFirst = min1 - max2;
        vec2D dLast = max1 - min2;
        if (relvel.value.x < 0) {
            if (min1.value.x > max2.value.x) {
                return false;
            }
            if (max1.value.x < min2.value.x && dFirst.value.x / relvel.value.x > tFirst) {
                tFirst = std::max(dFirst.value.x / relvel.value.x, tFirst);
            }
            if (max1.value.x > min2.value.x && (dLast.value.x / relvel.value.x) < tLast) {
                tLast = std::min(dLast.value.x / relvel.value.x, tLast);
            }
        }
        if (relvel.value.x > 0) {
            if (max1.value.x < min2.value.x) {
                return false;
            }
            if (min1.value.x > max2.value.x && (dFirst.value.x / relvel.value.x) > tFirst) {
                tFirst = std::max(dFirst.value.x / relvel.value.x, tFirst);
            }
            if (max1.value.x > min2.value.x && dLast.value.x / relvel.value.x < tLast) {
                tLast = std::min(dLast.value.x / relvel.value.x, tLast);
            }
        }
        if (tFirst > tLast) {
            return false;
        }
        if (relvel.value.y < 0) {
            if (min1.value.y > max2.value.y) {
                return false;
            }
            if (max1.value.y < min2.value.y && (dFirst.value.y / relvel.value.y) > tFirst) {
                tFirst = std::max((max1.value.y - min2.value.y) / relvel.value.y, tFirst);
            }
            if (max1.value.y > min2.value.y && (dLast.value.y / relvel.value.y) < tLast) {
                tLast = std::min((min1.value.y - max2.value.y) / relvel.value.y, tLast);
            }

        }
        if (relvel.value.y > 0) {
            if (max1.value.y < min2.value.y) {
                return false;
            }
            if (min1.value.y > max2.value.y && (dFirst.value.y / relvel.value.y) > tFirst) {
                tFirst = std::max((min1.value.y - max2.value.y) / relvel.value.y, tFirst);
            }
            if (max1.value.y > min2.value.y && (dLast.value.y / relvel.value.y) < tLast) {
                tLast = std::min((max1.value.y - min2.value.y) / relvel.value.y, tLast);
            }

        }
        if (tFirst > tLast) {
            return false;
        }
        //if all falls through, return no collision
        return false;
    }

    //circle wall reaction
    void wallBounce(const vec2D &colpt, const vec2D &ptnorm, vec2D &entnextpos, vec2D &reflectiondir) {
        vec2D penPoint = entnextpos - colpt;
        float dotprod = 2 * (dotProduct(penPoint, ptnorm));
        entnextpos = colpt + penPoint - (dotprod * ptnorm);
        reflectiondir = entnextpos - colpt;
        Normalize(reflectiondir, reflectiondir);
    }
    //circle circle reaction
    void circleBounce(const vec2D &colnorm, const float coltime, vec2D &ent1vel, vec2D &ent1colpt, vec2D &ent2vel, vec2D &ent2colpt, vec2D &ent1newvel, vec2D &ent1nextpos, vec2D &ent2newvel, vec2D &ent2nextpos) {
        float magA = dotProduct(ent1vel, colnorm);
        float magB = dotProduct(ent2vel, colnorm);
        float forceMagnitude = 2 * (magA - magB) / (1 + 1);
        ent1newvel = ent1vel - (colnorm * forceMagnitude * 1);
        ent2newvel = ent2vel + (colnorm * forceMagnitude * 1);
        ent1nextpos = ent1colpt + ent1newvel * (1 - coltime);
        ent2nextpos = ent2colpt + ent2newvel * (1 - coltime);
    }
    //circle obstacle reaction
    void obstacleBounce(const vec2D &colnorm, const vec2D &colpt, vec2D &entnextpos, vec2D &reflectionnorm) {
        vec2D penPoint = entnextpos - colpt;
        float dotprod = 2 * (dotProduct(penPoint, colnorm));
        entnextpos = colpt + penPoint - (dotprod * colnorm);
        reflectionnorm = entnextpos - colpt;
        Normalize(reflectionnorm, reflectionnorm);
    }

    void accelent(vec2D &entvel, vec2D dir, float mag, float lim) {
        entvel += (dir * mag);
        if (length(entvel) >= lim) {
            entvel = 0.9 * entvel;
        }
    }
    void decelent(vec2D &entvel) {
        if (length(entvel) > 0) {
            entvel -= entvel * 0.5;
        }
    }
}