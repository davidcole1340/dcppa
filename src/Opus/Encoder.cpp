/**
 * dcppa - opus encoder
 * 
 * Author: David Cole
 */

#include "Encoder.hpp"

dcppa::Opus::Encoder::Encoder(std::string application, int sampleRate, int frameSize, int channels)
: frameSize(frameSize), channels(channels), sampleRate(sampleRate)
{
    int opusApplication = OPUS_APPLICATION_AUDIO;

    if (application == "voip") opusApplication = OPUS_APPLICATION_VOIP;
    else if (application == "lowdelay") opusApplication = OPUS_APPLICATION_RESTRICTED_LOWDELAY;

    int err;
    this->enc = opus_encoder_create(sampleRate, channels, opusApplication, &err);

    if (err != OPUS_OK) {
        throw std::runtime_error(opus_strerror(err));
    }

    this->maxBytes = this->frameSize * this->channels * 2;
}

void dcppa::Opus::Encoder::setBitrate(int bitrate)
{
    opus_encoder_ctl(this->enc, OPUS_SET_BITRATE(bitrate));
}

void dcppa::Opus::Encoder::encode(std::istream *input, std::ostream *output)
{
    opus_int16 *pcm = new opus_int16[this->frameSize * this->channels];
    opus_uint32 status;
    unsigned char *data = new unsigned char[this->maxBytes];

    while (! input->eof()) {
        input->read((char*) pcm, this->frameSize * this->channels);
        status = opus_encode(this->enc, pcm, this->frameSize, data, this->maxBytes);

        if (status < 0) {
            throw std::runtime_error(opus_strerror(status));
        }
        
        output->write((const char*) data, status);
    }
}

dcppa::Opus::Encoder::~Encoder()
{
    opus_encoder_destroy(this->enc);
}