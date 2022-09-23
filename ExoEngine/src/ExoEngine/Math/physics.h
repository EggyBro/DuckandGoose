#ifndef PHYSICS_H_
#define PHYSICS_H_
namespace EXOMATA {
    //collision logic
    struct wall {
        vec2D	p1;
        vec2D	p2;
        vec2D	normal;
    };
    struct circle {
        vec2D   center;
        float	rad; //mass tied to radius
    };
    struct castRay {
        vec2D	pt0;
        vec2D	dir;
    };
    /***************************************************************************//*!
    \brief
    creates a wall segment

    \param[in] pt1
    start point of wall
	\param[in] pt2
    end point of wall

    \return
    a wall struct with values initialised
    *//**************************************************************************/
    wall buildWall(vec2D pt1, vec2D pt2);
    /***************************************************************************//*!
    \brief
    creates a circle

    \param[in] pos
    coordinate point of circle
	\param[in] radius
    radius of circle

    \return
    a circle struct with values initialised
    *//**************************************************************************/
    circle buildCircle(vec2D pos, float radius);
    /***************************************************************************//*!
    \brief
    creates a ray

    \param[in] pos
    start point of ray
	\param[in] dir
    direction of ray

    \return
    a ray struct with values initialised
    *//**************************************************************************/
    castRay buildRay(vec2D pos, vec2D dir);
    /***************************************************************************//*!
    \brief
    calculates collision between a circle and wall

    \param[in] circle
    struct of the circle to check
	\param[in] entnextpos
    end position of the circle
    \param[in] wall
    struct of the wall to check
	\param[out] colpt
    point of collision between entity and wall
    \param[out] colnorm
    normal at point of collision
	\param[out] coltime
    time of collision

    \return
    boolean indicating collision true or false
    *//**************************************************************************/
    bool wallCollision(const circle &circle, const vec2D &entnextpos, const wall &wall, vec2D &colpt, vec2D &colnorm, float &coltime); 
    /***************************************************************************//*!
    \brief
    calculates collision between a circle and edge of wall

    \param[in] willcollide
    bool indicating if circle is travelling in a direction that will cause a collision
    with the wall
    \param[in] circle
    struct of the circle to check
	\param[in] entnextpos
    end position of the circle
    \param[in] wall
    struct of the wall to check
	\param[out] colpt
    point of collision between entity and wall
    \param[out] colnorm
    normal at point of collision
	\param[out] coltime
    time of collision

    \return
    boolean indicating collision true or false
    *//**************************************************************************/
    bool edgeCollision(bool willcollide, const circle &circle, const vec2D &entnextpos, const wall &wall, vec2D &colpt, vec2D &colnorm,	float &coltime);
    /***************************************************************************//*!
    \brief
    calculates collision between two circles

    \param[in] ent1
    struct of the first circle
    \param[in] ent1vel
    velocity of first circle
    \param[in] ent2
    struct of the second circle
	\param[in] ent2vel
    velocity of second circle
    \param[out] ent1colpt
    point of collision for first circle
	\param[out] ent2colpt
    point of collision for second circle
    \param[out] coltime
    time of collision

    \return
    boolean indicating collision true or false
    *//**************************************************************************/
    bool objCollision(const circle &ent1, const vec2D &ent1vel, const circle &ent2, const vec2D &ent2vel, vec2D &ent1colpt, vec2D &ent2colpt, float &coltime);
    /***************************************************************************//*!
    \brief
    calculates collision between a cone and a circle. Used for hit detection. 

    \param[in] ent1
    struct of the circle which will be the cone
    \param[in] startAngle
    angle of the start of the cone in degrees
    \param[in] endAngle
    angle of the end of the cone in degrees
    \param[in] lr
    bool indicating facing left or right (1 right, 0 left)
    \param[in] ent2
    struct of the second circle

    \return
    boolean indicating collision true or false
    *//**************************************************************************/
    bool coneCollision(const circle &ent1, const int startAngle, const int endAngle, bool lr, const circle &ent2);
    /***************************************************************************//*!
    \brief
    calculates collision response between a circle and wall

    \param[in] colpt
    point of collision
	\param[in] ptnorm
    normal at point of reflection
    \param[out] entnextpos
    next position of object
	\param[out] reflectiondir
    normalised direction of the reflected vector
    *//**************************************************************************/
    void wallBounce(const vec2D &colpt, const vec2D &ptnorm, vec2D &entnextpos, vec2D &reflectiondir);
    /***************************************************************************//*!
    \brief
    calculates collision response between a circle and edge

    \param[in] colnorm
    normal at point of collision
    \param[in] coltime
    time of collision
    \param[in] ent1vel
    velocity of first circle
	\param[in] ent1colpt
    point of collision for object 1
    \param[in] ent2vel
    velocity of second circle
	\param[in] ent2colpt
    point of collision for object 2
    \param[out] ent1newvel
    new velocity of object 1
	\param[out] ent1nextpos
    next position of object 1
    \param[out] ent2newvel
    new velocity of object 2
	\param[out] ent2nextpos
    next position of object 2
    *//**************************************************************************/
    void circleBounce(const vec2D &colnorm, const float coltime, vec2D &ent1vel, vec2D &ent1colpt, vec2D &ent2vel, vec2D &ent2colpt, vec2D &ent1newvel, vec2D &ent1nextpos, vec2D &ent2newvel, vec2D &ent2nextpos);
    /***************************************************************************//*!
    \brief
    calculates collision response between a circle and edge

    \param[in] colnorm
    normal at point of collision
    \param[in] colpt
    point of collision
	\param[out] entnextpos
    next position of object
    \param[out] reflectionnorm
    normalised direction of the reflected vector
    *//**************************************************************************/
    void obstacleBounce(const vec2D &colnorm, const vec2D &colpt, vec2D &entnextpos,vec2D &reflectionnorm);

    //acceleration, deceleration logic
    void accelent(vec2D &entvel, vec2D dir, float mag, float lim);
    void decelent(vec2D &entvel);
    //gravity logic

    //friction logic
}
#endif