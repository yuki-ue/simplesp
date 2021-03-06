﻿#include "simplesp.h"
#include "spex/spgl.h"

using namespace sp;

class PathTracingGUI : public BaseWindow {

    // camera
    CamParam m_cam;

    // image
    Mem2<Col4> m_img;

    // object mesh model
    Mem1<Mesh3> m_model;

    // object to cam pose
    Pose m_pose;

    PathTrace m_pt;

    Thread m_thread;

private:

    void help() {
        printf("\n");
    }

    virtual void init() {

        help();

        m_cam = getCamParam(640, 480);

        m_img.resize(m_cam.dsize);
        m_img.zero();

        m_model = loadBunny(SP_DATA_DIR "/stanford/bun_zipper.ply");
        //loadPLY("C:/work/model.ply", m_model);
        if (m_model.size() == 0) {
            // if could not find stanford bunny, load dummy model
            m_model = loadGeodesicDorm(100.0, 1);
        }

        //m_model.push(m_model + getVec3(0, 50, 100));
        SP_ASSERT(m_model.size() > 0);

        m_pose = getPose(getVec3(0.0, 0.0, getModelDistance(m_model, m_cam)));


        static Mem1<Material> mats0;
        static Mem1<Material> mats1;
        mats0.resize(m_model.size());
        mats1.resize(m_model.size());
        static Material mat0;
        static Material mat1;
        memset(&mat0, 0, sizeof(Material));
        memset(&mat1, 0, sizeof(Material));

        mat0.col = getCol4f(0.9, 0.2, 0.2, 1.0);
        mat1.col = getCol4f(0.2, 0.9, 0.4, 1.0);
        //mat0.tr = 0.7f;
        //mat0.ri = 1.1f;
        //mat1.tr = 0.0f;
        for (int i = 0; i < mats0.size(); i++) {
            mats0[i] = mat0;
            mats1[i] = mat1;
        }

        Mem1<PathTrace::PntLight> lights;
        lights.push(PathTrace::PntLight());
        lights[0].pos = invPose(m_pose) * getVec3(200.0, -200.0, 0.0);

        PathTrace::Light amb = PathTrace::Light();
        amb.val = 0.8f;
        amb.sdw = 0.8f;
        m_pt.setAmbient(amb);
        //m_pt.setPntLights(lights);
        m_pt.setCam(m_cam, m_pose);

        //m_pt.addModel(m_model, mats0);
        Mem1<Mat> poses;
        poses.push(eyeMat(4, 4));
        poses.push(getMat(getPose(getVec3(100, 0, 0)), 4, 4));
        //m_pt.addModel(m_model, mats0, poses);
        m_pt.build();
    }

    virtual void keyFun(int key, int scancode, int action, int mods) {

        if (m_key[GLFW_KEY_D] == 1 || m_key[GLFW_KEY_N] == 1) {
        }

    }

    virtual void display() {
        glClearColor(0.10f, 0.12f, 0.12f, 0.00f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        if (m_thread.used() == false) {
            //m_pt.render(m_img, getCol4f(1.0, 0.3, 0.2, 1.0));
            m_pt.render(m_img);
        }
        {
            static Pose prev = m_pose;
            if (m_thread.used() == false && m_pose != prev) {
                m_pt.setCam(m_cam, m_pose);
                prev = m_pose;

                //Mem1<PathTrace::PntLight> lights;
                //lights.push(PathTrace::PntLight());
                //lights[0].pos = invPose(m_pose) * getVec3(200.0, -200.0, 0.0);
                //m_pt.setPntLights(lights);
            }
            m_thread.run([&]() {
                Timer timer;
                timer.start();
                m_pt.update();
                timer.stop();
                static double mean = 0.0;
                static int cnt = 0;
                mean = (mean * cnt + timer.getms()) / (1.0 + cnt);
                cnt++;
                //printf("%d %lf\n", cnt, mean);
                }, false);
        }

        {
            // view 2D
            glLoadView2D(m_cam, m_viewPos, m_viewScale);
            glTexImg(m_img);
        }
    }


    virtual void mousePos(double x, double y) {
        controlPose(m_pose, m_mouse, m_wcam, m_viewScale);
    }

    virtual void mouseScroll(double x, double y) {
        controlPose(m_pose, m_mouse, m_wcam, m_viewScale);
    }

};


int main(){
    PathTracingGUI win;
    win.execute("pathtracing", 800, 600);

    return 0;
}