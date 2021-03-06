//--------------------------------------------------------------------------------
// Copyright (c) 2017-2020, sanko-shoko. All rights reserved.
//--------------------------------------------------------------------------------

#ifndef __SP_GLWIN_H__
#define __SP_GLWIN_H__

#if SP_USE_GLEW
#define GLEW_STATIC
#include "GL/glew.h"
#endif

#include "GLFW/glfw3.h"
#include "spcore/spcore.h"

//--------------------------------------------------------------------------------
// additional define
//--------------------------------------------------------------------------------

#define GLFW_KEY_SHIFT   (GLFW_KEY_LAST + 1)
#define GLFW_KEY_CONTROL (GLFW_KEY_LAST + 2)
#define GLFW_KEY_ALT     (GLFW_KEY_LAST + 3)
#define GLFW_KEY_SUPER   (GLFW_KEY_LAST + 4)

#define GLFW_CALLBACK_SIZE   0x01
#define GLFW_CALLBACK_BUTTON 0x02
#define GLFW_CALLBACK_POS    0x04
#define GLFW_CALLBACK_SCROLL 0x08
#define GLFW_CALLBACK_KEY    0x10
#define GLFW_CALLBACK_CHAR   0x20
#define GLFW_CALLBACK_DROP   0x40
#define GLFW_CALLBACK_FOCUS  0x80

namespace sp {
     
    //--------------------------------------------------------------------------------
    // util
    //--------------------------------------------------------------------------------

    SP_CPUFUNC void initGLFW() {
        static bool once = false;
        if (once == true) return;
        once = true;

        SP_ASSERT(glfwInit());

        //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    }

    SP_CPUFUNC void initGLEW() {
        static bool once = false;
        if (once == true) return;
        once = true;

#if SP_USE_GLEW
        glewExperimental = GL_TRUE;
        SP_ASSERT(glewInit() == GLEW_OK);
#endif
    }

    //--------------------------------------------------------------------------------
    // mouse
    //--------------------------------------------------------------------------------

    class Mouse {

    public:

        // cursor position and move
        Vec2 pos, move;

        // scroll value
        double scroll;

        // button state
        int buttonL, pressL;
        int buttonR, pressR;
        int buttonM, pressM;

        Mouse() {
            reset();
        }

        void reset() {
            memset(this, 0, sizeof(Mouse));
        }

        void next() {
            setScroll(0.0, 0.0);
            pressL = 0;
            pressR = 0;
            pressM = 0;
        }

        void setButton(const int button, const int action, const int mods) {

            if (action == 1 && (buttonL == 0 && buttonR == 0 && buttonM == 0)) {
            }
            
            if (button == GLFW_MOUSE_BUTTON_LEFT) {
                buttonL = action;
                if (action == 1) pressL = +1;
                if (action == 0) pressL = -1;
            }
            if (button == GLFW_MOUSE_BUTTON_RIGHT) {
                buttonR = action;
                if (action == 1) pressR = +1;
                if (action == 0) pressR = -1;
            }
            if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
                buttonM = action;
                if (action == 1) pressM = +1;
                if (action == 0) pressM = -1;
            }
        }

        void setPos(const double x, const double y) {

            if (buttonL || buttonR || buttonM) {
                move = getVec2(x, y) - pos;
            }
            pos = getVec2(x, y);
        }

        void setScroll(const double x, const double y) {
            scroll = y;
        }

    };


    //--------------------------------------------------------------------------------
    // control
    //--------------------------------------------------------------------------------

    SP_CPUFUNC bool controlView(Vec2 &viewpPos, double &viewScale, const Mouse &mouse) {
        bool ret = false;
        if (mouse.buttonL && normVec(mouse.move) > 0.0) {
            viewpPos += mouse.move;
            ret = true;
        }

        if (mouse.scroll != 0) {
            viewpPos  *= (1.0 + mouse.scroll * 0.1);
            viewScale *= (1.0 + mouse.scroll * 0.1);
            ret = true;
        }
        return ret;
    }

    SP_CPUFUNC bool controlPose(Pose &pose, const Mouse &mouse, const CamParam &cam, const double viewScale, const Pose base = zeroPose()) {
        bool ret = false;

        Pose cpose = pose * invPose(base);
        if (cpose.pos.z < 0.0) return false;

        if (mouse.buttonM && normVec(mouse.move) > 0.0) {
            const double s = ((cam.type == CamParam_Pers) ? cpose.pos.z : 1.0) / viewScale;
            cpose.pos.x += SP_CAST_REAL(mouse.move.x / cam.fx * s);
            cpose.pos.y += SP_CAST_REAL(mouse.move.y / cam.fy * s);

            ret = true;
        }

        if (mouse.buttonL && normVec(mouse.move) > 0.0) {
            cpose.rot = getRotAngle(getVec3(+mouse.move.y, -mouse.move.x, 0.0), 0.01 * normVec(mouse.move)) * cpose.rot;
            ret = true;
        }

        if (mouse.scroll != 0) {
            cpose.pos -= unitVec(cpose.pos) * (cpose.pos.z * mouse.scroll * 0.02);
            ret = true;
        }

        pose = cpose * base;
        return ret;
    }


    //--------------------------------------------------------------------------------
    // base window
    //--------------------------------------------------------------------------------

    class BaseWindow {

    protected:

        virtual void windowSize(int width, int height) {
        }
        virtual void mouseButton(int button, int action, int mods) {
        }
        virtual void mousePos(double x, double y) {
        }
        virtual void mouseScroll(double x, double y) {
        }
        virtual void keyFun(int key, int scancode, int action, int mods) {
        }
        virtual void charFun(unsigned int charInfo) {
        }
        virtual void drop(int num, const char **paths) {
        }
        virtual void focus(int focused) {
        }

        virtual void init() {
        }
        virtual void display() {
        }
        virtual void post() {
        }
        virtual void terminate() {
        }
    protected:

        // window ptr
        GLFWwindow * m_win;

    public:

        // view position
        Vec2 m_viewPos;

        // view scale
        double m_viewScale;

        // keybord state
        char m_key[400];

        // mouse event class
        Mouse m_mouse;

        // window cam
        CamParam m_wcam;

        // call back flag;
        int m_callback;

        // 
        bool m_noswap;

    public:

        BaseWindow() {
            m_win = NULL;

            m_viewPos = getVec2(0.0, 0.0);
            m_viewScale = 1.0;

            memset(m_key, 0, sizeof(m_key));

            m_callback = GLFW_CALLBACK_FOCUS;
            m_noswap = false;
        }


        //--------------------------------------------------------------------------------
        // main window
        //--------------------------------------------------------------------------------

        bool create(const char *name, const int width, const int height) {

            if (m_win == NULL) {
                // glfw create window
                m_win = glfwCreateWindow(width, height, name, NULL, NULL);
            }

            if (m_win == NULL) {
                SP_PRINTD(" Can't create GLFW window.\n");
                glfwTerminate();
                return false;
            }

            m_wcam = getCamParam(width, height);

            // glfw make context
            glfwMakeContextCurrent(m_win);

            // vsync
            glfwSwapInterval(1);

            // glfw set event callbacks
            setCallback(m_win);

            return true;
        }

        bool main() {
            if (m_win == NULL) return false;

            if (glfwWindowShouldClose(m_win)) {
                glfwDestroyWindow(m_win);
                m_win = NULL;
                return false;
            }

            // glfw make context
            if (m_win != glfwGetCurrentContext()) {
                glfwMakeContextCurrent(m_win);
            }

            display();

            if (m_noswap == false) {
                glfwSwapBuffers(m_win);
            }
            else {
                sleep(10);
            }

            m_noswap = false;
            m_callback = false;

            m_mouse.next();

            return true;
        }

        void execute(const char *name, const int width, const int height) {

            initGLFW();
            SP_ASSERT(create(name, width, height) == true);

            initGLEW();

            init();

            while (!glfwWindowShouldClose(m_win)) {
                if (main() == false) break;

                glfwPollEvents();

                post();
            }
            glfwTerminate();
        }

        //--------------------------------------------------------------------------------
        // util
        //--------------------------------------------------------------------------------

        bool focused() {
            return glfwGetWindowAttrib(m_win, GLFW_FOCUSED);
        }

        void noswap() {
            m_noswap = true;
        }


    public:

        //--------------------------------------------------------------------------------
        // event process (internal)
        //--------------------------------------------------------------------------------
        
        virtual bool _pwindowSize(int width, int height) {
            return false;
        }
        virtual bool _pmouseButton(int button, int action, int mods) {
            return false;
        }
        virtual bool _pmousePos(double x, double y) {
            return false;
        }
        virtual bool _pmouseScroll(double x, double y) {
            return false;
        }
        virtual bool _pkeyFun(int key, int scancode, int action, int mods) {
            return false;
        }
        virtual bool _pcharFun(unsigned int charInfo) {
            return false;
        }
        virtual bool _pdrop(int num, const char **paths) {
            return false;
        }
        virtual bool _pfocus(int focused) {
            return false;
        }

        void _windowSize(int width, int height) {
            m_callback |= GLFW_CALLBACK_SIZE;
            m_wcam = getCamParam(width, height);

            ::glViewport(0, 0, width, height);

            if (_pwindowSize(width, height) == true)return;
            windowSize(width, height);
        }

        void _mouseButton(int button, int action, int mods) {
            if (action == 0 || action == 1) {
                m_callback |= GLFW_CALLBACK_BUTTON;
            }
            m_mouse.setButton(button, action, mods);

            if (_pmouseButton(button, action, mods) == true) return;
            mouseButton(button, action, mods);
        }

        void _mousePos(double x, double y) {
            m_callback |= GLFW_CALLBACK_POS;
            m_mouse.setPos(x, y);

            if (_pmousePos(x, y) == true) return;
            mousePos(x, y);
        }

        void _mouseScroll(double x, double y) {
            m_callback |= GLFW_CALLBACK_SCROLL;
            m_mouse.setScroll(x, y);

            if (_pmouseScroll(x, y) == true) return;
            mouseScroll(x, y);
        }

        void _keyFun(int key, int scancode, int action, int mods) {
            if (key < 0) return;

            if (action == 0 || action == 1) {
                m_callback |= GLFW_CALLBACK_KEY;
            }

            m_key[key] = static_cast<char>(action);

            if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT) {
                m_key[GLFW_KEY_SHIFT] = action;
            }
            if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL) {
                m_key[GLFW_KEY_CONTROL] = action;
            }
            if (key == GLFW_KEY_LEFT_ALT || key == GLFW_KEY_RIGHT_ALT) {
                m_key[GLFW_KEY_ALT] = action;
            }
            if (_pkeyFun(key, scancode, action, mods) == true) return;
            keyFun(key, scancode, action, mods);
        }

        void _charFun(unsigned int charInfo) {
            m_callback |= GLFW_CALLBACK_CHAR;

            if (_pcharFun(charInfo) == true) return;
            charFun(charInfo);
        }

        void _drop(int num, const char **paths) {
            m_callback |= GLFW_CALLBACK_DROP;

            if (_pdrop(num, paths) == true) return;
            drop(num, paths);
        }

        void _focus(int focused) {
            m_callback |= GLFW_CALLBACK_FOCUS;

            if (_pfocus(focused) == true) return;
            focus(focused);
        }

    protected:

        //--------------------------------------------------------------------------------
        // callback function
        //--------------------------------------------------------------------------------

        void setCallback(GLFWwindow *window) {
            // set my ptr
            glfwSetWindowUserPointer(window, this);

            glfwSetWindowSizeCallback(window, windowSizeCB);

            glfwSetMouseButtonCallback(window, mouseButtonCB);
            glfwSetCursorPosCallback(window, mousePosCB);
            glfwSetScrollCallback(window, mouseScrollCB);

            glfwSetKeyCallback(window, keyFunCB);
            glfwSetCharCallback(window, charFunCB);

            glfwSetDropCallback(window, dropCB);
            glfwSetWindowFocusCallback(window, focusCB);
        }

        static BaseWindow* getThisPtr(GLFWwindow *window) {
            return static_cast<BaseWindow*>(glfwGetWindowUserPointer(window));
        }

        static void windowSizeCB(GLFWwindow *window, int width, int height) {
            getThisPtr(window)->_windowSize(width, height);
        }
        static void mouseButtonCB(GLFWwindow *window, int button, int action, int mods) {
            getThisPtr(window)->_mouseButton(button, action, mods);
        }
        static void mousePosCB(GLFWwindow *window, double x, double y) {
            getThisPtr(window)->_mousePos(x, y);
        }
        static void mouseScrollCB(GLFWwindow *window, double x, double y) {
            getThisPtr(window)->_mouseScroll(x, y);
        }
        static void keyFunCB(GLFWwindow* window, int key, int scancode, int action, int mods) {
            getThisPtr(window)->_keyFun(key, scancode, action, mods);
        }
        static void charFunCB(GLFWwindow* window, unsigned int charInfo) {
            getThisPtr(window)->_charFun(charInfo);
        }
        static void dropCB(GLFWwindow *window, int num, const char **paths) {
            getThisPtr(window)->_drop(num, paths);
        }
        static void focusCB(GLFWwindow *window, int focused) {
            getThisPtr(window)->_focus(focused);
        }
    };

  

    template<typename TYPE>
    class ImgWindow : public BaseWindow {

    private:

        Mem2<TYPE> m_img;

        virtual void display() {
            if (m_img.size() > 0) {
                if (cmp(m_img.dsize, m_wcam.dsize, 2) == false) {
                    glfwSetWindowSize(m_win, m_img.dsize[0], m_img.dsize[1]);
                }
                glLoadView2D(m_img.dsize, m_viewPos, m_viewScale);
                glTexImg(m_img);
            }
        };


    public:

        ImgWindow() {
        }

        void set(const Mem2<TYPE> &img) {
            m_img = img;
        }

    };

}

#endif
