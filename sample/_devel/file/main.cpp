﻿
#include "simplesp.h"

using namespace sp;

int main(){ 

    CamParam cam = getCamParam(640, 480);
    saveText("cam.txt", cam);
    cam = getCamParam(320, 240);
    loadText("cam.txt", cam);
    print(cam);

    Pose pose = zeroPose();
    saveText("pose.txt", pose);
    pose = getPose(getRot(1, 1, 1, 1));
    loadText("pose.txt", pose);
    print(pose);

    Vec3 vec = getVec(0.0, 0.0, 0.0);
    saveText("vec.txt", vec);
    vec = getVec(2.0, 2.0, 3.0);
    loadText("vec.txt", vec);
    print(vec);

    Mat mat = zeroMat(3, 3);
    saveText("mat.txt", mat);
    mat = eyeMat(3, 3);
    loadText("mat.txt", mat);
    print(mat);

    return 0;
}