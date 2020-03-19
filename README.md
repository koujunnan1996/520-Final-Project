EEP-520 Final Projects
===

Project Name: Planet Gravitational Field Simulator    
---
Goal:
---
Develop a engaging and creative game through the "Enviro" enviroment which the theme is planetary gravitational field.

Description:
---
This game simulates the gravitational field of a planet in the universe. When a planet has a large mass, it will have a large gravitational field. It will devour a planet with a small mass near it. There is a cosmic turret in the universe. It will automaticallly aim at the massive planet and issue a strike command. When the planet reaches a certain level and is subject to a series of blows, the planet will split.

 

CHALLENGES
===

- ***1***: The original idea of implementing the gravity field was to let the object controlled by the player be the center of the gravitational field to attract and devour the surrounding small "planets". However, it will appear during the implementation process, so instead, the surrounding objects move toward the object controlled by the player. To achieve the same effect.

- ***2***: In the process of designing and designing the turret to point to a massive planet, the process machine was initially used to aim at the object. However, the process machine was found to be very unstable, and sometimes a segmentation fault occurred. Therefore, a state machine is used instead, so that processes do not affect each other. First, a search is performed, and then a hit instruction is executed, and different states run independently of each other. Program runs stably

- ***3***: At the same time, during the calculation of the rotation angle, there will be a small change in the angle, resulting in no change in the angular velocity. The solution is to calculate the appropriate quantitative parameters to modify the angular velocity by printing a lot of results

How to install and run the code
===
To start a Docker container with ENVIRO pre-loaded into it, do:

```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.6 bash
```

If you do not have the enviro image, the machine will help you download this image,
then, you need clone and pull the game from the github repository to your local computer 
then you need to mout this project to the enviro image like above.

 ```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.6 bash
```
then you need to run 
 ```bash
esm start
```
The above commands do the following:

- The `-p80:80 option maps *port* 80 from the Docker container to ports on your host computer. This should allow you to go to 
    > http://localhost
    with your web browser and see the ENVIRO client. It should say "Error: Failed to fetch. Is the server running?" at this point. 

- The `-p8765:8765` option allows the ENVIRO client to communicate with the `enviro` server (not yet running) via a *WebSocket*.

- The command `esm start` uses the <u>e</u>nviro <u>s</u>etup <u>m</u>anager to start a web server from which your browser can access the ENVRIO client. 

then run the command

 ```bash
make
```

then run the command

 ```bash
enviro
```
You can  play this game now !

How to run and/or use the project
===

The player can control the planet object through the "W","S","A","D" button on the computer, which represents four directions: up, down, left and right. You can go near other planets to devour them. At this time, the mass and volume of your planet will also increase
At this time, there is a turret on the left side of the game screen that will aim at the player's object at any time to strike. The player needs to avoid the attack of the shell while devouring the planet. After the player has been hit by the shell for five consecutive times, the planet will lose a certain amount of mass and volume and split a certain number of small red planets.


Acknowedges
===

This project can be developed beacause of supporting library can be found [here](https://github.com/klavinslab/enviro).


Thank you!
===

Thank you professor and teaching assistants for your hard work this quarter. I learned a lot of very useful knowledge!
