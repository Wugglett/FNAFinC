#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "include.h"
#include "struct.h"
#include "draw.h"

extern GameManager* app;

extern Camera* officeCam;

extern Camera* CurrentCam;

extern Animatronic* Freddy;
extern Animatronic* Bonnie;
extern Animatronic* Chica;
extern Animatronic* Foxy;

SDL_Texture* Map;

SDL_Texture* _1A_Map;
SDL_Texture* _1B_Map;
SDL_Texture* _1C_Map;
SDL_Texture* _2A_Map;
SDL_Texture* _2B_Map;
SDL_Texture* _3_Map;
SDL_Texture* _4A_Map;
SDL_Texture* _4B_Map;
SDL_Texture* _5_Map;
SDL_Texture* _6_Map;
SDL_Texture* _7_Map;

SDL_Texture* CameraOff;
SDL_Texture* CameraOn;

SDL_Texture* closedRightDoor;
SDL_Texture* closedLeftDoor;

SDL_Texture* rightButtonOff;
SDL_Texture* rightButtonLight;
SDL_Texture* rightButtonDoor;
SDL_Texture* rightButtonLightDoor;
SDL_Texture* leftButtonOff;
SDL_Texture* leftButtonLight;
SDL_Texture* leftButtonDoor;
SDL_Texture* leftButtonLightDoor;

SDL_Texture* powerLeftTexture;

SDL_Texture* usageTexture;
SDL_Texture* powerOne;
SDL_Texture* powerTwo;
SDL_Texture* powerThree;
SDL_Texture* powerFour;
SDL_Texture* powerFive;

SDL_Texture* amTime;
SDL_Texture* one;
SDL_Texture* two;
SDL_Texture* three;
SDL_Texture* four;
SDL_Texture* five;
SDL_Texture* six;

SDL_Texture* nightTexture;

extern long* then;

extern int FPS;

Camera* makeCamera(uint8_t n, char* screen, ...) {
    srand(time(NULL));
    Camera* c = (Camera*)malloc(sizeof(Camera)+(sizeof(SDL_Texture*)*n));
    
    c->num_screens = n;
    c->currentScreen = 0;
    c->pos = 0;
    c->step = (rand()%360);

    va_list screens;
    va_start(screens, screen);
    c->screens[0] = loadTexture(screen);
    for (int i = 1; i < n; i++) c->screens[i] = loadTexture(va_arg(screens, char*));
    va_end(screens);;

    return c;
}

void initCameras() {
    // call makeCamera for each camera and place it in the cameras array in gamemanager
    // cannot loop as each call to makeCamera will contain unique strings for the camera's associated screens

    int i = 0;
    Camera* _1A = makeCamera(7, "gfx/19.png", "gfx/2.png", "gfx/68.png", "gfx/223.png", "gfx/224.png", "gfx/355.png", "gfx/484.png");
    app->cameras[i++] = _1A;

    Camera* _1B = makeCamera(4, "gfx/48.png", "gfx/492.png", "gfx/90.png", "gfx/215.png");
    app->cameras[i++] = _1B;

    Camera* _1C = makeCamera(4, "gfx/66.png", "gfx/211.png", "gfx/338.png", "gfx/240.png");
    app->cameras[i++] = _1C;

    Camera* _2A = makeCamera(33, "gfx/43.png", "gfx/44.png", "gfx/206.png", "gfx/241.png", "gfx/244.png", "gfx/245.png", 
    "gfx/246.png", "gfx/247.png", "gfx/248.png", "gfx/250.png", "gfx/280.png", "gfx/282.png", "gfx/283.png", "gfx/284.png", "gfx/285.png",
    "gfx/286.png", "gfx/287.png", "gfx/288.png", "gfx/289.png", "gfx/290.png", "gfx/292.png", "gfx/302.png", "gfx/306.png", "gfx/327.png",
    "gfx/329.png", "gfx/330.png", "gfx/331.png", "gfx/332.png", "gfx/333.png", "gfx/334.png", "gfx/335.png", "gfx/336.png", "gfx/337.png");
    app->cameras[i++] = _2A;

    Camera* _2B = makeCamera(2, "gfx/0.png", "gfx/478.png");
    app->cameras[i++] = _2B;

    Camera* _3 = makeCamera(2, "gfx/62.png", "gfx/190.png");
    app->cameras[i++] = _3;

    Camera* _4A = makeCamera(3, "gfx/67.png", "gfx/487.png", "gfx/221.png");
    app->cameras[i++] = _4A;

    Camera* _4B = makeCamera(3, "gfx/49.png", "gfx/486.png", "gfx/376.png");
    app->cameras[i++] = _4B;

    Camera* _5 = makeCamera(3, "gfx/83.png", "gfx/205.png", "gfx/358.png");
    app->cameras[i++] = _5;

    Camera* _6 = makeCamera(8, "gfx/12.png", "gfx/13.png", "gfx/14.png", "gfx/15.png", "gfx/16.png", "gfx/17.png", "gfx/18.png", "gfx/20.png");
    app->cameras[i++] = _6;

    Camera* _7 = makeCamera(3, "gfx/41.png", "gfx/494.png", "gfx/217.png");
    app->cameras[i] = _7;

    Map = loadTexture("gfx/145.png");

    _1A_Map = loadTexture("gfx/170.png");
    _1B_Map = loadTexture("gfx/171.png");
    _1C_Map = loadTexture("gfx/177.png");
    _2A_Map = loadTexture("gfx/172.png");
    _2B_Map = loadTexture("gfx/165.png");
    _3_Map = loadTexture("gfx/168.png");
    _4A_Map = loadTexture("gfx/169.png");
    _4B_Map = loadTexture("gfx/173.png");
    _5_Map = loadTexture("gfx/174.png");
    _6_Map = loadTexture("gfx/175.png");
    _7_Map = loadTexture("gfx/176.png");

    CameraOff = loadTexture("gfx/167.png"); 
    CameraOn = loadTexture("gfx/166.png");

    CurrentCam = C_1A;
}

void initOfficeCam() {
    officeCam = (Camera*)malloc(sizeof(Camera)+(sizeof(SDL_Texture*)*7));
    
    officeCam->num_screens = 11;
    officeCam->currentScreen = 0;
    officeCam->step = 0;
    officeCam->pos = OFFICE_CAMERA_MAX/2;

    officeCam->screens[0] = loadTexture("gfx/39.png");
    officeCam->screens[1] = loadTexture("gfx/58.png");
    officeCam->screens[2] = loadTexture("gfx/127.png");
    officeCam->screens[3] = loadTexture("gfx/225.png");
    officeCam->screens[4] = loadTexture("gfx/227.png");
    officeCam->screens[5] = loadTexture("gfx/58.png");
    officeCam->screens[6] = loadTexture("gfx/304.png");
    officeCam->screens[7] = loadTexture("gfx/313.png"); // Freddy death
    officeCam->screens[8] = loadTexture("gfx/293.png"); // Bonnie death
    officeCam->screens[9] = loadTexture("gfx/228.png"); // Chica death
    officeCam->screens[10] = loadTexture("gfx/412.png");// Foxy death

    closedLeftDoor = loadTexture("gfx/102.png");
    closedRightDoor = loadTexture("gfx/118.png");
    rightButtonOff = loadTexture("gfx/134.png");
    rightButtonDoor = loadTexture("gfx/135.png");
    rightButtonLight = loadTexture("gfx/131.png");
    rightButtonLightDoor = loadTexture("gfx/47.png");
    leftButtonOff = loadTexture("gfx/122.png");
    leftButtonDoor = loadTexture("gfx/124.png");
    leftButtonLight = loadTexture("gfx/125.png");
    leftButtonLightDoor = loadTexture("gfx/130.png");

    powerLeftTexture = loadTexture("gfx/207.png");

    usageTexture = loadTexture("gfx/209.png");
    powerOne = loadTexture("gfx/212.png");
    powerTwo = loadTexture("gfx/213.png");
    powerThree = loadTexture("gfx/214.png");
    powerFour = loadTexture("gfx/456.png");
    powerFive = loadTexture("gfx/455.png");

    amTime = loadTexture("gfx/251.png");
    one = loadTexture("gfx/252.png");
    two = loadTexture("gfx/253.png");
    three = loadTexture("gfx/254.png");
    four = loadTexture("gfx/255.png");
    five = loadTexture("gfx/256.png");
    six = loadTexture("gfx/257.png");

    nightTexture = loadTexture("gfx/447.png");

    app->rButton.texture = rightButtonOff;
    app->lButton.texture = leftButtonOff;
}

void initAnimatronics() {
    Freddy = (Animatronic*)malloc(sizeof(Animatronic)+sizeof(Camera*)*6);
    Freddy->difficulty = 1;
    Freddy->freddy_timer = 5*FPS;
    Freddy->foxy_state = NONE;
    Freddy->timer = 3*FPS;
    Freddy->pos = 0;
    Freddy->killer = FALSE;
    Freddy->positions[0] = C_1A;
    Freddy->positions[1] = C_1B;
    Freddy->positions[2] = C_7;
    Freddy->positions[3] = C_6;
    Freddy->positions[4] = C_4A;
    Freddy->positions[5] = C_4B;

    Bonnie = (Animatronic*)malloc(sizeof(Animatronic)+sizeof(Camera*)*6);
    Bonnie->difficulty = 3;
    Bonnie->freddy_timer = -1;
    Bonnie->foxy_state = NONE;
    Bonnie->timer = 4*FPS;
    Bonnie->pos = 0;
    Bonnie->killer = FALSE;
    Bonnie->positions[0] = C_1A;
    Bonnie->positions[1] = C_1B;
    Bonnie->positions[2] = C_5;
    Bonnie->positions[3] = C_3;
    Bonnie->positions[4] = C_2A;
    Bonnie->positions[5] = C_2B;

    Chica = (Animatronic*)malloc(sizeof(Animatronic)+sizeof(Camera*)*6);
    Chica->difficulty = 2;
    Chica->freddy_timer = 0;
    Chica->foxy_state = NONE;
    Chica->timer = 4*FPS;
    Chica->pos = 0;
    Chica->killer = FALSE;
    Chica->positions[0] = C_1A;
    Chica->positions[1] = C_1B;
    Chica->positions[2] = C_7;
    Chica->positions[3] = C_6;
    Chica->positions[4] = C_4A;
    Chica->positions[5] = C_4B;

    Foxy = (Animatronic*)malloc(sizeof(Animatronic)*sizeof(Camera*)*3);
    Foxy->difficulty = 1;
    Foxy->freddy_timer = -1;
    Foxy->foxy_state = START;
    Foxy->timer = 4*FPS;
    Foxy->pos = 0;
    Foxy->killer = FALSE;
    Foxy->positions[0] = C_1C;
    Foxy->positions[1] = C_2B;
    Foxy->positions[2] = C_2A;
}

void initGame() {
    initOfficeCam();
    initCameras();
    initAnimatronics();
    FPS = 60;
}

void initApp() {
    app = (GameManager*)malloc(sizeof(GameManager)+(sizeof(Camera*)*MAX_CAMS));

    app->leftDoor.state = OPEN;
    app->rightDoor.state = OPEN;
    app->rightDoor.pos = RIGHTDOOR_POS;
    app->leftDoor.pos = LEFTDOOR_POS;

    app->rButton.pos = WIDTH-250;
    app->lButton.pos = 125;
    app->rButton.light = OFF;
    app->lButton.light = OFF;

    app->lookLeft = FALSE;
    app->lookRight = FALSE;

    app->pstate = OFFICE;

    app->power = MAX_POWER;
    app->time = MAX_TIME;

    app->powerOut = FALSE;

    app->gameover = FALSE;

    app->night = 0;
}

void free_assets() {
    for (int i = 0; i < MAX_CAMS; i++) {
        free(app->cameras[i]);
    }
    free(officeCam);
    free(app);
    free(Freddy);
    free(Bonnie);
    free(Chica);
    free(Foxy);
}