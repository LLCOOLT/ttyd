#include <dolphin.h>
#include <dolphin/syn.h>
#include "fake_tgmath.h"

#include "__syn.h"

/**
 * Finds the wavetable data for a note: the region for the key from the channel's instrument,
 * then its articulation, sample and ADPCM entries. Returns 0 when the instrument has no region for the key.
 */
int __SYNGetWavetableData(SYNVOICE* voice) {
    u32 regionIndex;
    SYNSYNTH* synth;

    synth = voice->synth;
    regionIndex = synth->inst[voice->midiChannel]->keyRegion[voice->keyNum];
    if (regionIndex == 0xFFFF) {
        return 0;
    }
    voice->region = &synth->region[regionIndex];
    voice->art = &synth->art[voice->region->articulationIndex];
    voice->sample = &synth->sample[voice->region->sampleIndex];
    voice->adpcm = &synth->adpcm[voice->sample->adpcmIndex];
    return 1;
}
