﻿#include "simplesp.h"
#include "spex/spgl.h"

using namespace sp;

class KmeansGUI : public BaseWindow {

    // cluster num
    int m_K;

    // point cloud
    Mem1<Vec2> m_pnts;

    // cluster index
    Mem1<int> m_index;

private:

    void help() {
        printf("'c' key : calc k-means\n");
        printf("'r' key : reset iteration\n");
        printf("\n");
    }

    virtual void init() {
        help();

        m_K = 10;

        // generate test data
        m_pnts.clear();
        for (int c = 0; c < m_K; c++) {
            const Vec2 vec = getVec2(300.0, 200.0);
            const Vec2 cent = randuVec2(vec.x / 2, vec.y / 2);

            const int num = 200;
            for (int n = 0; n < num; n++) {
                const Vec2 pnt = randgVec2(vec.x / 4, vec.y / 4) + cent;
                m_pnts.push(pnt);
            }
        }
    }

    virtual void keyFun(int key, int scancode, int action, int mods) {
        // iteration
        static int it = 0;

        if (m_key[GLFW_KEY_C] > 0) {
            it++;
            m_index = kmeans(2, m_pnts.ptr, m_pnts.size(), m_K, it);
        }

        if (m_key[GLFW_KEY_R] == 1) {
            it = 0;
            m_index.clear();
        }
    }

    virtual void display() {
        glClearColor(0.10f, 0.12f, 0.12f, 0.00f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render points
        {
            glLoadView2D(0, 0, m_viewPos, m_viewScale);

            glPointSize(5.f);
            glBegin(GL_POINTS);
            if (m_index.size() == 0) {
                glColor3f(1.0f, 1.0f, 1.0f);
                for (int i = 0; i < m_pnts.size(); i++) {
                    glVertex(m_pnts[i]);
                }
            }
            else {
                for (int i = 0; i < m_pnts.size(); i++) {
                    glColor(getCol3(m_index[i]));
                    glVertex(m_pnts[i]);
                }
            }
            glEnd();
        }

    }

};


int main(){

    KmeansGUI win;
    win.execute("kmeans", 800, 600);

    return 0;
}