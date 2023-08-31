#ifndef TESTBED2D_ENTITY_H
#define TESTBED2D_ENTITY_H

#define DEGTOGRAD b2_pi / 180.0f

#include <testbed2d/test.h>
#include <testbed2d/settings.h>
#include <box2d/box2d.h>

class SumoRing {
public:
    SumoRing(Test *test);
    friend class Test;
    Test* m_test;
    b2Body* m_body;
};

class Wheel {
public: 
    Wheel(Test* test);

    void step(Settings& settings, float force);

    float m_maxLateralImpulse;
    float m_drag;
    Test* m_test;
    b2Body* m_body;
};

class DifferentialDriveCar {
public:
    DifferentialDriveCar(Test *test);

    void step(Settings& settings, float forceLeft, float forceRight);

    b2Body* m_body;
    Wheel m_leftWheel;
    Wheel m_rightWheel;
    Test* m_test;

    float getMaxLateralImpulse() const;
    float getDrag() const;
    void setMaxLateralImpulse(float maxLateralImpulse);
    void setDrag(float drag);

private:
    float m_maxLateralImpulse;
    float m_drag;
};

#endif
