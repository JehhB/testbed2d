#include <testbed2d/entity.h>

static b2BodyDef createBodyDef(const b2BodyType &bodyType, const b2Vec2 &position, const float angle) {
	b2BodyDef bodydef;
	bodydef.position = position;
	bodydef.angle = angle;
	bodydef.type = bodyType;
	return bodydef;
}

Entity::Entity(Test* test, b2Body* body) 
	: m_body(body) 
	, m_test(test)
{
	m_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

Entity::Entity(Test* test, b2BodyDef& bodydef) 
	: m_test(test)
	, m_body(test->getWorld()->CreateBody(&bodydef)) {};

Entity::Entity(Test* test, const b2BodyType& type, const b2Vec2& position, float angle)
	: m_test(test)
	, m_body(test->getWorld()->CreateBody(&createBodyDef(type, position, angle))) {};

b2Fixture* Entity::setup(b2FixtureDef& fixtureDef) {
	 return m_body->CreateFixture(&fixtureDef);
}

b2Fixture* Entity::setup() {
	return nullptr;
}

void Entity::step(Settings& settings) {
}

b2Body* Entity::getBody() const {
	return m_body;
}

b2World* Entity::getWorld() const {
	return m_body->GetWorld();
}

Test* Entity::getTest() const {
	return m_test;
}
