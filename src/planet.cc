#include <iostream>
#include "planet.h"

using namespace enviro;

// Put your implementations here

static const double G = 6.67408;

void PlanetController::init() {
    watch("PLAYER_INFO", [&](Event &e) {
        PLAYER_ID = e.value()["id"];
        PLAYER_MASS = e.value()["mass"];
    });
    notice_collisions_with("Player", [&](Event &e) {
        remove_agent(id());
    });
    counter = 0;

}

void PlanetController::start() {
    omni_apply_force(rand() % 400 - 800, rand() % 400 - 800);
}

void PlanetController::update() {
    
    if (agent_exists(PLAYER_ID)) {
        Agent& player = find_agent(PLAYER_ID);

        double dx(player.x() - x()), dy(player.y() - y());
        int Gf = Gforce(PLAYER_MASS, mass(), pow(dx, 2) + pow(dy, 2));

        double agl = atan(fabs(dy) / fabs(dx));
        double fx = dx > 0 ? Gf * cos(agl) : Gf * cos(agl) * -1;
        double fy = dy > 0 ? Gf * sin(agl) : Gf * sin(agl) * -1;
        omni_apply_force(fx, fy);
    }

    if (counter++ >= 600 && (x() < -1000 || x() > 1000 || y()> 700 || y() < -700 )) {
        remove_agent(id());
    }
}

void PlanetController::stop() {}

double PlanetController::Gforce(double m1, double m2, double rsq) {
    double Gf = G * m1 * m2 / rsq;
    return Gf;
}

double PlanetController::mass() {
    return PLANET_MASS;
}