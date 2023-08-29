#ifndef TESTBED2D_ENTITY_H
#define TESTBED2D_ENTITY_H

#include <testbed2d/test.h>

class SumoRing {
public:
    SumoRing(Test *test);
protected:
    Test* m_test;
};

#endif
