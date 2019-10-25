// Copyright 2019 Fuzhou Rockchip Electronics Co., Ltd. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sound.h"

#include <string.h>

#include "key_string.h"
#include "media_type.h"
#include "utils.h"

static const struct SampleFormatEntry {
  SampleFormat fmt;
  const char *fmt_str;
} sample_format_string_map[] = {
    {SAMPLE_FMT_U8, AUDIO_PCM_U8},   {SAMPLE_FMT_S16, AUDIO_PCM_S16},
    {SAMPLE_FMT_S32, AUDIO_PCM_S32}, {SAMPLE_FMT_VORBIS, AUDIO_VORBIS},
    {SAMPLE_FMT_AAC, AUDIO_AAC},     {SAMPLE_FMT_MP2, AUDIO_MP2},
};

const char *SampleFmtToString(SampleFormat fmt) {
  FIND_ENTRY_TARGET(fmt, sample_format_string_map, fmt, fmt_str)
  return nullptr;
}

SampleFormat StringToSampleFmt(const char *fmt_str) {
  FIND_ENTRY_TARGET_BY_STRCMP(fmt_str, sample_format_string_map, fmt_str, fmt)
  return SAMPLE_FMT_NONE;
}

bool SampleInfoIsValid(const SampleInfo &sample_info) {
  return (sample_info.fmt != SAMPLE_FMT_NONE) && (sample_info.channels > 0) &&
         (sample_info.sample_rate > 0);
}

size_t GetSampleSize(const SampleInfo &sample_info) {
  size_t sample_size = sample_info.channels;
  switch (sample_info.fmt) {
  case SAMPLE_FMT_U8:
    return sample_size;
  case SAMPLE_FMT_S16:
    return sample_size << 1;
  case SAMPLE_FMT_S32:
    return sample_size << 2;
  default:
    return 0;
  }
}

namespace easymedia {

bool ParseSampleInfoFromMap(std::map<std::string, std::string> &params,
                            SampleInfo &si) {
  std::string value;
  CHECK_EMPTY(value, params, KEY_INPUTDATATYPE)
  si.fmt = StringToSampleFmt(value.c_str());
  if (si.fmt == SAMPLE_FMT_NONE) {
    LOG("unsupport sample fmt %s\n", value.c_str());
    return false;
  }
  CHECK_EMPTY(value, params, KEY_CHANNELS)
  si.channels = std::stoi(value);
  CHECK_EMPTY(value, params, KEY_SAMPLE_RATE)
  si.sample_rate = std::stoi(value);
  CHECK_EMPTY(value, params, KEY_FRAMES)
  si.nb_samples = std::stoi(value);
  return true;
}

std::string to_param_string(const SampleInfo &si) {
  std::string s;
  const char *fmt = SampleFmtToString(si.fmt);
  if (!fmt)
    return s;
  PARAM_STRING_APPEND(s, KEY_INPUTDATATYPE, fmt);
  PARAM_STRING_APPEND_TO(s, KEY_CHANNELS, si.channels);
  PARAM_STRING_APPEND_TO(s, KEY_SAMPLE_RATE, si.sample_rate);
  PARAM_STRING_APPEND_TO(s, KEY_FRAMES, si.nb_samples);
  return s;
}

} // namespace easymedia
