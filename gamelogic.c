#include <math.h>
#include <stdio.h>
#include "draw.h"
#include "include.h"
#include "struct.h"
#include "Animatronic.h"
#include "gamelogic.h"
#include "input.h"

extern int FPS;

extern GameManager* app;

extern Camera* officeCam;

extern Animatronic* Freddy;
extern Animatronic* Bonnie;
extern Animatronic* Chica;
extern Animatronic* Foxy;

extern SDL_Texture* rightButtonOff;
extern SDL_Texture* leftButtonOff;

int getPos(double pos) {
    double sinPos = ((sin(pos)+1)/2)*CAMERA_MAX;
    return (int) sinPos;
}

void updateCameras() {
    for (int i = 0; i < MAX_CAMS; i++) {
        if (i != 9) app->cameras[i]->pos = getPos(app->cameras[i]->step += 0.01);
        else {
            app->cameras[i]->currentScreen++;
            app->cameras[i]->currentScreen = (app->cameras[i]->currentScreen % app->cameras[i]->num_screens);
        }
    }
    if (app->lookRight && officeCam->pos >= OFFICE_CAMERA_MAX+4) officeCam->pos -= 4;
    if (app->lookLeft && officeCam->pos <= CAMERA_MIN-4) officeCam->pos += 4;
}

void powerOut() {
    app->pstate = OFFICE;

    app->leftDoor.state = OPEN;
    app->rightDoor.state = OPEN;

    app->lButton.light = OFF;
    app->rButton.light = OFF;

    app->lButton.texture = leftButtonOff;
    app->rButton.texture = rightButtonOff;

    officeCam->currentScreen = 6;
}

void doPower() {
    if (app->leftDoor.state == CLOSED) app->power--;
    if (app->rightDoor.state == CLOSED) app->power--;

    if (app->rButton.light == ON) app->power--;
    if (app->lButton.light == ON) app->power--;

    if (app->pstate == CAM) app->power--;

    if (app->power <= 0) { // Change officeCam to dark room and disable all doors, lights, and cams
        app->powerOut = TRUE;
        powerOut();
    }
}

void updateDoorPositions() {
    if (app->lookRight == TRUE && officeCam->pos >= OFFICE_CAMERA_MAX+4) {
        app->rightDoor.pos -= 4;
        app->leftDoor.pos -= 4;
        app->rButton.pos -= 4;
        app->lButton.pos -= 4;
    }
    else if (app->lookLeft == TRUE && officeCam->pos <= CAMERA_MIN-4) {
        app->leftDoor.pos += 4;
        app->rightDoor.pos += 4;
        app->rButton.pos += 4;
        app->lButton.pos += 4;
    }
}

void killPlayer() {
    static int timer_frames = 90;

    if (Freddy->killer == TRUE) officeCam->currentScreen = 7;
    else if (Bonnie->killer == TRUE) officeCam->currentScreen = 8;
    else if (Chica->killer == TRUE) officeCam->currentScreen = 9;
    else officeCam->currentScreen = 10;

    app->pstate = OFFICE;

    if (--timer_frames == 0) {
        printf("INFO: Gameover\n");
        exit(0);
    }
}

void checkTime() {
    if (--app->time <= 0) {
        printf("INFO: Player wins\n");
        exit(0);
    }
}

void capFrameRate(long *then, float *remainder) {
	long wait, frameTime;

	wait = 16 + *remainder;
	*remainder -= (int)*remainder;
	frameTime = SDL_GetTicks() - *then;
	wait -= frameTime;

	if (wait < 1) wait = 1;

	SDL_Delay(wait);
	*remainder += 0.667;
	*then = SDL_GetTicks();
}

void getFrames(long* then) {
    static int frames = 0;
    if ((SDL_GetTicks() - (*then)) > 1000) {
        FPS = frames;
        *then = SDL_GetTicks();
        frames = 0;
    }
    else frames++;
}