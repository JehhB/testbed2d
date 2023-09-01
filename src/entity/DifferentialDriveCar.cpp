#include <testbed2d/entity.h>

DifferentialDriveCar::DifferentialDriveCar(Test* test) :
	m_leftWheel(test), m_rightWheel(test) 
{
	m_leftWheel.setup();
	m_rightWheel.setup();

	m_test = test;
	setDrag(0.5f);
	setMaxLateralImpulse(0.1f);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	m_body = m_test->getWorld()->CreateBody(&bodyDef); 

	b2PolygonShape shape;
	shape.SetAsBox(0.08f, 0.1f);
	m_body->CreateFixture(&shape, 1.0f);

	b2WeldJointDef jointDef;
	jointDef.bodyA = m_body;
	jointDef.collideConnected = false;
	jointDef.referenceAngle = 0;
	jointDef.localAnchorB.SetZero();

	jointDef.bodyB = m_leftWheel.getBody();
	jointDef.localAnchorA.Set(-0.075f, -0.025f);
	m_test->getWorld()->CreateJoint(&jointDef);

	jointDef.bodyB = m_rightWheel.getBody();
	jointDef.localAnchorA.Set(0.075f, -0.025f);
	m_test->getWorld()->CreateJoint(&jointDef);
}

float DifferentialDriveCar::getDrag() const {
	return m_drag;
}

float DifferentialDriveCar::getMaxLateralImpulse() const {
	return m_maxLateralImpulse;
}

void DifferentialDriveCar::setDrag(float drag) {
	m_leftWheel.setDrag(drag);
	m_rightWheel.setDrag(drag);
	m_drag = drag;
}

void DifferentialDriveCar::setMaxLateralImpulse(float maxLateralImpulse) {
	m_leftWheel.setMaxLateralImpulse(maxLateralImpulse);
	m_rightWheel.setMaxLateralImpulse(maxLateralImpulse);
	m_maxLateralImpulse = maxLateralImpulse;
}

void DifferentialDriveCar::step(Settings& settings, float forceLeft, float forceRight) {
	m_leftWheel.setForce(forceLeft);
	m_rightWheel.setForce(forceRight);

	m_leftWheel.step(settings);
	m_rightWheel.step(settings);
}
