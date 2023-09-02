#include <testbed2d/entity.h>

static const b2Vec2 LEFT_WHEEL_POSITION(-0.075f, -0.025f);
static const b2Vec2 RIGHT_WHEEL_POSITION(0.075f, -0.025f);
static const b2Vec2 SENSOR_POSITIONS[4] = {
	b2Vec2(-0.08f, 0.1f),
	b2Vec2(0.08f, 0.1f),
	b2Vec2(0.08f, -0.1f),
	b2Vec2(-0.08f, -0.1f),
};

DifferentialDriveCar::DifferentialDriveCar(Test* test, const b2Vec2& position, float angle)
	: Entity(test, b2_dynamicBody, position, angle)
	, m_leftWheel(test, m_body->GetWorldPoint(LEFT_WHEEL_POSITION), angle)
	, m_rightWheel(test, m_body->GetWorldPoint(RIGHT_WHEEL_POSITION), angle)
	, m_sensors{
		Sensor(test, m_body->GetWorldPoint(SENSOR_POSITIONS[0])),
		Sensor(test, m_body->GetWorldPoint(SENSOR_POSITIONS[1])),
		Sensor(test, m_body->GetWorldPoint(SENSOR_POSITIONS[2])),
		Sensor(test, m_body->GetWorldPoint(SENSOR_POSITIONS[3])),
	}
{
	setDrag(0.5f);
	setMaxLateralImpulse(0.1f);
}

b2Fixture* DifferentialDriveCar::setup() {
	m_leftWheel.setup();
	m_rightWheel.setup();

	b2PolygonShape shape;
	shape.SetAsBox(0.08f, 0.1f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;

	b2WeldJointDef jointDef;
	jointDef.bodyA = m_body;
	jointDef.collideConnected = false;
	jointDef.referenceAngle = 0;
	jointDef.localAnchorB.SetZero();

	jointDef.bodyB = m_leftWheel.getBody();
	jointDef.localAnchorA = LEFT_WHEEL_POSITION;
	getWorld()->CreateJoint(&jointDef);

	jointDef.bodyB = m_rightWheel.getBody();
	jointDef.localAnchorA = RIGHT_WHEEL_POSITION;
	getWorld()->CreateJoint(&jointDef);

	for (int i = 0; i < 4; ++i) {
		m_sensors[i].setup();

		jointDef.bodyB = m_sensors[i].getBody();
		jointDef.localAnchorA = SENSOR_POSITIONS[i];
		getWorld()->CreateJoint(&jointDef);
	}

	return Entity::setup(fixtureDef);
}

void DifferentialDriveCar::step(Settings& settings) {
	m_leftWheel.step(settings);
	m_rightWheel.step(settings);
}

void DifferentialDriveCar::setForceLeft(float forceLeft) {
	m_leftWheel.setForce(forceLeft);
}

void DifferentialDriveCar::setForceRight(float forceRight) {
	m_rightWheel.setForce(forceRight);
}

void DifferentialDriveCar::setDrag(float drag) {
	m_leftWheel.setDrag(drag);
	m_rightWheel.setDrag(drag);
}

void DifferentialDriveCar::setMaxLateralImpulse(float maxLateralImpulse) {
	m_leftWheel.setMaxLateralImpulse(maxLateralImpulse);
	m_rightWheel.setMaxLateralImpulse(maxLateralImpulse);
}

void DifferentialDriveCar::setMaxAngularImpulse(float maxAngularImpulse) {
	m_leftWheel.setMaxAngularImpulse(maxAngularImpulse);
	m_rightWheel.setMaxAngularImpulse(maxAngularImpulse);
}

float DifferentialDriveCar::getForceLeft() const {
	return m_leftWheel.getForce();
}

float DifferentialDriveCar::getForceRight() const {
	return m_rightWheel.getForce();
}

float DifferentialDriveCar::getDrag() const {
	return m_leftWheel.getDrag();
}

float DifferentialDriveCar::getMaxLateralImpulse() const {
	return m_leftWheel.getMaxAngularImpulse();
}

float DifferentialDriveCar::getMaxAngularImpulse() const {
	return m_leftWheel.getMaxAngularImpulse();
}

void DifferentialDriveCar::BeginContact(b2Contact* contact) {
	for(int i = 0; i < 4; ++i) {
		m_sensors[i].BeginContact(contact);
	}
}

void DifferentialDriveCar::EndContact(b2Contact* contact) {
	for(int i = 0; i < 4; ++i) {
		m_sensors[i].EndContact(contact);
	}
}

std::array<Wheel*, 2> DifferentialDriveCar::getWheels() {
	return {&m_leftWheel, &m_rightWheel};
}

std::array<Sensor*, 4> DifferentialDriveCar::getSensors() {
	return {
		m_sensors + 0,
		m_sensors + 1,
		m_sensors + 2,
		m_sensors + 3,
	};
}
