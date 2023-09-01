#include <testbed2d/testbed2d.h>
#include <testbed2d/entity.h>
#include <testbed2d/settings.h>
#include <imgui.h>

class Sumo : public Test {
public:
    Sumo() 
        : m_sumoRing(this)
        , m_car1(this, b2Vec2(-0.35f, 0), -90 * DEGTOGRAD)
        , m_car2(this, b2Vec2(0.35f, 0), 90 * DEGTOGRAD)
    {
        m_world->SetGravity(b2Vec2(0, 0));
        m_sumoRing.setup();

        m_car1.setup();
        m_car2.setup();

        m_car2.setForceLeft(0.2f);
        m_car2.setForceRight(-0.2f);
    }

    void Step(Settings &settings) override
	{
        m_car1.setForceLeft(forceLeft);
        m_car1.setForceRight(forceRight);


        m_car1.step(settings);
        m_car2.step(settings);
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
    DifferentialDriveCar m_car1;
    DifferentialDriveCar m_car2;
};

int main(int argc, char *argv[]) {
    RegisterTest("Simulation", "Sumo", Sumo::Create);
    return StartTestBed();
}