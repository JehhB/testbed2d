#include <testbed2d/testbed2d.h>
#include <testbed2d/entity.h>
#include <testbed2d/settings.h>
#include <imgui.h>

class Sumo : public Test {
public:
    Sumo() 
        : m_sumoRing(this)
        , m_wheel(this)
    {
        m_world->SetGravity(b2Vec2(0, 0));
        m_wheel.m_body->SetLinearVelocity(b2Vec2(-0.5f, 1.0f));
    }

    void Step(Settings &settings) override
	{
        ImGui::Begin("Wheel Settings"); 
        ImGui::SliderFloat("Drag", &m_drag, 0.0f, 1.0f);
        ImGui::SliderFloat("Max Lateral Impulse", &m_maxLateralImpulse, 0.0f, 1.0f);
        ImGui::End();

        m_wheel.m_maxLateralImpulse = m_maxLateralImpulse;
        m_wheel.m_drag = m_drag;

        m_wheel.step(settings, 0.0f);
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
    Wheel m_wheel;
};

int main(int argc, char *argv[]) {
    RegisterTest("Simulation", "Sumo", Sumo::Create);
    return StartTestBed();
}