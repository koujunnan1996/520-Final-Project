#ifndef __TURRET_AGENT__H
#define __TURRET_AGENT__H 

#include "enviro.h"
#include "styles.h"

namespace {

    using namespace enviro;
    //define the two state: Shooting and Rotatiing
    class Shooting : public State, public AgentInterface {
        public:
        void entry(const Event& e) {
            counter = 0;
            
        }
        void during() { 
            Agent& bullet = add_agent("Bullet", 
                    x() + 17*cos(angle()), 
                    y() + 17*sin(angle()), 
                    angle(), 
                    BULLET_STYLE);    
                    bullet.apply_force(5,0);
            counter ++;
            if (counter >= 10) {
                emit(Event("search"));
            }
        }
        void exit(const Event& e) {}
        
        double counter;
    };

    class Rotating : public State, public AgentInterface {
        public:
        void entry(const Event& e) {
            double dx(goalX - x()), dy(goalY - y());
            desired_angle = atan(fabs(dy) / fabs(dx));
            if (goalY < 0) {
                desired_angle = -desired_angle;
            }
        }
        void during() { 
            if (fabs(desired_angle - angle()) < 0.005) {
                angle_v = 0;
                emit(Event("found"));
            } else {
                angle_v = sin(desired_angle - angle());
            }
            track_velocity(0, angle_v);
    
        }

        void setGoal(double px, double py) {
            goalX = px;
            goalY = py;
        }
        void exit(const Event& e) {}
        double desired_angle;
        double angle_v;
        double goalX;
        double goalY;
    };

    class Idling : public State, public AgentInterface {
        public:
        void entry(const Event& e) {}
        void during() {}
        void exit(const Event& e) {}
    };
    
    class TurretController : public StateMachine, public AgentInterface {
        public:
        TurretController() : StateMachine() {

            set_initial(rotating);
                                                        
            add_transition("search", shooting, rotating);
            add_transition("found", rotating, shooting);

        }

        void init() {
            watch("PLAYER_INFO", [&](Event& e) {
                PLAYER_X = e.value()["x"];
                PLAYER_Y = e.value()["y"];
            });
            StateMachine::init();
        }

        void update() {
            rotating.setGoal(PLAYER_X, PLAYER_Y);
            StateMachine::update();
        }

        Shooting shooting;
        Rotating rotating;

        double PLAYER_X;
        double PLAYER_Y;
    };
    // class TurretController : public Process, public AgentInterface {
    //     public:
    //     TurretController() : Process(), AgentInterface() {}

    //     void init() {
    //         watch("PLAYER_INFO", [&](Event& e) {
    //             PLAYER_ID = e.value()["id"];
    //         });  
    //     }
    //     void start() { counter = 0; }
    //     void update() {
    //         if (counter == 20) {
    //             Agent& bullet = add_agent("Bullet", 
    //                 x() + 17*cos(angle()), 
    //                 y() + 17*sin(angle()), 
    //                 angle(), 
    //                 BULLET_STYLE);    
    //                 bullet.apply_force(5,0);
    //         }
    //         if (agent_exists(PLAYER_ID)) {        
    //             Agent& player = find_agent(PLAYER_ID);
    //             double dx(player.x() - x()), dy(player.y() - y());
    //             desired_angle = atan(fabs(dy) / fabs(dx));
    //             if (player.y() < 0) {
    //                 desired_angle = -desired_angle;
    //             }
                
                
    //             std::cout << player.y() << "desired_heading \n";
    //             std::cout << desired_angle << "desired_angle \n";
    //             std::cout << angle() << "angle \n";

    //             double temp;
    //             if (counter++ == 60) {
    //                 temp = sin(desired_angle - angle());
    //                 counter = 0;
    //             }
                
    //             std::cout << temp << "\n";
    //             track_velocity(0, temp);

    //         } else {
    //             track_velocity(0, 0);
    //         }
    //     }
    //     void stop() {}

    //     int counter;
    //     double desired_angle;
    //     int PLAYER_ID;
    //     const json BULLET_STYLE = { 
    //                {"fill", "green"}, 
    //                {"stroke", "#888"}, 
    //                {"strokeWidth", "5px"},
    //                {"strokeOpacity", "0.25"}
    //            };
    // };

    class Turret : public Agent {
       
        public:
        Turret(json spec, World& world) : Agent(spec, world) {
            add_process(c);
        }   
        
        TurretController c;
    
    };

    DECLARE_INTERFACE(Turret)

}

#endif