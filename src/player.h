#ifndef __PLAYER_AGENT__H
#define __PLAYER_AGENT__H 

#include "enviro.h"

using namespace enviro;

class PlayerController : public Process, public AgentInterface {

    public:
    PlayerController() : Process(), AgentInterface() {}

    void init();
    void start();
    void update();
    void stop();

    double mass();

    bool grav;
    double fx, fy;
    double const magnitude = 200;
    int tick;
    double _mass;
    int ht;
    double vx;
    double vy;


    private:
    void check_pos();
    void check_hits();
    void broadcast_pos();

};

class Player : public Agent {
    public:
    Player(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    
    private:
    PlayerController c;
};

DECLARE_INTERFACE(Player)

#endif