/**
 * dcppa - opus encoder
 * 
 * Author: David Cole
 */

#include "Encoder.hpp"

dcppa::Opus::Encoder::Encoder(std::string application, int sampleRate, int frameSize, int channels)
{
    int opusApplication = OPUS_APPLICATION_AUDIO;

    if (application == "voip") opusApplication = OPUS_APPLICATION_VOIP;
    else if (application == "lowdelay") opusApplication = OPUS_APPLICATION_RESTRICTED_LOWDELAY;

    int err;
    this->enc = opus_encoder_create(sampleRate, channels, opusApplication, &err);

    if (err != OPUS_OK) {
        throw std::runtime_error(opus_strerror(err));
    }
}

dcppa::Opus::Encoder::~Encoder()
{
    opus_encoder_destroy(this->enc);
}