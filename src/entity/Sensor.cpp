#include <testbed2d/entity.h>

static bool isSensors(b2Contact *contact, b2Fixture *sensor) {
	return contact->GetFixtureA() == sensor && contact->GetFixtureB()->IsSensor() 
		|| contact->GetFixtureB() == sensor && contact->GetFixtureA()->IsSensor();
}

Sensor::Sensor(Test* test, const b2Vec2 &position) 
	: Entity(test, b2_dynamicBody, position, 0.0f)
	, m_contactCount(0)
	, m_fixture(0)
{}

b2Fixture* Sensor::setup(b2FixtureDef& fixtureDef) {
	m_fixture = Entity::setup(fixtureDef);
	return m_fixture;
}

b2Fixture* Sensor::setup() {
	b2CircleShape circleShape;
	circleShape.m_radius = 0.01f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 0.1f;
	fixtureDef.isSensor = true;
	return setup(fixtureDef);
}

void Sensor::BeginContact(b2Contact *contact) {
	if (contact->IsTouching() && isSensors(contact, m_fixture)) {
		m_contactCount++;
	}
}

void Sensor::EndContact(b2Contact* contact) {
	if (!contact->IsTouching() && isSensors(contact, m_fixture)) {
		m_contactCount--;
	}
}

int Sensor::getContactCount() const {
	return m_contactCount;
}

bool Sensor::isActive() const {
	return m_contactCount > 0;
}
