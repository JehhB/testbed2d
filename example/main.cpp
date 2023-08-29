#include <testbed2d/testbed2d.h>
#include <testbed2d/entity.h>

class Sumo : public Test {
public:
    Sumo() : m_sumoRing(this)
    {
        m_world->SetGravity(b2Vec2(0, 0));
    }


    static Test* Create()
	{
		return new Sumo;
	}
private:
    SumoRing m_sumoRing;
};

int main(int argc, char *argv[]) {
    RegisterTest("Simulation", "Sumo", Sumo::Create);
    return StartTestBed();
}