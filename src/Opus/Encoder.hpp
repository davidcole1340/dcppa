/**
 * dcppa - opus encoder
 * 
 * Author: David Cole
 */

#ifndef OPUS_ENCODER_HPP
#define OPUS_ENCODER_HPP

#include <string>
#include <stdexcept>

extern "C" {
    #include <opus/opus.h>
}

namespace dcppa::Opus
{
    class Encoder
    {
    private:
        OpusEncoder *enc;

    public:
        Encoder(std::string application, int sampleRate, int frameSize, int channels);

        ~Encoder();
    };
}

#endif /* OPUS_ENCODER_HPP */