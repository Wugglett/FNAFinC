#ifndef drawHeader
    #define drawHeader
    #include "include.h"
    #include "struct.h"
    
    void initSDL();

    SDL_Texture* loadTexture(char* filename);

    void blit(SDL_Texture* texture, int x, int y);

    void prepareScene();

    void presentScene();

    void drawCamera();

    void changeCameraScreen(Animatronic* anim);

    void drawPower();

    void changeOfficeCam();

    void drawTime();
#endif