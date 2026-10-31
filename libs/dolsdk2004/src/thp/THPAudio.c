#include <dolphin/thp.h>

#ifdef VERSION_G8MP01
/**
 * Decodes one audio frame of a THP movie (4-bit ADPCM,
 * left and right channels with their own coefficients
 * and history in the frame header) into 16-bit PCM in audioBuffer, returning the number of samples per channel.
 * With flag 1 the channels are written one after the other (right, then left); otherwise they are interleaved.
 * A mono frame is copied to both channels.
 * This copy (the PAL release) rounds each sample by adding 0x8000 before taking the high half.
 */
u32 THPAudioDecode(s16* audioBuffer, u8* audioFrame, s32 flag)
{
	THPAudioRecordHeader* header;
	THPAudioDecodeInfo decInfo;
	u8 *left, *right;
	s16 *decLeftPtr, *decRightPtr;
	s16 yn1, yn2;
	s32 i;
	s32 step;
	s32 sample;
	s64 yn;

	if (audioBuffer == NULL || audioFrame == NULL) {
		return 0;
	}

	header = (THPAudioRecordHeader*)audioFrame;
	left   = audioFrame + sizeof(THPAudioRecordHeader);
	right  = left + header->offsetNextChannel;

	if (flag == 1) {
		decRightPtr = audioBuffer;
		decLeftPtr  = audioBuffer + header->sampleSize;
		step        = 1;
	} else {
		decRightPtr = audioBuffer;
		decLeftPtr  = audioBuffer + 1;
		step        = 2;
	}

	if (header->offsetNextChannel == 0) {
		__THPAudioInitialize(&decInfo, left);

		yn1 = header->lYn1;
		yn2 = header->lYn2;

		for (i = 0; i < header->sampleSize; i++) {
			sample = __THPAudioGetNewSample(&decInfo);
			yn     = header->lCoef[decInfo.predictor][1] * yn2;
			yn += header->lCoef[decInfo.predictor][0] * yn1;
			yn += (sample << decInfo.scale) << 11;
			yn <<= 5;
			yn += 0x8000;

			if (yn > 2147483647LL) {
				yn = 2147483647LL;
			}

			if (yn < -2147483648LL) {
				yn = -2147483648LL;
			}

			*decLeftPtr = (s16)(yn >> 16);
			decLeftPtr += step;
			*decRightPtr = (s16)(yn >> 16);
			decRightPtr += step;
			yn2 = yn1;
			yn1 = (s16)(yn >> 16);
		}
	} else {
		__THPAudioInitialize(&decInfo, left);

		yn1 = header->lYn1;
		yn2 = header->lYn2;

		for (i = 0; i < header->sampleSize; i++) {
			sample = __THPAudioGetNewSample(&decInfo);
			yn     = header->lCoef[decInfo.predictor][1] * yn2;
			yn += header->lCoef[decInfo.predictor][0] * yn1;
			yn += (sample << decInfo.scale) << 11;
			yn <<= 5;
			yn += 0x8000;

			if (yn > 2147483647LL) {
				yn = 2147483647LL;
			}

			if (yn < -2147483648LL) {
				yn = -2147483648LL;
			}

			*decLeftPtr = (s16)(yn >> 16);
			decLeftPtr += step;
			yn2 = yn1;
			yn1 = (s16)(yn >> 16);
		}

		__THPAudioInitialize(&decInfo, right);

		yn1 = header->rYn1;
		yn2 = header->rYn2;

		for (i = 0; i < header->sampleSize; i++) {
			sample = __THPAudioGetNewSample(&decInfo);
			yn     = header->rCoef[decInfo.predictor][1] * yn2;
			yn += header->rCoef[decInfo.predictor][0] * yn1;
			yn += (sample << decInfo.scale) << 11;
			yn <<= 5;
			yn += 0x8000;

			if (yn > 2147483647LL) {
				yn = 2147483647LL;
			}

			if (yn < -2147483648LL) {
				yn = -2147483648LL;
			}

			*decRightPtr = (s16)(yn >> 16);
			decRightPtr += step;
			yn2 = yn1;
			yn1 = (s16)(yn >> 16);
		}
	}

	return header->sampleSize;
}
#else
/**
 * Decodes one audio frame of a THP movie (4-bit ADPCM,
 * left and right channels with their own coefficients
 * and history in the frame header) into 16-bit PCM in audioBuffer, returning the number of samples per channel.
 * With flag 1 the channels are written one after the other (right, then left); otherwise they are interleaved.
 * A mono frame is copied to both channels.
 * This copy (all releases except PAL) rounds to the nearest 16-bit value with ties going to the even value.
 */
u32 THPAudioDecode(s16* audioBuffer, u8* audioFrame, s32 flag)
{
	THPAudioRecordHeader* header;
	THPAudioDecodeInfo decInfo;
	u8 *left, *right;
	s16 *decLeftPtr, *decRightPtr;
	s16 yn1, yn2;
	s32 i;
	s32 step;
	s32 sample;
	s64 yn;

	if (audioBuffer == NULL || audioFrame == NULL) {
		return 0;
	}

	header = (THPAudioRecordHeader*)audioFrame;
	left   = audioFrame + sizeof(THPAudioRecordHeader);
	right  = left + header->offsetNextChannel;

	if (flag == 1) {
		decRightPtr = audioBuffer;
		decLeftPtr  = audioBuffer + header->sampleSize;
		step        = 1;
	} else {
		decRightPtr = audioBuffer;
		decLeftPtr  = audioBuffer + 1;
		step        = 2;
	}

	if (header->offsetNextChannel == 0) {
		__THPAudioInitialize(&decInfo, left);

		yn1 = header->lYn1;
		yn2 = header->lYn2;

		for (i = 0; i < header->sampleSize; i++) {
			sample = __THPAudioGetNewSample(&decInfo);
			yn     = header->lCoef[decInfo.predictor][1] * yn2;
			yn += header->lCoef[decInfo.predictor][0] * yn1;
			yn += (sample << decInfo.scale) << 11;
			yn <<= 5;

			if ((u16)(yn & 0xffff) > 0x8000) {
				yn += 0x10000;
			} else if ((u16)(yn & 0xffff) == 0x8000) {
				if ((yn & 0x10000))
					yn += 0x10000;
			}

			if (yn > 2147483647LL) {
				yn = 2147483647LL;
			}

			if (yn < -2147483648LL) {
				yn = -2147483648LL;
			}

			*decLeftPtr = (s16)(yn >> 16);
			decLeftPtr += step;
			*decRightPtr = (s16)(yn >> 16);
			decRightPtr += step;
			yn2 = yn1;
			yn1 = (s16)(yn >> 16);
		}
	} else {
		__THPAudioInitialize(&decInfo, left);

		yn1 = header->lYn1;
		yn2 = header->lYn2;

		for (i = 0; i < header->sampleSize; i++) {
			sample = __THPAudioGetNewSample(&decInfo);
			yn     = header->lCoef[decInfo.predictor][1] * yn2;
			yn += header->lCoef[decInfo.predictor][0] * yn1;
			yn += (sample << decInfo.scale) << 11;
			yn <<= 5;
			if ((u16)(yn & 0xffff) > 0x8000) {
				yn += 0x10000;
			} else {
				if ((u16)(yn & 0xffff) == 0x8000) {
					if ((yn & 0x10000))
						yn += 0x10000;
				}
			}

			if (yn > 2147483647LL) {
				yn = 2147483647LL;
			}

			if (yn < -2147483648LL) {
				yn = -2147483648LL;
			}

			*decLeftPtr = (s16)(yn >> 16);
			decLeftPtr += step;
			yn2 = yn1;
			yn1 = (s16)(yn >> 16);
		}

		__THPAudioInitialize(&decInfo, right);

		yn1 = header->rYn1;
		yn2 = header->rYn2;

		for (i = 0; i < header->sampleSize; i++) {
			sample = __THPAudioGetNewSample(&decInfo);
			yn     = header->rCoef[decInfo.predictor][1] * yn2;
			yn += header->rCoef[decInfo.predictor][0] * yn1;
			yn += (sample << decInfo.scale) << 11;
			yn <<= 5;

			if ((u16)(yn & 0xffff) > 0x8000) {
				yn += 0x10000;
			} else {
				if ((u16)(yn & 0xffff) == 0x8000) {
					if ((yn & 0x10000))
						yn += 0x10000;
				}
			}

			if (yn > 2147483647LL) {
				yn = 2147483647LL;
			}

			if (yn < -2147483648LL) {
				yn = -2147483648LL;
			}

			*decRightPtr = (s16)(yn >> 16);
			decRightPtr += step;
			yn2 = yn1;
			yn1 = (s16)(yn >> 16);
		}
	}

	return header->sampleSize;
}
#endif

/**
 * Returns the next signed 4-bit ADPCM nibble of the stream,
 * reading a new predictor and scale byte at the start of each 8-byte frame.
 */
static s32 __THPAudioGetNewSample(THPAudioDecodeInfo* info)
{
	s32 sample;

	if (!(info->offsetNibbles & 0x0f)) {
		info->predictor = (u8)((*(info->encodeData) & 0x70) >> 4);
		info->scale     = (u8)((*(info->encodeData) & 0xF));
		info->encodeData++;
		info->offsetNibbles += 2;
	}

	if (info->offsetNibbles & 0x1) {
		sample = (s32)((*(info->encodeData) & 0xF) << 28) >> 28;
		info->encodeData++;
	} else {
		sample = (s32)((*(info->encodeData) & 0xF0) << 24) >> 28;
	}

	info->offsetNibbles++;
	return sample;
}

/**
 * Starts decoding one channel at ptr: reads the first frame's predictor and scale byte
 * and positions the nibble reader after it.
 */
static void __THPAudioInitialize(THPAudioDecodeInfo* info, u8* ptr)
{
	info->encodeData    = ptr;
	info->offsetNibbles = 2;
	info->predictor     = (u8)((*(info->encodeData) & 0x70) >> 4);
	info->scale         = (u8)((*(info->encodeData) & 0xF));
	info->encodeData++;
}
