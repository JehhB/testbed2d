#include <testbed2d/entity.h>
#include <testbed2d/test.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

class Sumo : public Test {
public:
    Sumo() 
        : m_sumoRing(this)
        , m_car1(this, b2Vec2(-0.35f, 0), -90 * DEGTOGRAD)
        , m_car2(this, b2Vec2(0.35f, 0), 90 * DEGTOGRAD)
        , m_sensors(m_car1.getSensors())
    {
        m_world->SetGravity(b2Vec2(0, 0));
        m_sumoRing.setup();

        m_car1.setup();
        m_car2.setup();

        m_maxLateralImpulse = m_car1.getMaxLateralImpulse();
        m_maxAngularImpulse = m_car1.getMaxAngularImpulse();
        m_drag = m_car1.getDrag();
    }

    void Step(Settings &settings) override
	{
        float forceLeft = 0;
        float forceRight = 0;

        if (m_hardRight && !m_hardLeft) {
            forceRight = -0.10f;
            forceLeft = 0.10f;
        } 
        if (m_hardLeft && !m_hardRight) {
            forceRight = 0.10f;
            forceLeft = -0.10f;
        } 
        if (m_forward && !m_reverse) {
            forceRight = 0.10f;
            forceLeft = 0.10f;
        } 
        if (m_reverse && !m_forward) {
            forceRight = -0.10f;
            forceLeft = -0.10f;
        }
        if (m_right && !m_left) {
            forceRight -= 0.05f;
            forceLeft += 0.05f;
        }
        if (m_left && !m_right) {
            forceRight += 0.05f;
            forceLeft -= 0.05f;
        }

        m_car1.setForceLeft(forceLeft);
        m_car1.setForceRight(forceRight);

        m_car2.setForceLeft(m_forceLeft);
        m_car2.setForceRight(m_forceRight);

        m_car1.setDrag(m_drag);
        m_car2.setDrag(m_drag);

        m_car1.setMaxLateralImpulse(m_maxLateralImpulse);
        m_car2.setMaxLateralImpulse(m_maxLateralImpulse);

        m_car1.setMaxAngularImpulse(m_maxAngularImpulse);
        m_car2.setMaxAngularImpulse(m_maxAngularImpulse);

        m_car1.step(settings);
        m_car2.step(settings);
		Test::Step(settings);
	}

    void Keyboard(int key) override {
        if (key == GLFW_KEY_W) {
            m_forward = true;
        }
        else if (key == GLFW_KEY_D) {
			m_right = true;
		}
		else if (key == GLFW_KEY_A) {
			m_left = true;
		}
		else if (key == GLFW_KEY_S) {
			m_reverse = true;
		}
		else if (key == GLFW_KEY_Q) {
			m_hardLeft = true;
		}
		else if (key == GLFW_KEY_E) {
			m_hardRight = true;
        }
    }

    void KeyboardUp(int key) override {
        if (key == GLFW_KEY_W) {
            m_forward = false;
        }
        else if (key == GLFW_KEY_D) {
			m_right = false;
		}
		else if (key == GLFW_KEY_A) {
			m_left = false;
		}
		else if (key == GLFW_KEY_S) {
			m_reverse = false;
		}
		else if (key == GLFW_KEY_Q) {
			m_hardLeft = false;
		}
		else if (key == GLFW_KEY_E) {
			m_hardRight = false;
        }
    }

    void BeginContact(b2Contact* contact) override {
        m_car1.BeginContact(contact);
    }

    void EndContact(b2Contact* contact) override {
        m_car1.EndContact(contact);
    }

    void UpdateUI() override {
        ImGui::Begin("Sumo Configuration");

        ImGui::Text("Floor Settings");
        ImGui::SliderFloat("Max Lateral Impulse", &m_maxLateralImpulse, 0.0f, 5.0f);
        ImGui::SliderFloat("Max Angular Impulse", &m_maxAngularImpulse, 0.0f, 5.0f);
        ImGui::SliderFloat("Drag", &m_drag, 0.0f, 1.0f);

        ImGui::Separator();

        ImGui::Text("Car 2 Settings");
        ImGui::SliderFloat("Force Left", &m_forceLeft, -1.0f, 1.0f);
        ImGui::SliderFloat("Force Right", &m_forceRight, -1.0f, 1.0f);

        ImGui::Separator();

        ImGui::Text("Line sensors");
        for (int i = 0; i < m_sensors.size(); i++) {
			ImGui::Text("Sensor %d: %s", i, m_sensors[i]->isActive() ? "active" : "inactive");
		}

        ImGui::End();
    }

    static Test* Create()
	{
		return new Sumo;
	}
private:
    bool m_forward = false;
    bool m_reverse = false;
    bool m_left = false;
    bool m_right = false;
    bool m_hardLeft = false;
    bool m_hardRight = false;

    float m_maxLateralImpulse;
    float m_maxAngularImpulse;
    float m_drag;

    float m_forceLeft = 0.0f;
    float m_forceRight = 0.0f;

    std::array<Sensor*, 4> m_sensors;

    SumoRing m_sumoRing;
    DifferentialDriveCar m_car1;
    DifferentialDriveCar m_car2;
};

static int testId = RegisterTest("Simulation", "Sumo", Sumo::Create);
