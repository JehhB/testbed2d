#ifndef TESTBED2D_ENTITY_H
#define TESTBED2D_ENTITY_H

#define DEGTOGRAD b2_pi / 180.0f

#include <testbed2d/test.h>
#include <testbed2d/settings.h>
#include <box2d/box2d.h>
#include <unordered_set>

class Test;

class Entity : public b2ContactListener {
public:
    Entity(Test* test, b2Body* body);
    Entity(Test* test, b2BodyDef& bodyDef);
    Entity(Test* test, const b2BodyType& type, const b2Vec2& position = b2Vec2_zero, float angle = 0.0f);
    virtual ~Entity();

    virtual b2Fixture* setup(b2FixtureDef& fixtureDef);
    virtual b2Fixture* setup();

    virtual void step(Settings& setting);

    virtual void BeginContact(b2Contact* contact) override { B2_NOT_USED(contact); }
    virtual void EndContact(b2Contact* contact) override { B2_NOT_USED(contact); }
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override {
        B2_NOT_USED(contact);
        B2_NOT_USED(oldManifold);
    }
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override {
        B2_NOT_USED(contact);
        B2_NOT_USED(impulse);
    }

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

class Sensor : public Entity {
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

class DifferentialDriveCar : public Entity {
public:
	static const b2Vec2 DEFAULT_LEFT_WHEEL_POSITION;
	static const b2Vec2 DEFAULT_RIGHT_WHEEL_POSITION;
    static const b2Vec2 DEFAULT_SENSOR_POSITIONS[4];

    DifferentialDriveCar(Test *test, const b2Vec2& position = b2Vec2_zero, float angle = 0.0f);
    ~DifferentialDriveCar() override;

    b2Fixture* setup() override;
    void setupWheels(const b2Vec2 &leftPosition = DEFAULT_LEFT_WHEEL_POSITION, const b2Vec2 &rightWheelPosition = DEFAULT_RIGHT_WHEEL_POSITION);
    Wheel* setLeftWheel(Wheel *leftWheel, const b2Vec2 &postion);
    Wheel* setRightWheel(Wheel *rightWheel, const b2Vec2 &position);

    void setupSensors(const b2Vec2 sensorPositions[] = DEFAULT_SENSOR_POSITIONS, int count = 4);
    Sensor* attachSensor(Sensor *sensor = nullptr, const b2Vec2 &positions = b2Vec2_zero);
    void removeSensor(Sensor *sensor);

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

    Wheel* getLeftWheel();
    Wheel* getRightWheel();
    std::unordered_set<Sensor*>* getSensors();
protected:
    Wheel* m_leftWheel;
    Wheel* m_rightWheel;

    std::unordered_set<Sensor*> m_sensors;
};

#endif
