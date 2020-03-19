#ifndef __VIRUS_STYLES__H
#define __VIRUS_STYLES__H

#include "enviro.h"

using namespace enviro;

const json BULLET_STYLE = { 
                   {"fill", "green"}, 
                   {"stroke", "#888"}, 
                   {"strokeWidth", "5px"},
                   {"strokeOpacity", "0.25"}
               },
            PLANET_STYLE = {
                {"fill", "red"}, 
                {"stroke", "black"}, 
                {"strokeWidth", "5px"},
                {"strokeOpacity", "0.25"}
            };



#endif