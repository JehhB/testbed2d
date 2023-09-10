#include <testbed2d/entity.h>
#include <testbed2d/test.h>

class SensorTest : public Test {
public:
	SensorTest() 
		: box1(this, b2_dynamicBody, b2Vec2(0.2f, 0.3f))
		, box2(this, b2_dynamicBody, b2Vec2(-0.2f, 0.3f))
		, sensor(this)
	{
		m_world->SetGravity(b2Vec2_zero);

		b2PolygonShape shape;
		shape.SetAsBox(0.3f, 0.1f);
		b2FixtureDef fixtureDef;
		fixtureDef.isSensor = true;
		fixtureDef.density = 1.0f;
		fixtureDef.shape = &shape;

		box1.setup(fixtureDef);
		box2.setup(fixtureDef);

		b2CircleShape circle;
		circle.m_radius = 0.1f;
		fixtureDef.shape = &circle;

		sensor.setup();
	}

	void UpdateUI() override {
		g_debugDraw.DrawString(5, m_textLine, "Sensor: %s", sensor.isActive() ? "active" : "inactive");
		m_textLine += 15;

		g_debugDraw.DrawString(5, m_textLine, "Sensor Count: %d", sensor.getContactCount());
		m_textLine += 15;
	}

	static Test* Create() {
		return new SensorTest;
	}

private:
	Entity box1;
	Entity box2;
	Sensor sensor;
};

static int testId = RegisterTest("Simulation", "02 Sensor", SensorTest::Create);
