#include <testbed2d/entity.h>

Wheel::Wheel(Test* test, const b2Vec2& position, float angle)
	: Entity(test, b2_dynamicBody, position, angle)
	, m_maxLateralImpulse(1.0f)
	, m_maxAngularImpulse(1.0f)
	, m_drag(0.75f)
	, m_force(0.0f)
{}

b2Fixture* Wheel::setup() {
	b2PolygonShape shape;
	shape.SetAsBox(0.015f, 0.05f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;

	return Entity::setup(fixtureDef);
}

void Wheel::step(Settings &settings) {
	if (!settings.m_pause) {
		b2Vec2 v = m_body->GetLinearVelocity();
		b2Vec2 vN = v;
		vN.Normalize();

		b2Vec2 x = m_body->GetWorldVector(b2Vec2(1, 0));
		b2Vec2 y = m_body->GetWorldVector(b2Vec2(0, 1));
		b2Vec2 lateralVelocity = b2Dot(v, x) * x;
		b2Vec2 lateralImpulse = m_body->GetMass() * -lateralVelocity;
		float angularImpulse = m_body->GetInertia() * -m_body->GetAngularVelocity();

		m_body->ApplyLinearImpulse(m_maxLateralImpulse * lateralImpulse, m_body->GetWorldCenter(), true);
		m_body->ApplyAngularImpulse(m_maxAngularImpulse * angularImpulse, true);
		b2Vec2 force = m_force * y;
		force -= m_drag * m_body->GetMass() / (1 / settings.m_hertz) * v;

		m_body->ApplyForce(force, m_body->GetWorldCenter(), true);
	}
}


void Wheel::setForce(float force) {
	m_force = force;
}

void Wheel::setMaxLateralImpulse(float maxLateralImpulse) {
	m_maxLateralImpulse = maxLateralImpulse;
}

void Wheel::setMaxAngularImpulse(float maxAngularImpulse) {
	m_maxAngularImpulse = maxAngularImpulse;
}

void Wheel::setDrag(float drag) {
	m_drag = drag;
}

float Wheel::getForce() const {
	return m_force;
}

float Wheel::getMaxLateralImpulse() const {
	return m_maxLateralImpulse;
}

float Wheel::getMaxAngularImpulse() const {
	return m_maxAngularImpulse;
}

float Wheel::getDrag() const {
	return m_drag;
}
