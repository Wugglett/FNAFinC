#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "include.h"
#include "struct.h"
#include "draw.h"
#include "init.h"
#include "gameloop.h"
#include "gamelogic.h"
#include "input.h"

GameManager* app;

Animatronic* Freddy;
Animatronic* Bonnie;
Animatronic* Chica;
Animatronic* Foxy;

Camera* CurrentCam;
Camera* officeCam;

int FPS;
long then;

int WinMain() {

    initApp();
    initSDL();
    initGame();
    then = SDL_GetTicks();
    float remainder;

    while (1) {
        prepareScene();
        getFrames(&then);
        if (app->gameover == FALSE) {
            logic();
            playerInput();
        }
        else killPlayer();
        draw();
        presentScene();
        capFrameRate(&then, &remainder);
    }

    freeAssets();
}