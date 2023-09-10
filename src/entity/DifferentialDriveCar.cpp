#include <testbed2d/entity.h>

const b2Vec2 DifferentialDriveCar::DEFAULT_LEFT_WHEEL_POSITION(-0.075f, -0.025f);
const b2Vec2 DifferentialDriveCar::DEFAULT_RIGHT_WHEEL_POSITION(0.075f, -0.025f);

const b2Vec2 DifferentialDriveCar::DEFAULT_SENSOR_POSITIONS[4] = {
	b2Vec2(-0.08f, 0.1f),
	b2Vec2(0.08f, 0.1f),
	b2Vec2(0.08f, -0.1f),
	b2Vec2(-0.08f, -0.1f),
};

static Wheel* _setupWheel(DifferentialDriveCar* car, Wheel* wheel, const b2Vec2& position);

DifferentialDriveCar::DifferentialDriveCar(Test* test, const b2Vec2& position, float angle)
	: Entity(test, b2_dynamicBody, position, angle)
	, m_leftWheel(nullptr)
	, m_rightWheel(nullptr)
{
	setDrag(0.5f);
	setMaxLateralImpulse(0.1f);
}

DifferentialDriveCar::~DifferentialDriveCar() {
	for (Sensor* sensor : m_sensors) {
		delete sensor;
	}

	if (m_leftWheel != nullptr) delete m_leftWheel;
	if (m_rightWheel != nullptr) delete m_rightWheel;
}

b2Fixture* DifferentialDriveCar::setup() {
	b2PolygonShape shape;
	shape.SetAsBox(0.08f, 0.1f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;

	return Entity::setup(fixtureDef);
}

void DifferentialDriveCar::setupWheels(const b2Vec2 &leftPosition, const b2Vec2 &rightPosition) {
	if (m_leftWheel != nullptr) delete m_leftWheel;
	if (m_rightWheel != nullptr) delete m_rightWheel;

	setLeftWheel(nullptr, leftPosition);
	setRightWheel(nullptr, rightPosition);

	m_leftWheel->setup();
	m_rightWheel->setup();
}

Wheel* DifferentialDriveCar::setLeftWheel(Wheel *leftWheel, const b2Vec2 &position) {
	Wheel *temp = m_leftWheel;
	m_leftWheel = _setupWheel(this, leftWheel, position);

	return temp;
}

Wheel* DifferentialDriveCar::setRightWheel(Wheel *rightWheel, const b2Vec2 &position) {
	Wheel *temp = m_rightWheel;
	m_rightWheel = _setupWheel(this, rightWheel, position);
	return temp;
}

void DifferentialDriveCar::setupSensors(const b2Vec2 sensorPositions[], int count) {
	for (int i = 0; i < count; ++i) {
		Sensor* sensor = attachSensor(nullptr, sensorPositions[i]);
		sensor->setup();
	}
}

Sensor* DifferentialDriveCar::attachSensor(Sensor* sensor, const b2Vec2 &position) {
	if (sensor == nullptr) {
		sensor = new Sensor(getTest(), m_body->GetWorldPoint(position));
	}

	b2WeldJointDef jointDef;
	jointDef.bodyA = m_body;
	jointDef.collideConnected = false;
	jointDef.referenceAngle = 0;
	jointDef.localAnchorB.SetZero();

	jointDef.bodyB = sensor->getBody();
	jointDef.localAnchorA = position;
	getWorld()->CreateJoint(&jointDef);

	m_sensors.insert(sensor);

	return sensor;
}

void DifferentialDriveCar::removeSensor(Sensor* sensor) {
	m_sensors.erase(sensor);
	delete sensor;
}

void DifferentialDriveCar::step(Settings& settings) {
	if (m_leftWheel != nullptr) m_leftWheel->step(settings);
	if (m_rightWheel != nullptr) m_rightWheel->step(settings);
}

void DifferentialDriveCar::setForceLeft(float forceLeft) {
	if (m_leftWheel != nullptr) m_leftWheel->setForce(forceLeft);
}

void DifferentialDriveCar::setForceRight(float forceRight) {
	if (m_rightWheel != nullptr) m_rightWheel->setForce(forceRight);
}

void DifferentialDriveCar::setDrag(float drag) {
	if (m_leftWheel != nullptr) m_leftWheel->setDrag(drag);
	if (m_rightWheel != nullptr) m_rightWheel->setDrag(drag);
}

void DifferentialDriveCar::setMaxLateralImpulse(float maxLateralImpulse) {
	if (m_leftWheel != nullptr) m_leftWheel->setMaxLateralImpulse(maxLateralImpulse);
	if (m_rightWheel != nullptr) m_rightWheel->setMaxLateralImpulse(maxLateralImpulse);
}

void DifferentialDriveCar::setMaxAngularImpulse(float maxAngularImpulse) {
	if (m_leftWheel != nullptr) m_leftWheel->setMaxAngularImpulse(maxAngularImpulse);
	if (m_rightWheel != nullptr) m_rightWheel->setMaxAngularImpulse(maxAngularImpulse);
}

float DifferentialDriveCar::getForceLeft() const {
	return m_leftWheel != nullptr ? m_leftWheel->getForce() : 0;
}

float DifferentialDriveCar::getForceRight() const {
	return m_leftWheel != nullptr ? m_leftWheel->getForce() : 0;
}

float DifferentialDriveCar::getDrag() const {
	if (m_leftWheel != nullptr) return m_leftWheel->getDrag();
	if (m_rightWheel != nullptr) return m_rightWheel->getDrag();
	return 0;
}

float DifferentialDriveCar::getMaxLateralImpulse() const {
	if (m_leftWheel != nullptr) return m_leftWheel->getMaxLateralImpulse();
	if (m_rightWheel != nullptr) return m_rightWheel->getMaxLateralImpulse();
	return 0;
}

float DifferentialDriveCar::getMaxAngularImpulse() const {
	if (m_leftWheel != nullptr) return m_leftWheel->getMaxAngularImpulse();
	if (m_rightWheel != nullptr) return m_rightWheel->getMaxAngularImpulse();
	return 0;
}

Wheel* DifferentialDriveCar::getLeftWheel() {
	return m_leftWheel;
}

Wheel* DifferentialDriveCar::getRightWheel() {
	return m_rightWheel;
}

std::unordered_set<Sensor*>* DifferentialDriveCar::getSensors() {
	return &m_sensors;
}

static Wheel* _setupWheel(DifferentialDriveCar *car, Wheel *wheel, const b2Vec2 &position) {
	b2Body* carBody = car->getBody();

	if (wheel == nullptr) {
		wheel = new Wheel(car->getTest(), carBody->GetWorldPoint(position), carBody->GetAngle());
	}

	b2WeldJointDef jointDef;
	jointDef.bodyA = carBody;
	jointDef.collideConnected = false;
	jointDef.referenceAngle = 0;
	jointDef.localAnchorB.SetZero();

	jointDef.bodyB = wheel->getBody();
	jointDef.localAnchorA = position;
	car->getWorld()->CreateJoint(&jointDef);

	return wheel;
}
