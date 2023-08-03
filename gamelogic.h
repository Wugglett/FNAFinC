#ifndef gamelogic 
    #define gamelogic
    void updateCameras();

    int getPos(double pos);

    void capFrameRate(long* then, float* remainder);

    void getFrames(long* then);

    void killPlayer();

    void checkTime();

    void doPower();

    void updateDoorPositions();
#endif