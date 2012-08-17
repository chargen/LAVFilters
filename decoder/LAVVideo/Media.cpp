/*
 *      Copyright (C) 2010-2012 Hendrik Leppkes
 *      http://www.1f0.de
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "stdafx.h"
#include "LAVVideo.h"
#include "Media.h"

#include <MMReg.h>

#include "moreuuids.h"

typedef struct {
  const CLSID*        clsMinorType;
  const enum AVCodecID  nFFCodec;
} FFMPEG_SUBTYPE_MAP;

// Map Media Subtype <> FFMPEG Codec Id
static const FFMPEG_SUBTYPE_MAP lavc_video_codecs[] = {
  // H264
  { &MEDIASUBTYPE_H264, AV_CODEC_ID_H264 },
  { &MEDIASUBTYPE_h264, AV_CODEC_ID_H264 },
  { &MEDIASUBTYPE_X264, AV_CODEC_ID_H264 },
  { &MEDIASUBTYPE_x264, AV_CODEC_ID_H264 },
  { &MEDIASUBTYPE_AVC1, AV_CODEC_ID_H264 },
  { &MEDIASUBTYPE_avc1, AV_CODEC_ID_H264 },
  { &MEDIASUBTYPE_CCV1, AV_CODEC_ID_H264 }, // Used by Haali Splitter

  // MPEG1/2
  { &MEDIASUBTYPE_MPEG1Payload, AV_CODEC_ID_MPEG1VIDEO },
  { &MEDIASUBTYPE_MPEG1Video,   AV_CODEC_ID_MPEG1VIDEO },
  { &MEDIASUBTYPE_MPEG2_VIDEO,  AV_CODEC_ID_MPEG2VIDEO },

  // MJPEG
  { &MEDIASUBTYPE_MJPG,   AV_CODEC_ID_MJPEG  },
  { &MEDIASUBTYPE_QTJpeg, AV_CODEC_ID_MJPEG  },
  { &MEDIASUBTYPE_MJPGB,  AV_CODEC_ID_MJPEGB },

  // VC-1
  { &MEDIASUBTYPE_WVC1, AV_CODEC_ID_VC1 },
  { &MEDIASUBTYPE_wvc1, AV_CODEC_ID_VC1 },
  { &MEDIASUBTYPE_WMVA, AV_CODEC_ID_VC1 },
  { &MEDIASUBTYPE_wmva, AV_CODEC_ID_VC1 },

  // WMV
  { &MEDIASUBTYPE_WMV1, AV_CODEC_ID_WMV1 },
  { &MEDIASUBTYPE_wmv1, AV_CODEC_ID_WMV1 },
  { &MEDIASUBTYPE_WMV2, AV_CODEC_ID_WMV2 },
  { &MEDIASUBTYPE_wmv2, AV_CODEC_ID_WMV2 },
  { &MEDIASUBTYPE_WMV3, AV_CODEC_ID_WMV3 },
  { &MEDIASUBTYPE_wmv3, AV_CODEC_ID_WMV3 },

  // VP8
  { &MEDIASUBTYPE_VP80, AV_CODEC_ID_VP8 },

  // MPEG4 ASP
  { &MEDIASUBTYPE_XVID, AV_CODEC_ID_MPEG4 },
  { &MEDIASUBTYPE_xvid, AV_CODEC_ID_MPEG4 },
  { &MEDIASUBTYPE_DIVX, AV_CODEC_ID_MPEG4 },
  { &MEDIASUBTYPE_divx, AV_CODEC_ID_MPEG4 },
  { &MEDIASUBTYPE_DX50, AV_CODEC_ID_MPEG4 },
  { &MEDIASUBTYPE_dx50, AV_CODEC_ID_MPEG4 },
  { &MEDIASUBTYPE_MP4V, AV_CODEC_ID_MPEG4 },
  { &MEDIASUBTYPE_mp4v, AV_CODEC_ID_MPEG4 },
  { &MEDIASUBTYPE_M4S2, AV_CODEC_ID_MPEG4 },
  { &MEDIASUBTYPE_m4s2, AV_CODEC_ID_MPEG4 },
  { &MEDIASUBTYPE_MP4S, AV_CODEC_ID_MPEG4 },
  { &MEDIASUBTYPE_mp4s, AV_CODEC_ID_MPEG4 },
  { &MEDIASUBTYPE_FMP4, AV_CODEC_ID_MPEG4 },

  // MS-MPEG4
  { &MEDIASUBTYPE_MPG4, AV_CODEC_ID_MSMPEG4V1 },
  { &MEDIASUBTYPE_mpg4, AV_CODEC_ID_MSMPEG4V1 },
  { &MEDIASUBTYPE_MP41, AV_CODEC_ID_MSMPEG4V1 },
  { &MEDIASUBTYPE_mp41, AV_CODEC_ID_MSMPEG4V1 },
  { &MEDIASUBTYPE_DIV1, AV_CODEC_ID_MSMPEG4V1 },
  { &MEDIASUBTYPE_div1, AV_CODEC_ID_MSMPEG4V1 },

  { &MEDIASUBTYPE_MP42, AV_CODEC_ID_MSMPEG4V2 },
  { &MEDIASUBTYPE_mp42, AV_CODEC_ID_MSMPEG4V2 },
  { &MEDIASUBTYPE_DIV2, AV_CODEC_ID_MSMPEG4V2 },
  { &MEDIASUBTYPE_div2, AV_CODEC_ID_MSMPEG4V2 },

  { &MEDIASUBTYPE_MP43, AV_CODEC_ID_MSMPEG4V3 },
  { &MEDIASUBTYPE_mp43, AV_CODEC_ID_MSMPEG4V3 },
  { &MEDIASUBTYPE_DIV3, AV_CODEC_ID_MSMPEG4V3 },
  { &MEDIASUBTYPE_div3, AV_CODEC_ID_MSMPEG4V3 },
  { &MEDIASUBTYPE_MPG3, AV_CODEC_ID_MSMPEG4V3 },
  { &MEDIASUBTYPE_mpg3, AV_CODEC_ID_MSMPEG4V3 },
  { &MEDIASUBTYPE_DIV4, AV_CODEC_ID_MSMPEG4V3 },
  { &MEDIASUBTYPE_div4, AV_CODEC_ID_MSMPEG4V3 },
  { &MEDIASUBTYPE_DIV5, AV_CODEC_ID_MSMPEG4V3 },
  { &MEDIASUBTYPE_div5, AV_CODEC_ID_MSMPEG4V3 },
  { &MEDIASUBTYPE_DIV6, AV_CODEC_ID_MSMPEG4V3 },
  { &MEDIASUBTYPE_div6, AV_CODEC_ID_MSMPEG4V3 },
  { &MEDIASUBTYPE_DVX3, AV_CODEC_ID_MSMPEG4V3 },
  { &MEDIASUBTYPE_dvx3, AV_CODEC_ID_MSMPEG4V3 },

  // Flash
  { &MEDIASUBTYPE_FLV1, AV_CODEC_ID_FLV1 },
  { &MEDIASUBTYPE_flv1, AV_CODEC_ID_FLV1 },
  { &MEDIASUBTYPE_VP60, AV_CODEC_ID_VP6  },
  { &MEDIASUBTYPE_vp60, AV_CODEC_ID_VP6  },
  { &MEDIASUBTYPE_VP61, AV_CODEC_ID_VP6  },
  { &MEDIASUBTYPE_vp61, AV_CODEC_ID_VP6  },
  { &MEDIASUBTYPE_VP62, AV_CODEC_ID_VP6  },
  { &MEDIASUBTYPE_vp62, AV_CODEC_ID_VP6  },
  { &MEDIASUBTYPE_VP6A, AV_CODEC_ID_VP6A },
  { &MEDIASUBTYPE_vp6a, AV_CODEC_ID_VP6A },
  { &MEDIASUBTYPE_VP6F, AV_CODEC_ID_VP6F },
  { &MEDIASUBTYPE_vp6f, AV_CODEC_ID_VP6F },
  { &MEDIASUBTYPE_FLV4, AV_CODEC_ID_VP6F },
  { &MEDIASUBTYPE_flv4, AV_CODEC_ID_VP6F },
  { &MEDIASUBTYPE_FSV1, AV_CODEC_ID_FLASHSV },

  // Real
  { &MEDIASUBTYPE_RV10, AV_CODEC_ID_RV10 },
  { &MEDIASUBTYPE_RV20, AV_CODEC_ID_RV20 },
  { &MEDIASUBTYPE_RV30, AV_CODEC_ID_RV30 },
  { &MEDIASUBTYPE_RV40, AV_CODEC_ID_RV40 },

  // DV Video
  { &MEDIASUBTYPE_dvsd, AV_CODEC_ID_DVVIDEO },
  { &MEDIASUBTYPE_DVSD, AV_CODEC_ID_DVVIDEO },
  { &MEDIASUBTYPE_CDVH, AV_CODEC_ID_DVVIDEO },
  { &MEDIASUBTYPE_dv25, AV_CODEC_ID_DVVIDEO },
  { &MEDIASUBTYPE_DV25, AV_CODEC_ID_DVVIDEO },
  { &MEDIASUBTYPE_dv50, AV_CODEC_ID_DVVIDEO },
  { &MEDIASUBTYPE_DV50, AV_CODEC_ID_DVVIDEO },
  { &MEDIASUBTYPE_DVCP, AV_CODEC_ID_DVVIDEO },
  { &MEDIASUBTYPE_DV5P, AV_CODEC_ID_DVVIDEO },
  { &MEDIASUBTYPE_DVPP, AV_CODEC_ID_DVVIDEO },
  { &MEDIASUBTYPE_DVC,  AV_CODEC_ID_DVVIDEO },

  // Misc Formats
  { &MEDIASUBTYPE_SVQ1, AV_CODEC_ID_SVQ1 },
  { &MEDIASUBTYPE_SVQ3, AV_CODEC_ID_SVQ3 },
  { &MEDIASUBTYPE_H261, AV_CODEC_ID_H261 },
  { &MEDIASUBTYPE_h261, AV_CODEC_ID_H261 },
  { &MEDIASUBTYPE_H263, AV_CODEC_ID_H263 },
  { &MEDIASUBTYPE_h263, AV_CODEC_ID_H263 },
  { &MEDIASUBTYPE_S263, AV_CODEC_ID_H263 },
  { &MEDIASUBTYPE_s263, AV_CODEC_ID_H263 },
  { &MEDIASUBTYPE_THEORA, AV_CODEC_ID_THEORA },
  { &MEDIASUBTYPE_theora, AV_CODEC_ID_THEORA },
  { &MEDIASUBTYPE_TSCC, AV_CODEC_ID_TSCC },
  { &MEDIASUBTYPE_IV50, AV_CODEC_ID_INDEO5 },
  { &MEDIASUBTYPE_IV41, AV_CODEC_ID_INDEO4 },
  { &MEDIASUBTYPE_IV31, AV_CODEC_ID_INDEO3 },
  { &MEDIASUBTYPE_IV32, AV_CODEC_ID_INDEO3 },
  { &MEDIASUBTYPE_FPS1, AV_CODEC_ID_FRAPS },
  { &MEDIASUBTYPE_HuffYUV,  AV_CODEC_ID_HUFFYUV },
  { &MEDIASUBTYPE_Lagarith, AV_CODEC_ID_LAGARITH },
  { &MEDIASUBTYPE_CVID,  AV_CODEC_ID_CINEPAK },
  { &MEDIASUBTYPE_QTRle, AV_CODEC_ID_QTRLE },
  { &MEDIASUBTYPE_VP30, AV_CODEC_ID_VP3  },
  { &MEDIASUBTYPE_VP31, AV_CODEC_ID_VP3  },
  { &MEDIASUBTYPE_CSCD, AV_CODEC_ID_CSCD },
  { &MEDIASUBTYPE_QPEG, AV_CODEC_ID_QPEG },
  { &MEDIASUBTYPE_QP10, AV_CODEC_ID_QPEG },
  { &MEDIASUBTYPE_QP11, AV_CODEC_ID_QPEG },
  { &MEDIASUBTYPE_MSZH, AV_CODEC_ID_MSZH },
  { &MEDIASUBTYPE_ZLIB, AV_CODEC_ID_ZLIB },
  { &MEDIASUBTYPE_QTRpza, AV_CODEC_ID_RPZA },
  { &MEDIASUBTYPE_PNG, AV_CODEC_ID_PNG   },
  { &MEDIASUBTYPE_PCM, AV_CODEC_ID_MSRLE }, // Yeah, PCM. Its the same FourCC as used by MS-RLE
  { &MEDIASUBTYPE_apch, AV_CODEC_ID_PRORES },
  { &MEDIASUBTYPE_apcn, AV_CODEC_ID_PRORES },
  { &MEDIASUBTYPE_apcs, AV_CODEC_ID_PRORES },
  { &MEDIASUBTYPE_apco, AV_CODEC_ID_PRORES },
  { &MEDIASUBTYPE_ap4h, AV_CODEC_ID_PRORES },
  { &MEDIASUBTYPE_ULRA, AV_CODEC_ID_UTVIDEO },
  { &MEDIASUBTYPE_ULRG, AV_CODEC_ID_UTVIDEO },
  { &MEDIASUBTYPE_ULY0, AV_CODEC_ID_UTVIDEO },
  { &MEDIASUBTYPE_ULY2, AV_CODEC_ID_UTVIDEO },
  { &MEDIASUBTYPE_AMVV, AV_CODEC_ID_AMV     },
  { &MEDIASUBTYPE_AMVF, AV_CODEC_ID_AMV     },
  { &MEDIASUBTYPE_DiracVideo, AV_CODEC_ID_DIRAC },
  { &MEDIASUBTYPE_DRAC, AV_CODEC_ID_DIRAC },
  { &MEDIASUBTYPE_AVdn, AV_CODEC_ID_DNXHD },
  { &MEDIASUBTYPE_CRAM, AV_CODEC_ID_MSVIDEO1 },
  { &MEDIASUBTYPE_MSVC, AV_CODEC_ID_MSVIDEO1 },
  { &MEDIASUBTYPE_WHAM, AV_CODEC_ID_MSVIDEO1 },
  { &MEDIASUBTYPE_8BPS, AV_CODEC_ID_8BPS  },
  { &MEDIASUBTYPE_LOCO, AV_CODEC_ID_LOCO  },
  { &MEDIASUBTYPE_ZMBV, AV_CODEC_ID_ZMBV  },
  { &MEDIASUBTYPE_VCR1, AV_CODEC_ID_VCR1 },
  { &MEDIASUBTYPE_AASC, AV_CODEC_ID_AASC },
  { &MEDIASUBTYPE_SNOW, AV_CODEC_ID_SNOW },
  { &MEDIASUBTYPE_FFV1, AV_CODEC_ID_FFV1 },
  { &MEDIASUBTYPE_FFVH, AV_CODEC_ID_FFVHUFF },

  // Game Formats
  { &MEDIASUBTYPE_BIKI, AV_CODEC_ID_BINKVIDEO  },
  { &MEDIASUBTYPE_BIKB, AV_CODEC_ID_BINKVIDEO  },
  { &MEDIASUBTYPE_SMK2, AV_CODEC_ID_SMACKVIDEO },
  { &MEDIASUBTYPE_SMK4, AV_CODEC_ID_SMACKVIDEO },

  // Special raw formats
  { &MEDIASUBTYPE_v210, AV_CODEC_ID_V210 },
  { &MEDIASUBTYPE_v410, AV_CODEC_ID_V410 },
};

// Define Input Media Types
const AMOVIESETUP_MEDIATYPE CLAVVideo::sudPinTypesIn[] = {
  // H264
  { &MEDIATYPE_Video, &MEDIASUBTYPE_H264 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_h264 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_X264 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_x264 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_AVC1 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_avc1 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_CCV1 },

  // MPEG1/2
  { &MEDIATYPE_Video, &MEDIASUBTYPE_MPEG1Payload },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_MPEG1Video   },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_MPEG2_VIDEO  },

  // MJPEG
  { &MEDIATYPE_Video, &MEDIASUBTYPE_MJPG   },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_QTJpeg },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_MJPGB  },

  // VC-1
  { &MEDIATYPE_Video, &MEDIASUBTYPE_WVC1 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_wvc1 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_WMVA },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_wmva },

  // WMV
  { &MEDIATYPE_Video, &MEDIASUBTYPE_WMV1 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_wmv1 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_WMV2 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_wmv2 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_WMV3 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_wmv3 },

  // VP8
  { &MEDIATYPE_Video, &MEDIASUBTYPE_VP80 },

  // MPEG4 ASP
  { &MEDIATYPE_Video, &MEDIASUBTYPE_XVID },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_xvid },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DIVX },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_divx },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DX50 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_dx50 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_MP4V },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_mp4v },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_M4S2 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_m4s2 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_MP4S },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_mp4s },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_FMP4 },

  // MS-MPEG4
  { &MEDIATYPE_Video, &MEDIASUBTYPE_MPG4 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_mpg4 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_MP41 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_mp41 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DIV1 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_div1 },

  { &MEDIATYPE_Video, &MEDIASUBTYPE_MP42 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_mp42 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DIV2 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_div2 },

  { &MEDIATYPE_Video, &MEDIASUBTYPE_MP43 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_mp43 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DIV3 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_div3 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_MPG3 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_mpg3 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DIV4 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_div4 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DIV5 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_div5 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DIV6 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_div6 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DVX3 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_dvx3 },

  // Flash
  { &MEDIATYPE_Video, &MEDIASUBTYPE_FLV1 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_flv1 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_VP60 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_vp60 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_VP61 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_vp61 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_VP62 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_vp62 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_VP6A },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_vp6a },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_VP6F },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_vp6f },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_FLV4 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_flv4 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_FSV1 },

  // Real
  { &MEDIATYPE_Video, &MEDIASUBTYPE_RV10 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_RV20 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_RV30 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_RV40 },

  // DV Video
  { &MEDIATYPE_Video, &MEDIASUBTYPE_dvsd },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DVSD },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_CDVH },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_dv25 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DV25 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_dv50 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DV50 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DVCP },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DV5P },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DVPP },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DVC  },

  // Misc Formats
  { &MEDIATYPE_Video, &MEDIASUBTYPE_SVQ1 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_SVQ3 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_H261 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_h261 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_H263 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_h263 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_S263 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_s263 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_THEORA },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_theora },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_TSCC },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_IV50 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_IV41 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_IV31 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_IV32 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_FPS1 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_HuffYUV },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_Lagarith },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_CVID },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_QTRle },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_VP30 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_VP31 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_CSCD },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_QPEG },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_QP10 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_QP11 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_MSZH },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_ZLIB },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_QTRpza },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_PNG  },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_PCM  }, // Yeah, PCM. Its the same FourCC as used by MS-RLE
  { &MEDIATYPE_Video, &MEDIASUBTYPE_apch },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_apcn },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_apcs },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_apco },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_ap4h },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_ULRA },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_ULRG },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_ULY0 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_ULY2 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_AMVV },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_AMVF },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DiracVideo },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_DRAC },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_AVdn },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_CRAM },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_MSVC },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_WHAM },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_8BPS },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_LOCO },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_ZMBV },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_VCR1 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_AASC },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_SNOW },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_FFV1 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_FFVH },

  // Game Formats
  { &MEDIATYPE_Video, &MEDIASUBTYPE_BIKI },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_BIKB },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_SMK2 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_SMK4 },

  // Special raw formats
  { &MEDIATYPE_Video, &MEDIASUBTYPE_v210 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_v410 },
};
const int CLAVVideo::sudPinTypesInCount = countof(CLAVVideo::sudPinTypesIn);

// Define Output Media Types
const AMOVIESETUP_MEDIATYPE CLAVVideo::sudPinTypesOut[] = {
  { &MEDIATYPE_Video, &MEDIASUBTYPE_YV12 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_NV12 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_YUY2 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_UYVY },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_RGB32 },
  { &MEDIATYPE_Video, &MEDIASUBTYPE_RGB24 },
};
const int CLAVVideo::sudPinTypesOutCount = countof(CLAVVideo::sudPinTypesOut);

// Crawl the lavc_video_codecs array for the proper codec
AVCodecID FindCodecId(const CMediaType *mt)
{
  for (int i=0; i<countof(lavc_video_codecs); ++i) {
    if (mt->subtype == *lavc_video_codecs[i].clsMinorType) {
      return lavc_video_codecs[i].nFFCodec;
    }
  }
  return AV_CODEC_ID_NONE;
}

// Strings will be filled in eventually.
// AV_CODEC_ID_NONE means there is some special handling going on.
// Order is Important, has to be the same as the CC Enum
// Also, the order is used for storage in the Registry
static codec_config_t m_codec_config[] = {
  { 1, { AV_CODEC_ID_H264 }},                                                // Codec_H264
  { 1, { AV_CODEC_ID_VC1 }},                                                 // Codec_VC1
  { 1, { AV_CODEC_ID_MPEG1VIDEO }, "mpeg1"},                                 // Codec_MPEG1
  { 1, { AV_CODEC_ID_MPEG2VIDEO }, "mpeg2"},                                 // Codec_MPEG2
  { 1, { AV_CODEC_ID_MPEG4 }},                                               // Codec_MPEG4
  { 3, { AV_CODEC_ID_MSMPEG4V1, AV_CODEC_ID_MSMPEG4V2, AV_CODEC_ID_MSMPEG4V3 }, "msmpeg4", "MS-MPEG-4 (DIVX3)" },   // Codec_MSMPEG4
  { 1, { AV_CODEC_ID_VP8 }},                                                 // Codec_VP8
  { 1, { AV_CODEC_ID_WMV3 }},                                                // Codec_WMV3
  { 2, { AV_CODEC_ID_WMV1, AV_CODEC_ID_WMV2 }, "wmv12", "Windows Media Video 7/8" },  // Codec_WMV12
  { 3, { AV_CODEC_ID_MJPEG, AV_CODEC_ID_MJPEGB, AV_CODEC_ID_AMV }},                // Codec_MJPEG
  { 2, { AV_CODEC_ID_THEORA, AV_CODEC_ID_VP3 }},                                // Codec_Theora
  { 2, { AV_CODEC_ID_FLV1, AV_CODEC_ID_FLASHSV }, "flash", "Flash Video (FLV1, FSV1)"}, // Codec_FLV1
  { 3, { AV_CODEC_ID_VP6, AV_CODEC_ID_VP6A, AV_CODEC_ID_VP6F }},                   // Codec_VP6
  { 2, { AV_CODEC_ID_SVQ1, AV_CODEC_ID_SVQ3 }, "svq", "SVQ 1 / SVQ 3"},         // Codec_SVQ
  { 1, { AV_CODEC_ID_H261 }},                                                // Codec_H261
  { 1, { AV_CODEC_ID_H263 }},                                                // Codec_H263
  { 3, { AV_CODEC_ID_INDEO3, AV_CODEC_ID_INDEO4, AV_CODEC_ID_INDEO5 }, "indeo", "Intel Indeo 3/4/5"}, // Codec_Indeo
  { 1, { AV_CODEC_ID_TSCC }},                                                // Codec_TSCC
  { 1, { AV_CODEC_ID_FRAPS }},                                               // Codec_Fraps
  { 2, { AV_CODEC_ID_HUFFYUV, AV_CODEC_ID_FFVHUFF }},                           // Codec_HuffYUV
  { 1, { AV_CODEC_ID_QTRLE }},                                               // Codec_QTRle
  { 1, { AV_CODEC_ID_DVVIDEO }},                                             // Codec_DV
  { 1, { AV_CODEC_ID_BINKVIDEO }, "bink"},                                   // Codec_Bink
  { 1, { AV_CODEC_ID_SMACKVIDEO }},                                          // Codec_Smacker
  { 2, { AV_CODEC_ID_RV10, AV_CODEC_ID_RV20 }, "rv12", "RealVideo 1/2" },       // Codev_RV12
  { 2, { AV_CODEC_ID_RV30, AV_CODEC_ID_RV40 }, "rv34", "RealVideo 3/4" },       // Codec_RV34
  { 1, { AV_CODEC_ID_LAGARITH }},                                            // Codec_Lagarith
  { 1, { AV_CODEC_ID_CINEPAK }},                                             // Codec_Cinepak
  { 1, { AV_CODEC_ID_CSCD }},                                                // Codec_Camstudio
  { 1, { AV_CODEC_ID_QPEG }},                                                // Codec_QPEG
  { 2, { AV_CODEC_ID_ZLIB, AV_CODEC_ID_MSZH }, "zlib", "ZLIB/MSZH lossless" },  // Codec_ZLIB
  { 1, { AV_CODEC_ID_RPZA }},                                                // Codec_QTRpza
  { 1, { AV_CODEC_ID_PNG }},                                                 // Codec_PNG
  { 2, { AV_CODEC_ID_MSRLE, AV_CODEC_ID_AASC }},                                // Codec_MSRLE
  { 1, { AV_CODEC_ID_PRORES }, "prores", "ProRes" },                         // Codec_ProRes
  { 1, { AV_CODEC_ID_UTVIDEO }},                                             // Codec_UtVideo
  { 1, { AV_CODEC_ID_DIRAC }},                                               // Codec_Dirac
  { 1, { AV_CODEC_ID_DNXHD }},                                               // Codec_DNxHD
  { 1, { AV_CODEC_ID_MSVIDEO1 }},                                            // Codec_MSVideo1
  { 1, { AV_CODEC_ID_8BPS }},                                                // Codec_8BPS
  { 1, { AV_CODEC_ID_LOCO }},                                                // Codec_LOCO
  { 1, { AV_CODEC_ID_ZMBV }},                                                // Codec_ZMBV
  { 1, { AV_CODEC_ID_VCR1 }},                                                // Codec_VCR1
  { 1, { AV_CODEC_ID_SNOW }},                                                // Codec_Snow
  { 1, { AV_CODEC_ID_FFV1 }},                                                // Codec_FFV1
  { 2, { AV_CODEC_ID_V210, AV_CODEC_ID_V410 }, "v210/v410", "v210/v410 uncompressed"}, // Codec_v210
};

const codec_config_t *get_codec_config(LAVVideoCodec codec)
{
  codec_config_t *config = &m_codec_config[codec];

  AVCodec *avcodec = avcodec_find_decoder(config->codecs[0]);
  if (avcodec) {
    if (!config->name) {
      config->name = avcodec->name;
    }

    if (!config->description) {
      config->description = avcodec->long_name;
    }
  }

  return &m_codec_config[codec];
}

int flip_plane(BYTE *buffer, int stride, int height)
{
  BYTE *line_buffer = (BYTE *)av_malloc(stride);
  BYTE *cur_front   = buffer;
  BYTE *cur_back    = buffer + (stride * (height - 1));
  height /= 2;
  for (int i = 0; i < height; i++) {
    memcpy(line_buffer, cur_front, stride);
    memcpy(cur_front, cur_back, stride);
    memcpy(cur_back, line_buffer, stride);
    cur_front += stride;
    cur_back -= stride;
  }
  av_freep(&line_buffer);
  return 0;
}

void fillDXVAExtFormat(DXVA2_ExtendedFormat &fmt, int range, int primaries, int matrix, int transfer)
{
  fmt.value = 0;

  if (range != -1)
      fmt.NominalRange = range ? DXVA2_NominalRange_0_255 : DXVA2_NominalRange_16_235;

  // Color Primaries
  switch(primaries) {
  case AVCOL_PRI_BT709:
    fmt.VideoPrimaries = DXVA2_VideoPrimaries_BT709;
    break;
  case AVCOL_PRI_BT470M:
    fmt.VideoPrimaries = DXVA2_VideoPrimaries_BT470_2_SysM;
    break;
  case AVCOL_PRI_BT470BG:
    fmt.VideoPrimaries = DXVA2_VideoPrimaries_BT470_2_SysBG;
    break;
  case AVCOL_PRI_SMPTE170M:
    fmt.VideoPrimaries = DXVA2_VideoPrimaries_SMPTE170M;
    break;
  case AVCOL_PRI_SMPTE240M:
    fmt.VideoPrimaries = DXVA2_VideoPrimaries_SMPTE240M;
    break;
  }

  // Color Space / Transfer Matrix
  switch (matrix) {
  case AVCOL_SPC_BT709:
    fmt.VideoTransferMatrix = DXVA2_VideoTransferMatrix_BT709;
    break;
  case AVCOL_SPC_FCC:
    fmt.VideoTransferMatrix = (DXVA2_VideoTransferMatrix)6;
    break;
  case AVCOL_SPC_BT470BG:
  case AVCOL_SPC_SMPTE170M:
    fmt.VideoTransferMatrix = DXVA2_VideoTransferMatrix_BT601;
    break;
  case AVCOL_SPC_SMPTE240M:
    fmt.VideoTransferMatrix = DXVA2_VideoTransferMatrix_SMPTE240M;
    break;
  case AVCOL_SPC_YCGCO:
    fmt.VideoTransferMatrix = (DXVA2_VideoTransferMatrix)7;
    break;
  }

  // Color Transfer Function
  switch(transfer) {
  case AVCOL_TRC_BT709:
    fmt.VideoTransferFunction = DXVA2_VideoTransFunc_709;
    break;
  case AVCOL_TRC_GAMMA22:
    fmt.VideoTransferFunction = DXVA2_VideoTransFunc_22;
    break;
  case AVCOL_TRC_GAMMA28:
    fmt.VideoTransferFunction = DXVA2_VideoTransFunc_28;
    break;
  case AVCOL_TRC_SMPTE240M:
    fmt.VideoTransferFunction = DXVA2_VideoTransFunc_240M;
    break;
  }
}
