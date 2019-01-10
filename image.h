/*
 * Copyright (C) 2017 Rockchip Electronics Co., Ltd.
 * author: hertz.wang hertz.wong@rock-chips.com
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#ifndef RKMEDIA_IMAGE_H_
#define RKMEDIA_IMAGE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  PIX_FMT_NONE = -1,
  PIX_FMT_YUV420P,
  PIX_FMT_NV12,
  PIX_FMT_NV21,
  PIX_FMT_YUV422P,
  PIX_FMT_NV16,
  PIX_FMT_NV61,
  PIX_FMT_YVYU422,
  PIX_FMT_UYVY422,
  PIX_FMT_RGB565,
  PIX_FMT_BGR565,
  PIX_FMT_RGB888,
  PIX_FMT_BGR888,
  PIX_FMT_ARGB8888,
  PIX_FMT_ABGR8888,
  PIX_FMT_NB
} PixelFormat;

typedef struct {
  PixelFormat pix_fmt;
  int width;      // valid pixel width
  int height;     // valid pixel height
  int vir_width;  // stride width, same to buffer_width
  int vir_height; // stride height, same to buffer_height
} ImageInfo;

#ifdef __cplusplus
}
#endif

#endif // #ifndef RKMEDIA_IMAGE_H_
