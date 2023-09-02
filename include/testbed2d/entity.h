#ifndef TESTBED2D_ENTITY_H
#define TESTBED2D_ENTITY_H

#define DEGTOGRAD b2_pi / 180.0f

#include <testbed2d/test.h>
#include <testbed2d/settings.h>
#include <box2d/box2d.h>

class Entity {
public:
    Entity(Test* test, b2Body* body);
    Entity(Test* test, b2BodyDef& bodyDef);
    Entity(Test* test, const b2BodyType& type, const b2Vec2& position = b2Vec2_zero, float angle = 0.0f);
    virtual ~Entity() {};

    virtual b2Fixture* setup(b2FixtureDef& fixtureDef);
    virtual b2Fixture* setup();

    virtual void step(Settings& setting);

    b2Body* getBody() const;
    b2World* getWorld() const;
    Test* getTest() const;

protected:
    b2Body* m_body;
    Test* m_test;
};

class SumoRing : public Entity {
public:
    SumoRing(Test *test, const b2Vec2& position = b2Vec2_zero);

    b2Fixture* setup() override;
};

class Wheel : public Entity {
public: 
    Wheel(Test* test, const b2Vec2& position = b2Vec2_zero, float angle = 0.0f);

    b2Fixture* setup() override;

    void step(Settings& settings) override;

    void setForce(float force);
    void setMaxLateralImpulse(float maxLateralImpulse);
    void setMaxAngularImpulse(float maxAngularImpulse);
    void setDrag(float drag);

    float getForce() const;
    float getMaxLateralImpulse() const;
    float getMaxAngularImpulse() const;
    float getDrag() const;

protected:
    float m_force;
    float m_maxLateralImpulse;
    float m_maxAngularImpulse;
    float m_drag;
};

class DifferentialDriveCar : public Entity {
public:
    DifferentialDriveCar(Test *test, const b2Vec2& position = b2Vec2_zero, float angle = 0.0f);

    b2Fixture* setup() override;

    void step(Settings& settings) override;

    void setForceLeft(float forceLeft);
    void setForceRight(float forceRight);
    void setMaxLateralImpulse(float maxLateralImpulse);
    void setMaxAngularImpulse(float maxAngularImpulse);
    void setDrag(float drag);

    float getForceLeft() const;
    float getForceRight() const;
    float getMaxLateralImpulse() const;
    float getMaxAngularImpulse() const;
    float getDrag() const;

protected:
    Wheel m_leftWheel;
    Wheel m_rightWheel;
};

class Sensor : public Entity, public b2ContactListener {
public:
    Sensor(Test* test, const b2Vec2& position = b2Vec2_zero);

    b2Fixture* setup(b2FixtureDef& fixtureDef);
    b2Fixture* setup() override;

    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;

    int getContactCount() const;
    bool isActive() const;
private:
    int m_contactCount;
    b2Fixture* m_fixture;
};

#endif
