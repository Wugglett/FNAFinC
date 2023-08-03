#include <stdio.h>
#include "struct.h"
#include "draw.h"
#include "include.h"
#include "gameloop.h"

extern GameManager* app;

extern Animatronic* Freddy;
extern Animatronic* Bonnie;
extern Animatronic* Chica;
extern Animatronic* Foxy;

extern Camera* CurrentCam;
extern Camera* officeCam;

extern SDL_Texture* Map;

extern SDL_Texture* _1A_Map;
extern SDL_Texture* _1B_Map;
extern SDL_Texture* _1C_Map;
extern SDL_Texture* _2A_Map;
extern SDL_Texture* _2B_Map;
extern SDL_Texture* _3_Map;
extern SDL_Texture* _4A_Map;
extern SDL_Texture* _4B_Map;
extern SDL_Texture* _5_Map;
extern SDL_Texture* _6_Map;
extern SDL_Texture* _7_Map;

extern SDL_Texture* CameraOff;
extern SDL_Texture* CameraOn;

extern SDL_Texture* closedRightDoor;
extern SDL_Texture* closedLeftDoor;
extern SDL_Texture* OnRightDoorButton;
extern SDL_Texture* OffRightDoorButton;
extern SDL_Texture* OnLeftDoorButton;
extern SDL_Texture* OffLeftDoorButton;

extern SDL_Texture* powerLeftTexture;

extern SDL_Texture* usageTexture;
extern SDL_Texture* powerOne;
extern SDL_Texture* powerTwo;
extern SDL_Texture* powerThree;
extern SDL_Texture* powerFour;
extern SDL_Texture* powerFive;

extern SDL_Texture* amTime;
extern SDL_Texture* one;
extern SDL_Texture* two;
extern SDL_Texture* three;
extern SDL_Texture* four;
extern SDL_Texture* five;
extern SDL_Texture* six;

extern SDL_Texture* nightTexture;

void initSDL() {
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    
    app->window = SDL_CreateWindow("FNAF", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    
    if (app->window == NULL) {
        printf("Failed to open window: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
    
    if (app->renderer == NULL) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_ShowCursor(1);
    SDL_SetRelativeMouseMode(SDL_TRUE); // Lock cursor inside the window
}

SDL_Texture* loadTexture(char* filename) {
    SDL_Texture* texture;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    texture = IMG_LoadTexture(app->renderer, filename);

    return texture;
}

void blit(SDL_Texture* texture, int x, int y) {
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(app->renderer, texture, NULL, &dest);
}

void prepareScene() {
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);
}

void presentScene() {
    SDL_RenderPresent(app->renderer);
}

void blitMapIcon(SDL_Texture* cam, SDL_Texture* background, int x, int y) {
    blit(background, x, y);
    blit(cam, x+15, y+5);
}

void drawCamera() {
    switch(app->pstate) {
        case OFFICE:
            blit(officeCam->screens[officeCam->currentScreen], officeCam->pos, 0);
            // draw right door either open or closed
            if (app->rightDoor.state == CLOSED) blit(closedRightDoor, app->rightDoor.pos, 0);
            // draw right door button either on or off
            blit(app->rButton.texture, app->rButton.pos, 275);
            // draw left door either open or closed
            if (app->leftDoor.state == CLOSED) blit(closedLeftDoor, app->leftDoor.pos, 0);
            // draw left door button either on or off
            blit(app->lButton.texture, app->lButton.pos, 275);
            // draw fan
            break;
        case CAM:
            blit(CurrentCam->screens[CurrentCam->currentScreen], CurrentCam->pos, 0);
            SDL_Texture* background = CameraOff;

            // Draw Camera map and highlight current cam
            blit(Map, WIDTH-400, HEIGHT-400);
            blitMapIcon(_1A_Map, (background = (CurrentCam == C_1A) ? CameraOn : CameraOff), WIDTH-300, HEIGHT-380);
            blitMapIcon(_1B_Map, (background = (CurrentCam == C_1B) ? CameraOn : CameraOff), WIDTH-330, HEIGHT-330);
            blitMapIcon(_1C_Map, (background = (CurrentCam == C_1C) ? CameraOn : CameraOff), WIDTH-350, HEIGHT-250);
            blitMapIcon(_2A_Map, (background = (CurrentCam == C_2A) ? CameraOn : CameraOff), WIDTH-300, HEIGHT-130);
            blitMapIcon(_2B_Map, (background = (CurrentCam == C_2B) ? CameraOn : CameraOff), WIDTH-300, HEIGHT-90);
            blitMapIcon(_3_Map, (background = (CurrentCam == C_3) ? CameraOn : CameraOff), WIDTH-380, HEIGHT-150);
            blitMapIcon(_4A_Map, (background = (CurrentCam == C_4A) ? CameraOn : CameraOff), WIDTH-190, HEIGHT-130);
            blitMapIcon(_4B_Map, (background = (CurrentCam == C_4B) ? CameraOn : CameraOff), WIDTH-190, HEIGHT-90);
            blitMapIcon(_5_Map, (background = (CurrentCam == C_5) ? CameraOn : CameraOff), WIDTH-420, HEIGHT-300);
            blitMapIcon(_6_Map, (background = (CurrentCam == C_6) ? CameraOn : CameraOff), WIDTH-80, HEIGHT-150);
            blitMapIcon(_7_Map, (background = (CurrentCam == C_7) ? CameraOn : CameraOff), WIDTH-80, HEIGHT-305);
    }
    // draw time
    // draw night
}

void changeCameraScreen(Animatronic* anim) {
    if (anim == Freddy) {
        switch(Freddy->pos) {
            case 1:
                // C_1A goes to state without Freddy
                if (Chica->pos != 0) {
                    if (Bonnie->pos != 0) C_1A->currentScreen = 6;
                }
                C_1B->currentScreen = 1;
                break;
            case 2:
                // C_1B goes to state without Freddy
                if (Chica->pos == 1) C_1B->currentScreen = 3;
                else if (Bonnie->pos == 1) C_1B->currentScreen = 2;
                else C_1B->currentScreen = 0;
                // C_7 goes to state with Freddy
                C_7->currentScreen = 1;
                break;
            case 3:
                // C_7 goes to state without Freddy
                if (Chica->pos == 2) C_7->currentScreen = 2;
                else C_7->currentScreen = 0;
                // C_6 is borken kitchen cam and does not change
                break;
            case 4:
                C_4A->currentScreen = 1;
                break;
            case 5:
                // C_4A goes to state without Freddy
                if (Chica->pos == 4) C_4A->currentScreen = 2;
                else C_4A->currentScreen = 0;
                C_4B->currentScreen = 1;
                break;
        }
    }
    else if (anim == Bonnie) {
        switch(Bonnie->pos) {
            case 0:
            // C_1A goes to state with Bonnie
            if (Chica->pos == 0) {
                if (Freddy->pos == 0) C_1A = 0;
            }
            else C_1A->currentScreen = 3;
            //C_2B goes to state without Bonnie
            C_2B->currentScreen = 0;
                break;
            case 1:
            // C_1A goes to state without Bonnie
            if (Chica->pos == 0) C_1A->currentScreen = 2;
            else if (Freddy->pos == 0) C_1A->currentScreen = 4;
            else C_1A->currentScreen = 6;
            // C_1B goes to state with Bonnie
            C_1B->currentScreen = 2;
                break;
            case 2:
            // C_1B goes to state without Bonnie
            if (Chica->pos == 1) C_1B->currentScreen = 3;
            else if (Freddy->pos == 1) C_1B->currentScreen = 1;
            else C_1B->currentScreen = 0;
            C_1B->currentScreen = 0;
            // C_5 goes to state with Bonnie
            C_5->currentScreen = 1;
                break;
            case 3:
            // C_5 goes to state without Bonnie
            C_5->currentScreen = 0;
            // C_3 goes to state with Bonnie
            C_3->currentScreen = 1;
                break;
            case 4:
            // C_3 goes to state without Bonnie
            C_3->currentScreen = 0;
            // C_2A goes to state with Bonnie
            C_2A->currentScreen = 2;
                break;
            case 5:
            // C_2A goes to state without Bonnie
            C_2A->currentScreen = 0;
            // C_2B goes to state with Bonnie
            C_2B->currentScreen = 1;
                break;
        }
    }
    else if (anim == Chica) {
        switch(Chica->pos) {
            case 0:
                // C_4B goes to state without Chica
                if (Freddy->pos == 5) C_4B->currentScreen = 1;
                else C_4B->currentScreen = 0;
                // C_1A goes to state with Chica
                if (Bonnie->pos == 0) C_1A->currentScreen = 0;
                else C_1A->currentScreen = 2;
                break;
            case 1:
                // C_1A goes to state without Chica
                if (Bonnie->pos == 0) C_1A->currentScreen = 3;
                else C_1A->currentScreen = 4;
                // C_1B goes to state with Chica
                C_1B->currentScreen = 3;
                break;
            case 2:
                // C_1B goes to state without Chica
                if (Bonnie->pos == 1) C_1B->currentScreen = 2;
                else if (Freddy->pos == 1) C_1B->currentScreen = 1;
                else C_1B->currentScreen = 0;
                // C_7 goes to state with Chica
                C_7->currentScreen = 2;
                break;
            case 3:
                // C_7 goes to state without Chica
                if (Freddy->pos == 2) C_7->currentScreen = 1;
                else C_7->currentScreen = 0;
                // C_6 is kitchen with no cam
                break;
            case 4:
                // C_4A goes to state with Chica
                C_4A->currentScreen = 2;
                break;
            case 5:
                // C_4A goes to state without Chica
                if (Freddy->pos == 4) C_4A->currentScreen = 1;
                else C_4A->currentScreen = 0;
                // C_4B goes to state with Chica
                C_4B->currentScreen = 2;
                break;
        }
    }
    else {
        switch(Foxy->foxy_state) {
            case START:
                // Stage is fully closed
                C_1C->currentScreen = 0;
                break;
            case PARTED:
                // Stage is partially open, Foxy can be seen somewhat behind the curtain
                C_1C->currentScreen = 1;
                break;
            case FULLYOPEN:
                // Stage is fully open and foxy can be seen
                C_1C->currentScreen = 2;
                break;
            case RUNNING:
                // Foxy is gone from the stage and is seen running down the hall
                C_1C->currentScreen = 3;
                C_2A->currentScreen = 8;
                break;
            case ATTACK:
                // Foxy tries to attack player, regardless of success stage camera is set to closed
                C_2A->currentScreen = 0;
                break;
            case NONE:
                printf("ERROR: Should never be there\n");
                exit(1);
                break;
        }
    }
}

void drawPower() {
    int powerUse = (int)app->leftDoor.state + (int)app->rightDoor.state + (int)app->lButton.light + (int)app->rButton.light + (int)app->pstate;
    SDL_Texture* currentPowerUse;
    SDL_Texture* currentPower;

    blit(powerLeftTexture, 25, HEIGHT-43);
    blit(usageTexture, 25, HEIGHT-93);

    if (app->powerOut) return;
    
    if (app->power <= MAX_POWER/5) currentPower = powerOne;
    else if (app->power <= (MAX_POWER/5)*2) currentPower = powerTwo;
    else if (app->power <= (MAX_POWER/5)*3) currentPower = powerThree;
    else if (app->power <= (MAX_POWER/5)*4) currentPower = powerFour;
    else currentPower = powerFive;

    blit(currentPower, 165, HEIGHT-50);

    switch (powerUse) {
        case 1:
            currentPowerUse = powerOne;
            break;
        case 2:
            currentPowerUse = powerTwo;
            break;
        case 3:
            currentPowerUse = powerThree;
            break;
        case 4:
            currentPowerUse = powerFour;
            break;
        case 5:
            currentPowerUse = powerFive;
            break;
        default:
            return;
    }
    blit(currentPowerUse, 100, HEIGHT-100);
}

void changeOfficeCam() {
    if (app->lButton.light == ON) {
        if (Bonnie->pos == 5) officeCam->currentScreen = 3;
        else officeCam->currentScreen = 1;
    }
    else if (app->rButton.light == ON) {
        if (Chica->pos == 5) officeCam->currentScreen = 4;
        else officeCam->currentScreen = 2;
    }
    else {
        officeCam->currentScreen = 0;
    }
}

void drawTime() {
    SDL_Texture* current_time;

    blit(nightTexture, WIDTH-112, 48); // Blit'ing "Night" and night number (will add later)

    blit(amTime, WIDTH-75, 12);

    if (app->time <= 0) current_time = six;
    else if (app->time <= MAX_TIME/6) current_time = five;
    else if (app->time <= (MAX_TIME/6)*2) current_time = four;
    else if (app->time <= (MAX_TIME/6)*3) current_time = three;
    else if (app->time <= (MAX_TIME/6)*4) current_time = two;
    else if (app->time <= (MAX_TIME/6)*5) current_time = one;
    else {
        blit(one, WIDTH-130, 11);
        blit(two, WIDTH-112, 11);
        return; // Twelve is made up of two textures so it blit'd differently
    }

    blit(current_time, WIDTH-112, 11);
}