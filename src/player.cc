#include <iostream>
#include "player.h"
#include "styles.h"

using namespace enviro;

// Put your implementations here

void PlayerController::init() {
    _mass = 300;
    watch("keydown", [&](Event &e) {
        if ( e.value()["client_id"] == get_client_id() ) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == "w" ) {
                fy = -magnitude;              
            } else if ( k == "s" ) {
                fy = magnitude;  
            } else if ( k == "a" ) {
                fx = -magnitude;
            } else if ( k == "d" ) {
                fx = magnitude;
            } 
        }
    });

    watch("keyup", [&](Event &e) {
        if ( e.value()["client_id"] == get_client_id() ) {            
            auto k = e.value()["key"].get<std::string>();
            if ( k == " " ) {
                grav = false;
            } else if ( k == "w" || k == "s" ) {
                fy = 0;               
            } else if ( k == "a" || k == "d") {
                fx = 0;
            } 
        }
    });

    notice_collisions_with("Planet", [&](Event& e) {
        _mass += 60;
        omni_damp_movement();
    });

    notice_collisions_with("Bullet", [&](Event& e) {
        if (ht < 5) {
            ht++;
        }
    });
}

void PlayerController::start() { 
    ht = 0;
    broadcast_pos(); 
}

void PlayerController::update() {
    broadcast_pos();
    check_pos();
    check_hits();
    
    omni_apply_force(fx, fy);
    label(std::to_string((int) x()) + ", " + std::to_string((int)y()),20,20);

    std::string radius = std::to_string((int) pow(mass(), 0.5));
    // decorate("<circle x='0' y='0' r=' " + radius  + "' style='fill: black'></circle>");
    // std::string str = "<circle x='-5' y='5' r='" + radius + "' style='fill: blue'></circle>";
    std::string c = "<circle style='fill:#285680' cx='29' cy='29' r='29' id='circle3804' />";
    std::string str = "<path style='fill:#24ae5f' d='m 29,0 c -4.03,0 -7.866,0.823 -11.353,2.308 -0.159,0.949 -0.952,2.57 -0.928,3.087 0.112,0.022 7.373,-7.4 6.472,-2.39 -0.581,3.225 -6.516,3.206 -6.261,6.453 6.236,2.445 8.411,-4.642 13.708,-4.613 1.767,0.01 6.292,-2.784 7.155,-2.215 3.496,2.303 -0.799,10.467 -3.474,7.75 -2.572,-2.572 -6.242,0.901 -6.077,4.912 1.337,0.06 1.908,-3.796 3.11,-2.51 1.324,1.417 0.846,4.27 -0.986,4.925 -1.844,0.659 -9.077,-4.89 -7.3,-0.684 1.954,4.668 -5.854,8.275 2.028,6.393 3.716,-0.891 2.481,1.937 4.234,3.286 2.088,1.603 1.164,-2.214 2.686,-1.633 2.215,0.857 -0.381,3.065 3.088,1.462 4.069,-1.856 2.54,1.038 3.786,2.93 2.336,3.532 8.077,6.922 11.086,2.254 0.709,-1.101 0.254,-9.807 4.72,-3.967 2.836,3.71 1.863,-4.383 2.247,-6.509 C 53.547,8.993 42.327,0 29,0 Z' id='path3806' />";
    std::string circle = "<g transform='matrix(0.26458333,0,0,0.26458333,64.142563,67.077083)'>" + c + str + "</g>" + "<circle x='-5' y='5' r='" + radius + "' style='fill: blue'></circle>";
    // std::string circle = "<g transform='matrix(0,0," + radius + ",0,0," + radius + ")'>" + c + str + "</g>";

    decorate(c);
    decorate(circle);
}


void PlayerController::stop() {}

void PlayerController::check_pos() {
    double newX = x();
    double newY = y();
    if (x() > 1000 ) {
        newX = x()-2000;
    } else if (x() < -1000) {
        newX = x()+2000;
    }
    if (y() > 600 ) {
        newY = y()-1200;
    } else if (y() < -600) {
        newY = y()+1200;
    }
    
    if (newX != x() || newY != y()) {
        teleport(newX, newY, 0);
    }
}

void PlayerController::check_hits() {
    if (ht >= 5) {
        _mass -= 180;
        std::cout << _mass << "\n";
        if (_mass < 300) {
           _mass = 300;
            
        } else {
            for ( double theta=0; theta < 2 * M_PI; theta += M_PI / 2) {
                double dx = rand()% 1 > 0.5 ? rand() % 30 + 70 : -rand() % 30 - 70;
                double dy = rand()% 1 > 0.5 ? rand() % 30 + 70 : -rand() % 30 - 70;
                Agent& frag = add_agent("Planet", x() + dx, y() + dy, theta, PLANET_STYLE);
                frag.omni_apply_force(
                    5000*cos(theta+M_PI/8) + 10000, 
                    5000*sin(theta+M_PI/8) + 20000
                );
            }
        }
         
        ht = 0;
    }
    std::cout << ht << "\n"; 
}

void PlayerController::broadcast_pos() {
    if (tick++ == 10) {
        emit(Event("PLAYER_INFO", {
            {"id", id()},
            {"x", x()},
            {"y", y()},
            {"mass", mass()}   
        }));
        tick = 0;
    }
}

double PlayerController::mass() {
    return _mass;
}
