#pragma once
/*
 *      Copyright (C) 2010-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "cores/AudioEngine/Interfaces/AEEncoder.h"

extern "C" {
#include "libswresample/swresample.h"
}

/* ffmpeg re-defines this, so undef it to squash the warning */
#undef restrict

class CAEEncoderFFmpeg: public IAEEncoder
{
public:
  CAEEncoderFFmpeg();
  virtual ~CAEEncoderFFmpeg();

  virtual bool IsCompatible(const AEAudioFormat& format);
  virtual bool Initialize(AEAudioFormat &format, bool allow_planar_input = false);
  virtual void Reset();

  virtual unsigned int GetBitRate();
  virtual AVCodecID GetCodecID();
  virtual unsigned int GetFrames();

  virtual int Encode(uint8_t *in, int in_size, uint8_t *out, int out_size);
  virtual int GetData(uint8_t **data);
  virtual double GetDelay(unsigned int bufferSize);
private:
  unsigned int BuildChannelLayout(const int64_t ffmap, CAEChannelInfo& layout);

  std::string m_CodecName;
  AVCodecID m_CodecID;
  unsigned int m_BitRate;
  AEAudioFormat m_CurrentFormat;
  AVCodecContext *m_CodecCtx;
  SwrContext *m_SwrCtx;
  CAEChannelInfo m_Layout;
  AVPacket m_Pkt;
  uint8_t m_Buffer[8 + FF_MIN_BUFFER_SIZE];
  int m_BufferSize;
  unsigned int  m_NeededFrames;
  bool m_NeedConversion;
};

