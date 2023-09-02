#include <box2d/box2d.h>
#include <testbed2d/entity.h>
#include <testbed2d/util.h>

#include "SumoRingObj.h"

SumoRing::SumoRing(Test* test, const b2Vec2& position)
    : Entity(test, b2_staticBody, position, 0.0f)
{}

b2Fixture* SumoRing::setup() {
    Mesh mesh;
    mesh.loadFromObjString(SUMORING_OBJ);

    for (int i = 0; i < mesh.triangles.size(); ++i) {
        b2Vec2 points[3];
        for (int j = 0; j < 3; j++) {
            points[2 - j] = b2Vec2(
                mesh.vertices[mesh.triangles[i][j]][0],
                mesh.vertices[mesh.triangles[i][j]][2]
            );
        }

        b2PolygonShape triangleShape;
        triangleShape.Set(points, 3);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &triangleShape;
        fixtureDef.isSensor = true;
        Entity::setup(fixtureDef);
    }

    return nullptr;
}
