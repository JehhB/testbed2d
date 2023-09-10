#include <testbed2d/entity.h>

bool SensorCallback::shouldActivate(b2Fixture* fixture) {
	Entity* entity = reinterpret_cast<Entity*>(fixture->GetUserData().pointer);
	Sensor* sensor = dynamic_cast<Sensor*>(entity);

	return fixture->IsSensor() && sensor == nullptr;
}


static bool _shouldActivate(b2Contact *contact, b2Body *sensor, SensorCallback *callback) {
	static SensorCallback defaultCallback;

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	b2Body* bodyA = fixtureA->GetBody();
	b2Body* bodyB = fixtureB->GetBody();

	if (callback == nullptr) {
		callback = &defaultCallback;
	}

	return bodyA == sensor && callback->shouldActivate(fixtureB) 
		|| bodyB == sensor && callback->shouldActivate(fixtureA);
}

Sensor::Sensor(Test* test, const b2Vec2 &position) 
	: Entity(test, b2_dynamicBody, position, 0.0f)
	, m_contactCount(0)
	, m_sensorCallback(nullptr)
{}

b2Fixture* Sensor::setup() {
	b2CircleShape circleShape;
	circleShape.m_radius = 0.01f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 0.1f;
	fixtureDef.isSensor = true;
	return Entity::setup(fixtureDef);
}

void Sensor::BeginContact(b2Contact *contact) {
	if (contact->IsTouching() && _shouldActivate(contact, m_body, m_sensorCallback)) {
		m_contactCount++;
	}
}

void Sensor::EndContact(b2Contact* contact) {
	if (!contact->IsTouching() && _shouldActivate(contact, m_body, m_sensorCallback)) {
		m_contactCount--;
	}
}

int Sensor::getContactCount() const {
	return m_contactCount;
}

bool Sensor::isActive() const {
	return m_contactCount > 0;
}

void Sensor::setSensorCallback(SensorCallback* sensorCallback) {
	m_sensorCallback = sensorCallback;
}
