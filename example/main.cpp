#include <testbed2d/testbed2d.h>
#include <testbed2d/entity.h>
#include <testbed2d/settings.h>
#include <imgui.h>

class Sumo : public Test {
public:
    Sumo() 
        : m_sumoRing(this)
        , m_car(this)
    {
        m_world->SetGravity(b2Vec2(0, 0));
    }

    void Step(Settings &settings) override
	{
		Test::Step(settings);
	}

    static Test* Create()
	{
		return new Sumo;
	}
private:
    float m_drag = 0.0f;
    float m_maxLateralImpulse = 0.1f;

    SumoRing m_sumoRing;
    DifferentialDriveCar m_car;
};

int main(int argc, char *argv[]) {
    RegisterTest("Simulation", "Sumo", Sumo::Create);
    return StartTestBed();
}