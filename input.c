#include <stdio.h>
#include "input.h"
#include "include.h"
#include "struct.h"
#include "draw.h"

extern GameManager* app;

extern Camera* CurrentCam;

extern SDL_Texture* rightButtonOff;
extern SDL_Texture* rightButtonLight;
extern SDL_Texture* rightButtonDoor;
extern SDL_Texture* rightButtonLightDoor;
extern SDL_Texture* leftButtonOff;
extern SDL_Texture* leftButtonLight;
extern SDL_Texture* leftButtonDoor;
extern SDL_Texture* leftButtonLightDoor;

void doKeyDown(SDL_KeyboardEvent* event) {
    if (event->keysym.scancode == SDL_SCANCODE_ESCAPE) {
        printf("INFO: Exiting game\n");
        exit(0);
    }
    if (app->pstate == OFFICE) {
        switch(event->keysym.scancode) {
            case SDL_SCANCODE_M:
                app->pstate = CAM;
                break;
            case SDL_SCANCODE_LSHIFT:
                if (!app->powerOut) {
                    if (app->leftDoor.state == OPEN) {
                        app->leftDoor.state = CLOSED;
                        if (!app->lButton.light) app->lButton.texture = leftButtonDoor;
                        else app->lButton.texture = leftButtonLightDoor;
                    }
                    else {
                        app->leftDoor.state = OPEN;
                        if (!app->lButton.light) app->lButton.texture = leftButtonOff;
                        else app->lButton.texture = leftButtonLight;
                    }
                }
                break;
            case SDL_SCANCODE_RSHIFT:
                if (!app->powerOut) {
                    if (app->rightDoor.state == OPEN) {
                        app->rightDoor.state = CLOSED;
                        if (!app->rButton.light) app->rButton.texture = rightButtonDoor;
                        else app->rButton.texture = rightButtonLightDoor;
                    }
                    else {
                        app->rightDoor.state = OPEN;
                        if (!app->rButton.light) app->rButton.texture = rightButtonOff;
                        else app->rButton.texture = rightButtonLight;
                    }
                }
                break;
            case SDL_SCANCODE_A:
                app->lookLeft = TRUE;
                break;
            case SDL_SCANCODE_D:
                app->lookRight = TRUE;
                break;
            case SDL_SCANCODE_RETURN:
                if (!app->powerOut) {
                    if (app->rButton.light == ON) {
                        app->rButton.light = OFF;
                        if (app->rightDoor.state != CLOSED) app->rButton.texture = rightButtonOff;
                        else app->rButton.texture = rightButtonDoor;
                    }
                    else {
                        app->rButton.light = ON;
                        if (app->rightDoor.state != CLOSED) app->rButton.texture = rightButtonLight;
                        else app->rButton.texture = rightButtonLightDoor;
                    }
                    changeOfficeCam();
                }
                break;
            case SDL_SCANCODE_CAPSLOCK:
                if (!app->powerOut) {
                    if (app->lButton.light == ON) {
                        app->lButton.light = OFF;
                        if (app->leftDoor.state != CLOSED) app->lButton.texture = leftButtonOff;
                        else app->lButton.texture = leftButtonDoor;
                    }
                    else {
                        app->lButton.light = ON;
                        if (app->leftDoor.state != CLOSED) app->lButton.texture = leftButtonLight;
                        else app->lButton.texture = leftButtonLightDoor;
                    }
                    changeOfficeCam();
                }
                break;
            default:
                break;
        }
    }
    else {
        switch(event->keysym.scancode) {
            case SDL_SCANCODE_1:
                if (CurrentCam == C_1A) CurrentCam = C_1B;
                else if(CurrentCam == C_1B) CurrentCam = C_1C;
                else CurrentCam = C_1A; 
                break;
            case SDL_SCANCODE_2:
                if (CurrentCam == C_2A) CurrentCam = C_2B;
                else CurrentCam = C_2A;
                break;
            case SDL_SCANCODE_3:
                CurrentCam = C_3;
                break;
            case SDL_SCANCODE_4:
                if (CurrentCam == C_4A) CurrentCam = C_4B;
                else CurrentCam = C_4A;
                break;
            case SDL_SCANCODE_5:
                CurrentCam = C_5;
                break;
            case SDL_SCANCODE_6:
                CurrentCam = C_6;
                break;
            case SDL_SCANCODE_7:
                CurrentCam = C_7;
                break;
            case SDL_SCANCODE_M:
                app->pstate = OFFICE;
                break;
            default:
                break;
        }
    }
}

void doKeyUp(SDL_KeyboardEvent* event) {
    if (app->pstate == OFFICE) {
        switch (event->keysym.scancode) {
            case SDL_SCANCODE_A:
                app->lookLeft = FALSE;
                break;
            case SDL_SCANCODE_D:
                app->lookRight = FALSE;
                break;
            default:
                break;
        }
    }
}

void playerInput() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                doKeyDown(&event.key);
                break;
            case SDL_KEYUP:
                doKeyUp(&event.key);
                break;
            default:
                break;
        }
    }
}