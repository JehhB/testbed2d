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
        m_sumoRing.setup();
    }

    void Step(Settings &settings) override
	{
		Test::Step(settings);
	}

    void UpdateUI() override {
        ImGui::Begin("Car");
        ImGui::SliderFloat("Left", &forceLeft, -10.0f, 10.0f);
        ImGui::SliderFloat("Right", &forceRight, -10.0f, 10.0f);
        ImGui::End();
    }

    static Test* Create()
	{
		return new Sumo;
	}
private:
    float forceLeft = 0.0f;
    float forceRight = 0.0f;

    SumoRing m_sumoRing;
    DifferentialDriveCar m_car;
};

int main(int argc, char *argv[]) {
    RegisterTest("Simulation", "Sumo", Sumo::Create);
    return StartTestBed();
}