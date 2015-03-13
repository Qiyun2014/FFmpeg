/*
 * Intel MediaSDK QSV utility functions
 *
 * copyright (c) 2013 Luca Barbato
 *
 * This file is part of Libav.
 *
 * Libav is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * Libav is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Libav; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVCODEC_QSVDEC_H
#define AVCODEC_QSVDEC_H

#include <stdint.h>
#include <sys/types.h>

#include <mfx/mfxvideo.h>

#include "libavutil/frame.h"
#include "libavutil/pixfmt.h"

#include "avcodec.h"

typedef struct QSVFrame {
    AVFrame *frame;
    mfxFrameSurface1 *surface;

    mfxFrameSurface1 surface_internal;

    struct QSVFrame *next;
} QSVFrame;

typedef struct QSVContext {
    // the session used for decoding
    mfxSession session;

    // the session we allocated internally, in case the caller did not provide
    // one
    mfxSession internal_session;

    /**
     * a linked list of frames currently being used by QSV
     */
    QSVFrame *work_frames;

    // options set by the caller
    int async_depth;
    int iopattern;

    mfxExtBuffer **ext_buffers;
    int         nb_ext_buffers;
} QSVContext;

int ff_qsv_map_pixfmt(enum AVPixelFormat format);

int ff_qsv_decode_init(AVCodecContext *s, QSVContext *q, mfxSession session);

int ff_qsv_decode(AVCodecContext *s, QSVContext *q,
                  AVFrame *frame, int *got_frame,
                  AVPacket *avpkt);

int ff_qsv_decode_close(QSVContext *q);

#endif /* AVCODEC_QSVDEC_H */
