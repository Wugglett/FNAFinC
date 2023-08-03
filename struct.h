#ifndef structs
    #define structs
    #include "include.h"

    #define WIDTH 1280
    #define HEIGHT 720

    #define MAX_CAMS 11

    #define C_1A app->cameras[0]
    #define C_1B app->cameras[1]
    #define C_1C app->cameras[2]
    #define C_2A app->cameras[3]
    #define C_2B app->cameras[4]
    #define C_3 app->cameras[5]
    #define C_4A app->cameras[6]
    #define C_4B app->cameras[7]
    #define C_5 app->cameras[8]
    #define C_6 app->cameras[9]
    #define C_7 app->cameras[10]

    #define CAMERA_MAX -210
    #define CAMERA_MIN 0
    #define OFFICE_CAMERA_MAX -320

    #define RIGHTDOOR_POS WIDTH-200
    #define LEFTDOOR_POS CAMERA_MIN-100

    #define MAX_POWER 10000
    #define MAX_TIME 18000

    typedef enum curtain_stage {NONE = -1, START, PARTED, FULLYOPEN, RUNNING, ATTACK} Curtain_Stage;
    typedef enum door_state {OPEN, CLOSED} DoorState;
    typedef enum player_state {OFFICE, CAM} PlayerState;
    typedef enum light {OFF, ON} Light;
    typedef enum bool {FALSE, TRUE} Bool;

    typedef struct camera {
        unsigned num_screens: 4;
        int pos; // Position from left to right (0 - 359)
        double step;
        unsigned currentScreen: 4;
        SDL_Texture* screens[];
    } Camera;

    typedef struct animatronic {
        int timer;
        int pos;
        unsigned difficulty: 4;
        int freddy_timer;
        Curtain_Stage foxy_state;
        Bool killer;
        Camera* positions[];
    } Animatronic;

    typedef struct door {
        DoorState state;
        int pos;
    } Door;

    typedef struct button {
        SDL_Texture* texture;
        int pos;
        Light light: 1;
    } Button;

    typedef struct gamemanager {
        SDL_Renderer* renderer;
        SDL_Window* window;
        Camera* cameras[MAX_CAMS];
        float power;
        int time;
        Door leftDoor;
        Door rightDoor;
        Button rButton;
        Button lButton;
        PlayerState pstate: 1;
        Bool lookLeft: 1;
        Bool lookRight: 1;
        Bool powerOut: 1;
        Bool gameover: 1;
        int night: 3;
    } GameManager;
#endif