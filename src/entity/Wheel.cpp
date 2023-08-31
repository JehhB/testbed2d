#include <testbed2d/entity.h>

Wheel::Wheel(Test* test) {
	m_test = test;
	m_maxLateralImpulse = 0.1f;
	m_drag = 0.5f;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	m_body = m_test->getWorld()->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(0.015f, 0.05f);
	m_body->CreateFixture(&shape, 1.0);
}

void Wheel::step(Settings &settings, float forceMagnitude) {
	if (!settings.m_pause) {
		b2Vec2 v = m_body->GetLinearVelocity();
		b2Vec2 vN = v;
		vN.Normalize();

		b2Vec2 x = m_body->GetWorldVector(b2Vec2(1, 0));
		b2Vec2 y = m_body->GetWorldVector(b2Vec2(0, 1));
		b2Vec2 lateralVelocity = b2Dot(v, x) * x;
		b2Vec2 lateralImpulse = m_body->GetMass() * -lateralVelocity;
		float angularImpulse = 0.1f * m_body->GetInertia() * -m_body->GetAngularVelocity();

		m_body->ApplyLinearImpulse(m_maxLateralImpulse * lateralImpulse, m_body->GetWorldCenter(), true);
		m_body->ApplyAngularImpulse(angularImpulse, true);
		b2Vec2 force = forceMagnitude * y;
		force -= m_drag * m_body->GetMass() / (1 / settings.m_hertz) * v;

		g_debugDraw.DrawString(m_body->GetWorldCenter(), "%f %f", m_body->GetLinearVelocity().x, lateralImpulse.x);
		m_body->ApplyForce(force, m_body->GetWorldCenter(), true);
	}
}