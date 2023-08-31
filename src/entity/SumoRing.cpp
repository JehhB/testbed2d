#include <box2d/box2d.h>
#include <testbed2d/entity.h>
#include <testbed2d/util.h>

#include "SumoRingObj.h"

SumoRing::SumoRing(Test *test) {
    m_test = test;

    Mesh mesh;
    mesh.loadFromObjString(SUMORING_OBJ);

    b2BodyDef sumoRingBodyDef;
    sumoRingBodyDef.type = b2_staticBody;
    sumoRingBodyDef.position.Set(0, 0);

    m_body = m_test->getWorld()->CreateBody(&sumoRingBodyDef);

    for (const std::array<int, 3> triangle : mesh.triangles) {
        b2Vec2 points[4];
		for (int i = 0; i < 3; i++) {
			points[2-i] = b2Vec2(mesh.vertices[triangle[i]][0], mesh.vertices[triangle[i]][2]);
		}

        b2PolygonShape triangleShape;
        triangleShape.Set(points, 3);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &triangleShape;
        m_body->CreateFixture(&fixtureDef);
    }
}