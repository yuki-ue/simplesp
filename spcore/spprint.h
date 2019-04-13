﻿//--------------------------------------------------------------------------------
// Copyright (c) 2017-2019, sanko-shoko. All rights reserved.
//--------------------------------------------------------------------------------

#ifndef __SP_PRINT_H__
#define __SP_PRINT_H__

#include "spcore/spcom.h"
#include "spcore/spwrap.h"


namespace sp {

    //--------------------------------------------------------------------------------
    // print 
    //--------------------------------------------------------------------------------
  
    SP_CPUFUNC void _print(const int val) {
        SP_PRINTF("%d", val);
    }

    SP_CPUFUNC void _print(const SP_REAL val) {
        SP_PRINTF("%g", val);
    }

    SP_CPUFUNC void _print(const Cmp &cmp) {
        SP_PRINTF("[ %+.5lf, %+.5lf ]", cmp.re, cmp.im);
    }
    SP_CPUFUNC void print(const Cmp &cmp) {
        SP_PRINTF("Cmp ");
        _print(cmp);
        SP_PRINTF("\n");
    }

    SP_CPUFUNC void _print(const int dim, const int *dsize) {
        SP_PRINTF("[ ");
        for (int d = 0; d < dim; d++) {
            SP_PRINTF("%d ", dsize[d]);
        }
        SP_PRINTF("]");
    }
    SP_CPUFUNC void print(const int dim, const int *dsize) {
        SP_PRINTF("dsize ");
        _print(dim, dsize);
        SP_PRINTF("\n");
    }

    SP_CPUFUNC void _print(const Rect &rect) {
        SP_PRINTF("[ ");
        _print(rect.dim, rect.dbase);
        SP_PRINTF(", ");
        _print(rect.dim, rect.dsize);
        SP_PRINTF(" ]");
    }
    SP_CPUFUNC void print(const Rect &rect) {
        SP_PRINTF("Rect ");
        _print(rect);
        SP_PRINTF("\n");
    }

    SP_CPUFUNC void _print(const Vec2 &vec) {
        SP_PRINTF("[ %+.5lf %+.5lf ]", vec.x, vec.y);
    }
    SP_CPUFUNC void print(const Vec2 &vec) {
        SP_PRINTF("Vec2 ");
        _print(vec);
        SP_PRINTF("\n");
    }

    SP_CPUFUNC void _print(const Vec3 &vec) {
        SP_PRINTF("[ %+.5lf %+.5lf %+.5lf ]", vec.x, vec.y, vec.z);
    }
    SP_CPUFUNC void print(const Vec3 &vec) {
        SP_PRINTF("Vec3 ");
        _print(vec);
        SP_PRINTF("\n");
    }

    SP_CPUFUNC void _print(const Col3 &col) {
        SP_PRINTF("[ %d %d %d ]", col.r, col.g, col.b);
    }
    SP_CPUFUNC void print(const Col3 &col) {
        SP_PRINTF("Col3 ");
        _print(col);
        SP_PRINTF("\n");
    }

    SP_CPUFUNC void _print(const Col4 &col) {
        SP_PRINTF("[ %d %d %d %d ]", col.r, col.g, col.b, col.a);
    }
    SP_CPUFUNC void print(const Col4 &col) {
        SP_PRINTF("Col4 ");
        _print(col);
        SP_PRINTF("\n");
    }
    
    SP_CPUFUNC void _print(const VecPN2 &vec) {
        SP_PRINTF("[ ");
        _print(vec.pos);
        SP_PRINTF(", ");
        _print(vec.nrm);
        SP_PRINTF(" ]");
    }
    SP_CPUFUNC void print(const VecPN2 &vec) {
        SP_PRINTF("VecPN2 ");
        _print(vec);
        SP_PRINTF("\n");
    }

    SP_CPUFUNC void _print(const VecPN3 &vec) {
        SP_PRINTF("[ ");
        _print(vec.pos);
        SP_PRINTF(", ");
        _print(vec.nrm);
        SP_PRINTF(" ]");
    }
    SP_CPUFUNC void print(const VecPN3 &vec) {
        SP_PRINTF("VecPN3 ");
        _print(vec);
        SP_PRINTF("\n");
    }

    SP_CPUFUNC void _print(const Mesh2 &mesh) {
        SP_PRINTF("[ ");
        _print(mesh.pos[0]);
        SP_PRINTF(", ");
        _print(mesh.pos[1]);
        SP_PRINTF(", ");
        _print(mesh.pos[2]);
        SP_PRINTF(" ]");
    }
    SP_CPUFUNC void print(const Mesh2 &mesh) {
        SP_PRINTF("Mesh2 ");
        _print(mesh);
        SP_PRINTF("\n");
    }
    SP_CPUFUNC void _print(const Mesh3 &mesh) {
        SP_PRINTF("[ ");
        _print(mesh.pos[0]);
        SP_PRINTF(", ");
        _print(mesh.pos[1]);
        SP_PRINTF(", ");
        _print(mesh.pos[2]);
        SP_PRINTF(" ]");
    }
    SP_CPUFUNC void print(const Mesh3 &mesh) {
        SP_PRINTF("Mesh3 ");
        _print(mesh);
        SP_PRINTF("\n");
    }

    SP_CPUFUNC void _print(const Rot &rot) {
        SP_PRINTF("[ %+.5lf %+.5lf %+.5lf %+.5lf ]", rot.qx, rot.qy, rot.qz, rot.qw);
    }
    SP_CPUFUNC void print(const Rot &rot) {
        SP_PRINTF("Rot ");
        _print(rot);
        SP_PRINTF("\n");
    }

    SP_CPUFUNC void _print(const Pose &pose) {
        SP_PRINTF("[ ");
        _print(pose.rot);
        SP_PRINTF(", ");
        _print(pose.trn);
        SP_PRINTF(" ]");
    }
    SP_CPUFUNC void print(const Pose &pose) {
        SP_PRINTF("Pose ");
        _print(pose);
        SP_PRINTF("\n");
    }

    SP_CPUFUNC void _print(const CamParam &cam) {
        SP_PRINTF("[\n");
        SP_PRINTF("size %d %d\n", cam.dsize[0], cam.dsize[1]);
        SP_PRINTF("fx %.5lf, fy %.5lf\n", cam.fx, cam.fy);
        SP_PRINTF("cx %.5lf, cy %.5lf\n", cam.cx, cam.cy);
        SP_PRINTF("k1 %+.5lf, k2 %+.5lf, k3 %+.5lf\n", cam.k1, cam.k2, cam.k3);
        SP_PRINTF("p1 %+.5lf, p2 %+.5lf\n", cam.p1, cam.p2);
        SP_PRINTF("]");
    }
    SP_CPUFUNC void print(const CamParam &cam) {
        SP_PRINTF("CamParam ");
        _print(cam);
        SP_PRINTF("\n");
    }

    SP_CPUFUNC void print(const SP_REAL *mat, const int rows, const int cols) {
        SP_PRINTF("Mat %d %d [\n", rows, cols);
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                SP_PRINTF("%g ", mat[r * cols + c]);
            }
            SP_PRINTF("\n");
        }
        SP_PRINTF("]\n");
    }
    
    template <typename TYPE>
    SP_CPUFUNC void print(const ExPtr<TYPE> &mem) {
        SP_PRINTF("Mem ");

        print(mem.dim, mem.dsize);

        int size = 1;
        int unit[SP_DIMMAX] = { 0 };
        for (int i = 0; i < mem.dim; i++) {
            size *= mem.dsize[i];
            unit[i] = size;
        }

        for (int i = 0; i < size; i++) {
            for (int j = mem.dim - 1; j >= 0; j--) {
                if ((i + 0) % unit[j] == 0) {
                    SP_PRINTF((j != 0) ? "[\n" : "[ ");
                }
            }

            _print(mem.ptr[i]);
            SP_PRINTF(" ");

            for (int j = mem.dim - 1; j >= 0; j--) {
                if ((i + 1) % unit[j] == 0) {
                    SP_PRINTF("]\n");
                }
            }
        }
    }

    template<typename TYPE>
    SP_CPUFUNC void print(const TYPE &data, const char *name) {
        SP_PRINTF("%s ", name);
        print(data);
    }

    //--------------------------------------------------------------------------------
    // util
    //--------------------------------------------------------------------------------

    SP_CPUFUNC char* progressBar(const SP_REAL crnt, const SP_REAL size){
        const SP_REAL rate = (size > 1) ? crnt / (size - 1.0) : 1.0;

        static char bar[11] = { 0 };
        for (int i = 0; i < 10; i++){
            bar[i] = (i <= 10 * rate) ? '>' : '-';
        }
        return bar;
    }
}

#endif
