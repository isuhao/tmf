/*
 *
 *  Tiny Multimedia Framework
 *  Copyright (C) 2014 Arash Shafiei
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <tools/VideoEncoder.h>

VideoEncoder::VideoEncoder() {
	codec_ctx = 0;
	video_outbuf_size = 2000000;
	video_outbuf = (uint8_t*) av_malloc(video_outbuf_size);


}

int VideoEncoder::init(string codec_name, int width, int height, int bitrate, int framerate) {

	AVCodec * codec = avcodec_find_encoder_by_name(codec_name.c_str());
	if (codec == NULL) {
		cout << "Output video codec " << codec_name << " not found\n";
		return -1;
	}

	codec_ctx = avcodec_alloc_context3(codec);

	codec_ctx->codec_id = codec->id;
	codec_ctx->codec_type = AVMEDIA_TYPE_VIDEO;
	codec_ctx->bit_rate = bitrate;
	codec_ctx->width = width;
	codec_ctx->height = height;
	//codec_ctx->sample_aspect_ratio.num = width;
	//codec_ctx->sample_aspect_ratio.den = height;

	codec_ctx->time_base = AVRational { 1, framerate };

	//codec_ctx->time_base.den = gop_size ? gop_size : framerate;

	//if (use_source_timing) {
	//for avcodec to do rate allocation, we need to have ctx->timebase == 1/framerate
	//	codec_ctx->time_base.den = time_base.den;
	//	codec_ctx->time_base.num = time_base.num * time_base.den / framerate;
	//}

	codec_ctx->pix_fmt = PIX_FMT_YUV420P;
	codec_ctx->gop_size = framerate;
	codec_ctx->max_b_frames = 3;

	//av_opt_set(codec_ctx->priv_data, "preset", "ultrafast", 0);
	//av_opt_set(codec_ctx->priv_data, "tune", "zerolatency", 0);
	//codec_ctx->max_b_frames = 0;

	//the global header gives access to the extradata (SPS/PPS)
	codec_ctx->flags |= CODEC_FLAG_GLOBAL_HEADER;

	//vstream_idx = 0;

	/* open the video codec - options are passed thru  codec_ctx->priv_data */
	if (avcodec_open2(codec_ctx, codec, NULL) < 0) {
		cout << "Cannot open output video codec\n";
		return -1;
	}

	//rep_id = filename;
	return 0;
}

int VideoEncoder::encode(RawFrame * rawFrame, EncodedFrame * encodedFrame) {

	int ret;
	int out_size;

	AVFrame * vframe = rawFrame->getFrame();

	vframe->pts = rawFrame->number;
	//encodedFrame->number = rawFrame->number;

	/* Encoding video */

	//int got_packet = 0;

	av_init_packet(encodedFrame->pkt);

	//encodedFrame->pkt->pts = encodedFrame->pkt->dts = vframe->pkt_dts =
	//		vframe->pkt_pts = vframe->pts;

	//ret = avcodec_encode_video2(codec_ctx, encodedFrame->pkt, vframe,
	//		&got_packet);

	out_size = avcodec_encode_video(codec_ctx, video_outbuf, video_outbuf_size,
			vframe);

	if (out_size > 0) {
		av_init_packet(encodedFrame->pkt);

		encodedFrame->pkt->data = video_outbuf;
		encodedFrame->pkt->size = out_size;
		ret = out_size;
	} else {
		ret = 0;
	}

	/*
	 if (ret < 0) {
	 cout << "Error occurred while encoding video frame.\n";
	 return -1;
	 }

	 if (got_packet) {
	 codec_ctx->coded_frame->pts = codec_ctx->coded_frame->pkt_pts =
	 encodedFrame->pkt->pts;
	 codec_ctx->coded_frame->pkt_dts = encodedFrame->pkt->dts;
	 codec_ctx->coded_frame->key_frame =
	 (encodedFrame->pkt->flags & AV_PKT_FLAG_KEY) ? 1 : 0;
	 }
	 */

	return ret;
}

VideoEncoder::~VideoEncoder() {
	avcodec_close(codec_ctx);
	av_free(codec_ctx);
}

