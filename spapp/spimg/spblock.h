﻿//--------------------------------------------------------------------------------
// Copyright (c) 2017-2020, sanko-shoko. All rights reserved.
//--------------------------------------------------------------------------------

#ifndef __SP_BLOCK_H__
#define __SP_BLOCK_H__

#include "spcore/spcore.h"
#include "spapp/spimg/spimg.h"

namespace sp {

    SP_CPUFUNC int calcSAD(const Mem2<Byte> &src0, const Mem2<Byte> &src1, const int x, const int y, const Vec2 &flow, const int winSize) {

        const int offset = winSize / 2;

        const int fx = round(flow.x);
        const int fy = round(flow.y);

        int sad = 0;
        for (int wy = 0; wy < winSize; wy++) {
            for (int wx = 0; wx < winSize; wx++) {
                const int v0 = acs2(src0, x + wx - offset + fx, y + wy - offset + fy);
                const int v1 = acs2(src1, x + wx - offset, y + wy - offset);
                sad += abs(v0 - v1);
            }
        }
        const int eval = SP_BYTEMAX * winSize * winSize - sad;

        return eval;
    }

    //SP_CPUFUNC SP_REAL calcZNCC(const Mem2<Byte> &src0, const Mem2<Byte> &src1, const int x, const int y, const Vec2 &flow, const int winSize) {

    //    const int offset = winSize / 2;

    //    const int fx = round(flow.x);
    //    const int fy = round(flow.y);

    //    SP_REAL sum0 = 0.0;
    //    SP_REAL sum1 = 0.0;
    //    for (int wy = 0; wy < winSize; wy++) {
    //        for (int wx = 0; wx < winSize; wx++) {
    //            const int v0 = acs2(src0, x + wx - offset + fx, y + wy - offset + fy);
    //            const int v1 = acs2(src1, x + wx - offset, y + wy - offset);
    //            sum0 += v0;
    //            sum1 += v1;
    //        }
    //    }

    //    SP_REAL mean0 = sum0 / (winSize * winSize);
    //    SP_REAL mean1 = sum1 / (winSize * winSize);

    //    SP_REAL m00 = 0.0;
    //    SP_REAL m01 = 0.0;
    //    SP_REAL m11 = 0.0;
    //    for (int wy = 0; wy < winSize; wy++) {
    //        for (int wx = 0; wx < winSize; wx++) {
    //            const int v0 = acs2(src0, x + wx - offset + fx, y + wy - offset + fy) - mean0;
    //            const int v1 = acs2(src1, x + wx - offset, y + wy - offset) - mean1;
    //            m00 += v0 * v0;
    //            m01 += v0 * v1;
    //            m11 += v1 * v1;
    //        }
    //    }
    //    const SP_REAL div = sqrt(m00 * m11);
    //    const SP_REAL zncc = (div > SP_SMALL) ? m01 / div : 0.0;

    //    return zncc;
    //}

}

#endif