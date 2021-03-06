﻿//--------------------------------------------------------------------------------
// Copyright (c) 2017-2020, sanko-shoko. All rights reserved.
//--------------------------------------------------------------------------------

#ifndef __SP_SVG_H__
#define __SP_SVG_H__

#include "spcore/spcore.h"
#include "spapp/spdata/spfile.h"

namespace sp {

    //--------------------------------------------------------------------------------
    // svg
    //--------------------------------------------------------------------------------

    using namespace std;

    namespace _svg {

        SP_CPUFUNC string rect(const double x, const double y, const double w, const double h, const char *option) {
            char str[SP_STRMAX];
            sprintf(str, "<rect x='%.1lfmm' y='%.1lfmm' width='%.1lfmm' height='%.1lfmm' %s/>\n", x, y, w, h, option);
            return str;
        }
        SP_CPUFUNC string circle(const double x, const double y, const double r, const char *option) {
            char str[SP_STRMAX];
            sprintf(str, "<circle cx='%.1lfmm' cy='%.1lfmm' r='%.1lfmm' %s/>", x, y, r, option);
            return str;
        }
        SP_CPUFUNC string text(const char *t, const double x, const double y, const int size, const char *option) {
            char str[SP_STRMAX];
            sprintf(str, "<text x='%.1lfmm' y='%.1lfmm' font-size='%d' %s/>%s</text>\n", x, y, size, option, t);
            return str;
        }
    }


    // A3 (420mm x 297mm), A4 (297mm x 210mm)
    SP_CPUFUNC void saveSVG(const char *path, const char *str, const int w = 297, const int h = 210) {
        File file(path, "w");

        file.printf("<!DOCTYPE svg PUBLIC ' -//W3C//DTD SVG 1.1//EN\' 'http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd'>\n");
        file.printf("<svg width='%dmm' height='%dmm' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'>\n", w, h);

        file.printf("%s", str);

        file.printf("</svg>\n");
    };



}

#endif