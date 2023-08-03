#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "include.h"
#include "struct.h"
#include "Animatronic.h"
#include "draw.h"

extern GameManager* app;

extern Animatronic* Freddy;
extern Animatronic* Bonnie;
extern Animatronic* Chica;
extern Animatronic* Foxy;

extern Camera* CurrentCam;

extern int FPS;

void doFreddy() {
    static int timerOn = 0;
    srand(time(NULL));

    if(timerOn == 0 && --Freddy->timer <= 0) {
        if ((rand()%20)+1 < Freddy->difficulty) {
            timerOn = 1;
            Freddy->freddy_timer = (rand()%5 + 5)*FPS;
            printf("FREDDY: succeeded roll, timer on\n");
        }
        else {
            Freddy->timer = 3*FPS; 
            printf("FREDDY: failed roll\n");
        }
    }
    else if (timerOn == 1 && --Freddy->freddy_timer <= 0) {
        // Freddy cannot move if player is looking at him
        if (app->pstate == OFFICE || CurrentCam != Freddy->positions[Freddy->pos]){
            // Move to next position
            timerOn = 0;
            if (Freddy->positions[Freddy->pos] == C_4B) {
                if (app->pstate == CAM && app->rightDoor.state == OPEN) {
                    printf("FREDDY: kills player\n");// kill player if camera is open and door is open
                    Freddy->killer = TRUE;
                    app->gameover = TRUE;
                }
                else {Freddy->freddy_timer = (rand()%5 + 5)*FPS;printf("FREDDY: attempted player kill but camera not up\n");}
            }
            else {
                Freddy->pos++;
                changeCameraScreen(Freddy);
                Freddy->timer = 3*FPS;
                printf("FREDDY: not in-view, Freddy moving to pos: %d\n", Freddy->pos);
            }
        }
        else {
            printf("FREDDY: Looking at Freddy, resetting timer\n"); 
            Freddy->freddy_timer = (rand()%5 + 5)*FPS;
        }
    }
}

void doChica() {
    srand(time(NULL));

    if (--Chica->timer <= 0) {
        if ((rand()%20)+1 <= Chica->difficulty) {
            if (Chica->positions[Chica->pos] == C_4B) {
                if (app->pstate == CAM && app->rightDoor.state == OPEN) {
                    printf("CHICA: kills player\n");// kill player
                    Chica->killer = TRUE;
                    app->gameover = TRUE;
                }
                else {
                    Chica->pos = (rand()%3);
                    changeCameraScreen(Chica);
                    printf("CHICA: Door closed or camera shut, moving to random location between 1-A, 1-C, or 7\n");
                }
            }
            else {
                Chica->pos++;
                changeCameraScreen(Chica);
                printf("CHICA: moving to pos: %d\n", Chica->pos); 
            }
        }
        else {
            printf("CHICA: failed roll\n");
        }
        Chica->timer = 4*FPS;
    }
}

void doBonnie() {
    srand(time(NULL));

    if (--Bonnie->timer <= 0) {
        if ((rand()%20)+1 <= Bonnie->difficulty) {
            if (Bonnie->positions[Bonnie->pos] == C_2B) {
                if (app->pstate == CAM && app->leftDoor.state == OPEN) {
                    printf("BONNIE: kills player\n");// kill player
                    Bonnie->killer = TRUE;
                    app->gameover = TRUE;
                }
                else {
                    printf("BONNIE: Door closed or camera shut, moving to start position\n"); 
                    Bonnie->pos = 0;
                }
            }
            else {
                Bonnie->pos++; 
                changeCameraScreen(Bonnie);
                printf("BONNIE: moving to pos: %d\n", Bonnie->pos);
            }
        }
        else {
            printf("BONNIE: failed roll\n");
        }
        Bonnie->timer = 4*FPS;
    }
}

void doFoxy() {
    srand(time(NULL));

    if (Foxy->foxy_state == ATTACK) {
        if (app->leftDoor.state == OPEN) {
            printf("FOXY: kills player\n"); // kill player
            Foxy->killer = TRUE;
            app->gameover = TRUE;
        }
        else {
            app->power -= 100;
            Foxy->foxy_state = START;
            printf("FOXY: Left door closed, Foxy reset to START\n");
            changeCameraScreen(Foxy);
        }
    }
    if (Foxy->foxy_state == RUNNING) {
        if (CurrentCam == C_1C) Foxy->timer = 3*FPS; // Immediately start running down hallway if viewed in this state

        if (--Foxy->timer <= 0) {
            Foxy->foxy_state = ATTACK;
            changeCameraScreen(Foxy);
        }
    }
    else if (--Foxy->timer <= 0) {
        if ((app->pstate == OFFICE || CurrentCam != C_1C) && (rand()%20+1) <= Foxy->difficulty) {
            printf("FOXY: advanced stage\n"); 
            Foxy->foxy_state++; 
            changeCameraScreen(Foxy);
        }
        else {
            printf("FOXY: Foxy currently in view, or failed roll\n");
        }

        if (Foxy->foxy_state == RUNNING) {
            printf("FOXY: now in RUNNING state, timer increased to 10 secs\n"); 
            Foxy->timer = 10*FPS;
        }
        else Foxy->timer = 4*FPS;
    }
}