#ifndef __PLANET_AGENT__H
#define __PLANET_AGENT__H 

#include "enviro.h"

using namespace enviro;

class PlanetController : public Process, public AgentInterface {

    public:
    PlanetController() : Process(), AgentInterface() {}

    void init();
    void start();
    void update();
    void stop();

    double mass();
    double Gforce(double m1, double m2, double rsq);

    int PLAYER_ID;
    double PLAYER_MASS;

    const double PLANET_MASS = 600;
    int counter;

    
};

class Planet : public Agent {
    public:
    Planet(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    PlanetController c;
};



DECLARE_INTERFACE(Planet)

#endif