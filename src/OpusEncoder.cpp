#include "OpusEncoder.hpp"

dcppa::Encoder::Encoder(int application, int sampleRate, int frameSize, int channels)
{
    int err;
    this->enc = opus_encoder_create(sampleRate, channels, application, &err);

    if (err != OPUS_OK) {
        throw opus_strerror(err);
    }
}

dcppa::Encoder::~Encoder()
{
    opus_encoder_destroy(this->enc);
}