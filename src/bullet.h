#ifndef __BULLET_AGENT__H
#define __BULLET_AGENT__H 

#include "enviro.h"

using namespace enviro;

class BulletController : public Process, public AgentInterface {

    public:
    BulletController() : Process(), AgentInterface(), counter(0) {}

    void init() {
        //check wether collision with planet,if there is collisions, remove it
        notice_collisions_with("Planet", [&](Event &e) {
            remove_agent(e.value()["id"]);
            remove_agent(id());
        });            
    }
    void start() {}
    void update() {
        if ( counter++ > 50 ) {
            remove_agent(id());
        }
    }
    void stop() {}

    double counter;

};

class Bullet : public Agent {
    public:
    Bullet(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    BulletController c;
};

DECLARE_INTERFACE(Bullet)

#endif