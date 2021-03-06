﻿//--------------------------------------------------------------------------------
// Copyright (c) 2017-2020, sanko-shoko. All rights reserved.
//--------------------------------------------------------------------------------

#ifndef __SP_COL_H__
#define __SP_COL_H__

#include "spcore/spcom.h"
#include "spcore/spgen/spbase.h"

#include "spcore/spgen/spvec.h"

namespace sp{

    //--------------------------------------------------------------------------------
    // color
    //--------------------------------------------------------------------------------

    // get color
    SP_GENFUNC Col3 getCol3(const Byte r, const Byte g, const Byte b){
        Col3 dst;
        dst.r = r; 
        dst.g = g; 
        dst.b = b;
        return dst;
    }

    // get color
    SP_GENFUNC Col4 getCol4(const Byte r, const Byte g, const Byte b, const Byte a) {
        Col4 dst;
        dst.r = r;
        dst.g = g;
        dst.b = b; 
        dst.a = a;
        return dst;
    }
    // get color
    SP_GENFUNC Col4 getCol4(const Col3 &col, const Byte a) {
        return getCol4(col.r, col.g, col.b, a);
    }

    // get color
    SP_GENFUNC Col3f getCol3f(const double r, const double g, const double b) {
        Col3f dst;
        dst.r = static_cast<float>(r);
        dst.g = static_cast<float>(g);
        dst.b = static_cast<float>(b);
        return dst;
    }
    // get color
    SP_GENFUNC Col4f getCol4f(const double r, const double g, const double b, const double a) {
        Col4f dst;
        dst.r = static_cast<float>(r);
        dst.g = static_cast<float>(g);
        dst.b = static_cast<float>(b);
        dst.a = static_cast<float>(a);
        return dst;
    }
    // get color
    SP_GENFUNC Col4f getCol4f(const Col3f &col, const double a) {
        return getCol4f(col.r, col.g, col.b, a);
    }


    //--------------------------------------------------------------------------------
    // color operator (function)
    //--------------------------------------------------------------------------------

    // addition
    SP_GENFUNC Col3f addCol(const Col3f &col0, const Col3f &col1) {
        return getCol3f(col0.r + col1.r, col0.g + col1.g, col0.b + col1.b);
    }
    // addition
    SP_GENFUNC Col4f addCol(const Col4f &col0, const Col4f &col1) {
        return getCol4f(col0.r + col1.r, col0.g + col1.g, col0.b + col1.b, col0.a + col1.a);
    }

    // subtraction
    SP_GENFUNC Col3f subCol(const Col3f &col0, const Col3f &col1) {
        return getCol3f(col0.r - col1.r, col0.g - col1.g, col0.b - col1.b);
    }
    // subtraction
    SP_GENFUNC Col4f subCol(const Col4f &col0, const Col4f &col1) {
        return getCol4f(col0.r - col1.r, col0.g - col1.g, col0.b - col1.b, col0.a - col1.a);
    }

    // multiple
    SP_GENFUNC Col3f mulCol(const Col3f &col, const double val) {
        return getCol3f(col.r * val, col.g * val, col.b * val);
    }
    // multiple
    SP_GENFUNC Col4f mulCol(const Col4f &col, const double val) {
        return getCol4f(col.r * val, col.g * val, col.b * val, col.a * val);
    }

    // division
    SP_GENFUNC Col3f divCol(const Col3f &col, const double val) {
        SP_ASSERT(fabs(val) > SP_SMALL);
        return getCol3f(col.r / val, col.g / val, col.b / val);
    }
    // division
    SP_GENFUNC Col4f divCol(const Col4f &col, const double val) {
        SP_ASSERT(fabs(val) > SP_SMALL);
        return getCol4f(col.r / val, col.g / val, col.b / val, col.a / val);
    }

    //--------------------------------------------------------------------------------
    // color operator
    //--------------------------------------------------------------------------------

    SP_GENFUNC Col3f operator + (const Col3f &col0, const Col3f &col1) {
        return addCol(col0, col1);
    }
    SP_GENFUNC Col4f operator + (const Col4f &col0, const Col4f &col1) {
        return addCol(col0, col1);
    }
    SP_GENFUNC void operator += (Col3f &col0, const Col3f &col1) {
        col0 = addCol(col0, col1);
    }
    SP_GENFUNC void operator += (Col4f &col0, const Col4f &col1) {
        col0 = addCol(col0, col1);
    }

    SP_GENFUNC Col3f operator * (const Col3f &col, const double val) {
        return mulCol(col, val);
    }
    SP_GENFUNC Col4f operator * (const Col4f &col, const double val) {
        return mulCol(col, val);
    }
    SP_GENFUNC void operator *= (Col3f &col, const double val) {
        col = mulCol(col, val);
    }
    SP_GENFUNC void operator *= (Col4f &col, const double val) {
        col = mulCol(col, val);
    }

    SP_GENFUNC Col3f operator / (const Col3f &col, const double val) {
        return divCol(col, val);
    }
    SP_GENFUNC Col4f operator / (const Col4f &col, const double val) {
        return divCol(col, val);
    }
    SP_GENFUNC void operator /= (Col3f &col, const double val) {
        col = divCol(col, val);
    }
    SP_GENFUNC void operator /= (Col4f &col, const double val) {
        col = divCol(col, val);
    }

    //--------------------------------------------------------------------------------
    // util
    //--------------------------------------------------------------------------------
    
    // mean
    SP_GENFUNC Col3f meanCol(const Col3f &col0, const double r0, const Col3f &col1, const double r1) {
        if (r0 + r1 == 0.0f) return getCol4f(0.0, 0.0, 0.0, 0.0);

        Col4f dst;
        dst.r = (col0.r * r0 + col1.r * r1) / (r0 + r1);
        dst.g = (col0.g * r0 + col1.g * r1) / (r0 + r1);
        dst.b = (col0.b * r0 + col1.b * r1) / (r0 + r1);
        return dst;
    }

    // mean
    SP_GENFUNC Col4f meanCol(const Col4f &col0, const double r0, const Col4f &col1, const double r1) {
        if (r0 + r1 == 0.0) return getCol4f(0.0, 0.0, 0.0, 0.0);
        if (r0 == 0.0) return col1;
        if (r1 == 0.0) return col0;

        Col4f dst;
        const float t0 = col0.a * r0;
        const float t1 = col1.a * r1;

        if (t0 + t1 > 0.0f) {
            dst.r = (col0.r * t0 + col1.r * t1) / (t0 + t1);
            dst.g = (col0.g * t0 + col1.g * t1) / (t0 + t1);
            dst.b = (col0.b * t0 + col1.b * t1) / (t0 + t1);
            dst.a = (t0 + t1) / (r0 + r1);
        }
        else {
            dst.r = (col0.r * r0 + col1.r * r1) / (r0 + r1);
            dst.g = (col0.g * r0 + col1.g * r1) / (r0 + r1);
            dst.b = (col0.b * r0 + col1.b * r1) / (r0 + r1);
            dst.a = 0.0f;
        }
        return dst;
    }

    // color id
    SP_GENFUNC Col3 getCol3FromId(const int id) {
        Col3 col = getCol3(0, 0, 0);
        col.r = (id) % 256;
        col.g = (id / (256)) % 256;
        col.b = (id / (256 * 256)) % 256;
        return col;
    }

    // color id
    SP_GENFUNC int getIdFromCol3(const Col3 &col) {
        int id = 0;
        id += col.r;
        id += col.g * (256);
        id += col.b * (256 * 256);
        if (id == 256 * 256 * 256 - 1) id = -1;
        return id;
    }


    //--------------------------------------------------------------------------------
    // color space
    //--------------------------------------------------------------------------------

    // convert phase to col3(rainbow), phase = [0, 1]
    SP_GENFUNC void cnvPhaseToCol(Col3 &col, const double phase){
        const double p = maxVal(0.0, minVal(phase, 1.0));

        col.r = static_cast<Byte>(255 * (sin(1.5 * SP_PI * p + SP_PI * (9.0 / 4.0)) + 1.0) / 2.0);
        col.g = static_cast<Byte>(255 * (sin(1.5 * SP_PI * p + SP_PI * (7.0 / 4.0)) + 1.0) / 2.0);
        col.b = static_cast<Byte>(255 * (sin(1.5 * SP_PI * p + SP_PI * (5.0 / 4.0)) + 1.0) / 2.0);
    }

    // convert hsv to col3, hsv = Vec3(h = [0, 2 * PI], s = [0, 1], v = [0, 1])
    SP_GENFUNC void cnvHSVToCol(Col3 &col, const Vec3 &hsv){
        const double h = hsv.x;
        const double s = hsv.y;
        const double v = hsv.z;

        const double r = (h < 0 || h >= 2 * SP_PI) ? 0 : h;
        const double D = (r * 180.0 / SP_PI) / 60.0;

        const double f = D - floor(D);
        const Byte uv = static_cast<Byte>(v * 255.0 + 0.5);
        const Byte ua = static_cast<Byte>(v * 255.0 * (1.0 - s) + 0.5);
        const Byte ub = static_cast<Byte>(v * 255.0 * (1.0 - s * f) + 0.5);
        const Byte uc = static_cast<Byte>(v * 255.0 * (1.0 - s * (1.0 - f)) + 0.5);
        
        switch (floor(D) % 6){
        case 0: col = getCol3(uv, uc, ua); break;
        case 1: col = getCol3(ub, uv, ua); break;
        case 2: col = getCol3(ua, uv, uc); break;
        case 3: col = getCol3(ua, ub, uv); break;
        case 4: col = getCol3(uc, ua, uv); break;
        case 5: col = getCol3(uv, ua, ub); break;
        }
    }

    // convert col3 to hsv, hsv = Vec3(h = [0, 2 * PI], s = [0, 1], v = [0, 1])
    SP_GENFUNC void cnvColToHSV(Vec3 &hsv, const Col3 &col){
        const double maxv = maxVal(col.r, maxVal(col.g, col.b));
        const double minv = minVal(col.r, minVal(col.g, col.b));
        const double subv = maxv - minv;

        double h, s, v;
        {
            h = 0.0;
            v = maxv / 255.0;
            s = subv / maxVal(maxv, 1.0);
        }
        if (subv == 0.0) {
            h = 0.0;
        }
        else if (col.r == maxv) {
            h = (col.g - col.b) / subv + 0.0;
        }
        else if (col.g == maxv) {
            h = (col.b - col.r) / subv + 2.0;
        }
        else if (col.b == maxv) {
            h = (col.r - col.g) / subv + 4.0;
        }
        h *= SP_PI / 3.0;
        if (h < 0.0) {
            h += 2 * SP_PI;
        }

        hsv = getVec3(h, s, v);
    }

    
    SP_GENFUNC void cnvXYZToLab(Vec3 &lab, const Vec3 &xyz){

        const Vec3 w = getVec3(0.95047, 1.00000, 1.0883); // D65

        auto f = [](const double v)-> SP_REAL {
            return SP_CAST_REAL((v > 0.008856) ? pow(v, 1.0 / 3.0) : (7.787 * v) + (16.0 / 116.0));
        };

        Vec3 val;
        val.x = f(xyz.x / w.x);
        val.y = f(xyz.y / w.y);
        val.z = f(xyz.z / w.z);

        const double l = (116.0 * val.y) - 16.0;
        const double a = 500.0 * (val.x - val.y);
        const double b = 200.0 * (val.y - val.z);

        lab = getVec3(l, a, b);
    }

    
    SP_GENFUNC void cnvLabToXYZ(Vec3 &xyz, const Vec3 &lab) {

        const Vec3 w = getVec3(0.95047, 1.00000, 1.0883); // D65

        auto f = [](const SP_REAL v)-> SP_REAL {
            return SP_CAST_REAL((v > 0.206897) ? pow(v, 3.0) : 0.001107 * (116.0 * v - 16.0));
        };

        Vec3 val;
        val.y = SP_CAST_REAL((lab.x + 16.0) / 116.0);
        val.x = SP_CAST_REAL(val.y + lab.y / 500.0);
        val.z = SP_CAST_REAL(val.y - lab.z / 200.0);

        xyz.x = f(val.x) * w.x;
        xyz.y = f(val.y) * w.y;
        xyz.z = f(val.z) * w.z;
    }

    SP_GENFUNC void cnvColToXYZ(Vec3 &xyz, const Col3 &col){
        auto f = [](const double v)-> SP_REAL {
            return SP_CAST_REAL((v > 0.040450) ? pow((v + 0.055) / 1.055, 2.4) : v / 12.92);
        };

        Vec3 val;
        val.x = f(col.r / 255.0);
        val.y = f(col.g / 255.0);
        val.z = f(col.b / 255.0);

        // D65
        xyz.x = SP_CAST_REAL(+0.412391 * val.x + 0.357584 * val.y + 0.180481 * val.z);
        xyz.y = SP_CAST_REAL(+0.212639 * val.x + 0.715169 * val.y + 0.072192 * val.z);
        xyz.z = SP_CAST_REAL(+0.019331 * val.x + 0.119195 * val.y + 0.950532 * val.z);
    }

    SP_GENFUNC void cnvXYZToCol(Col3 &col, const Vec3 &xyz) {
        auto f = [](const double v)-> SP_REAL {
            return (v > 0.0031308) ? 1.055 * pow(v, 1.0 / 2.4) - 0.055 : 12.92 * v;
        };

        Vec3 val;

        // D65
        val.x = SP_CAST_REAL(+3.240970 * xyz.x - 1.537383 * xyz.y - 0.498611 * xyz.z);
        val.y = SP_CAST_REAL(-0.969244 * xyz.x + 1.875968 * xyz.y + 0.041555 * xyz.z);
        val.z = SP_CAST_REAL(0.055630 * xyz.x - 0.203977 * xyz.y + 1.056972 * xyz.z);
    
        val.x = minVal(1.0, f(val.x));
        val.y = minVal(1.0, f(val.y));
        val.z = minVal(1.0, f(val.z));

        col = cast<Col3>(val);
    }

    SP_GENFUNC void cnvColToLab(Vec3 &lab, const Col3 &col){
        Vec3 xyz;
        cnvColToXYZ(xyz, col);
        cnvXYZToLab(lab, xyz);
    }

    SP_GENFUNC void cnvLabToCol(Col3 &col, const Vec3 &lab) {
        Vec3 xyz;
        cnvLabToXYZ(xyz, lab);
        cnvXYZToCol(col, xyz);
    }


    //--------------------------------------------------------------------------------
    // convert geom to image
    //--------------------------------------------------------------------------------

    SP_GENFUNC void cnvDepthToCol(Byte &dst, const double depth, const double nearPlane, const double farPlane){
        const double rate = 1.0 - (depth - nearPlane) / (farPlane - nearPlane);
        dst = static_cast<Byte>(255 * rate + 0.5);
    }

    SP_GENFUNC void cnvDepthToCol(Col3 &dst, const double depth, const double nearPlane, const double farPlane){
        const double rate = 1.0 - (depth - nearPlane) / (farPlane - nearPlane);
        cnvPhaseToCol(dst, rate);
    }

    SP_GENFUNC void cnvNormalToCol(Byte &dst, const Vec3 &nrm){
        dst = (nrm.z < 0) ? static_cast<Byte>(-255 * nrm.z) : 0;
    }

    SP_GENFUNC void cnvNormalToCol(Col3 &dst, const Vec3 &nrm){
        dst.r = static_cast<Byte>(255 * (1.0 - nrm.x) / 2);
        dst.g = static_cast<Byte>(255 * (1.0 - nrm.y) / 2);
        dst.b = static_cast<Byte>(255 * (1.0 - nrm.z) / 2);
    }

    SP_GENFUNC void cnvDispToCol(Byte &dst, const float &disp, const int maxDisp, const int minDisp) {
        const double rate = 1.0 - (disp - minDisp) / (maxDisp - minDisp);
        dst = static_cast<Byte>(255 * rate + 0.5);
    }

    SP_GENFUNC void cnvDispToCol(Col3 &dst, const float &disp, const int maxDisp, const int minDisp) {
        const double rate = 1.0 - (disp - minDisp) / (maxDisp - minDisp);
        cnvPhaseToCol(dst, rate);
    }


    //--------------------------------------------------------------------------------
    // util
    //--------------------------------------------------------------------------------

    // standord color i (0-12) v (0-7)
    SP_GENFUNC Col3 stdcol(const int i, const int v) {
        Col3 col;
        if (i == 0) {
            const float vlist[] = { 1.00f, 0.90f, 0.80f, 0.70f, 0.60f, 0.50f, 0.40f, 0.30f };
            cnvHSVToCol(col, sp::getVec3(0.0f, 0.0f, vlist[v]));
        }
        else {
            const float h = (i - 1) * 2.0f * SP_PI / 12.0f;
            const float slist[] = { 0.16f, 0.26f, 0.38f, 0.50f, 0.62f, 0.74f, 0.86f, 0.98f };
            const float vlist[] = { 0.98f, 0.95f, 0.91f, 0.86f, 0.80f, 0.73f, 0.65f, 0.56f };
            cnvHSVToCol(col, sp::getVec3(h, slist[v], vlist[v]));
        }
        return col;
    }
    
    SP_GENFUNC Col3 getCol3(const int label) {
        srand(maxVal(label + 1, 0));
        Col3 col;
        cnvHSVToCol(col, getVec3((randu() + 1.0) * SP_PI, 1.0, 1.0));
        return col;
    }

    SP_GENFUNC Col3 revCol(const Col3 &col) {
        Vec3 hsv;
        cnvColToHSV(hsv, col);
        hsv.z = SP_CAST_REAL((hsv.z > 0.5) ? hsv.z - 0.5 : hsv.z + 0.5);

        Col3 tmp;
        cnvHSVToCol(tmp, hsv);

        return tmp;
    }

    SP_GENFUNC Col4 revCol(const Col4 &col) {
        Col3 c3 = revCol(getCol3(col.r, col.g, col.b));
        return getCol4(c3.r, c3.g, c3.b, col.a);
    }

    //--------------------------------------------------------------------------------
    // blend
    //--------------------------------------------------------------------------------

    SP_GENFUNC Byte blendCol(const Byte &val0, const Byte &val1, const double rate = 0.5) {
        Byte val;
        val = static_cast<Byte>(val0 * rate + val1 * (1.0 - rate));
        return val;
    }

    SP_GENFUNC Col3 blendCol(const Col3 &col0, const Col3 &col1, const double rate = 0.5) {
        Col3 col;
        col.r = static_cast<Byte>(col0.r * rate + col1.r * (1.0 - rate));
        col.g = static_cast<Byte>(col0.g * rate + col1.g * (1.0 - rate));
        col.b = static_cast<Byte>(col0.b * rate + col1.b * (1.0 - rate));
        return col;
    }



}

#endif