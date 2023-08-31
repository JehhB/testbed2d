#ifndef TESTBED2D_ENTITY_H
#define TESTBED2D_ENTITY_H

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

#endif
