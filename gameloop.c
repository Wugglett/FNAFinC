#include "draw.h"
#include "struct.h"
#include "Animatronic.h"
#include "gameloop.h"
#include "gamelogic.h"
#include "input.h"

extern GameManager* app;

void logic() {
    if (app->powerOut == FALSE) {
        doPower();
        doFreddy();
        doBonnie();
        doChica();
        doFoxy();
    }
    playerInput();
    updateDoorPositions();
    updateCameras(); // Player is still able to look left and right without power
    checkTime(); // Player is still able to win (time ticks to 0) without power
}

void draw() {
    drawCamera();
    drawPower();
    drawTime();
}