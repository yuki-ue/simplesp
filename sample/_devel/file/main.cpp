﻿
#include "simplesp.h"

using namespace sp;

int main(){ 
    {
        JSON json;

        json.nest("test");
        json.add("val0", "aaa");
        json.add("val1", "bbb");
        {
            json.nest("0");
            json.add("val00", "0");
            json.add("val01", "1");
            json.unnest();
        }
        json.unnest();

        json.save("test.json");
    }
    return 0;

    {
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

        Vec3 vec = getVec3(0.0, 0.0, 0.0);
        saveText("vec.txt", vec);
        vec = getVec3(2.0, 2.0, 3.0);
        loadText("vec.txt", vec);
        print(vec);

        Mat mat = zeroMat(3, 3);
        saveText("mat.txt", mat);
        mat = eyeMat(3, 3);
        loadText("mat.txt", mat);
        print(mat);
    }

    {
        XML xml;

        xml.nest("test");
        xml.add("val0", "aaa");
        xml.add("val1", "bbb");
        {
            xml.nest("0");
            xml.add("val00", "0");
            xml.add("val01", "1");
            xml.unnest();
        }
        xml.unnest();

        xml.save("test.xml");
    }
    return 0;
}