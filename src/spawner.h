#ifndef __SPAWNER_AGENT__H
#define __SPAWNER_AGENT__H 

#include <iostream>
#include "enviro.h"

using namespace enviro;

class SpawnerController : public Process, public AgentInterface {

    public:
    SpawnerController() : Process(), AgentInterface() {}

    void init() {
        watch("connection", [&](Event& e) {
            if ( ! e.value()["client_id"].is_null() ) {
                std::cout << "Connection from " << e.value() << "\n";
                Agent& a = add_agent("Player", 0, y, 0, PLAYER_STYLE);
                a.set_client_id(e.value()["client_id"]);
                y += 50;
            }
        });
    }
    
    void start() {
        counter = 0;
    }

    void update() {
        if (counter++ == 20) {
            Agent& planet = add_agent("Planet", 
                rand() % 2400 - 1200.0,
                rand() % 1800 - 900.0,
                0,
                PLANET_STYLE
            );
            counter = 0;
        }
    }
    void stop() {}

    
    
    int counter;
    double y = -150;
    
    const json PLAYER_STYLE = {
            {"fill", "lightgreen"},
            {"stroke", "none"}
        };

    const json PLANET_STYLE = {
            {"fill", "black"},
            {"stroke", "#888"},
            {"strokeWidth", "5px"},
            {"strokeOpacity", "0.25"}
        };
};

class Spawner : public Agent {
    public:
    Spawner(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    SpawnerController c;
};

DECLARE_INTERFACE(Spawner)

#endif