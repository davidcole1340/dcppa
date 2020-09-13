/**
 * dcppa - opus encoder
 * 
 * Author: David Cole
 */

#ifndef OPUS_ENCODER_HPP
#define OPUS_ENCODER_HPP

#include <string>
#include <stdexcept>
#include <istream>
#include <ostream>
#include <fstream>
#include <stdint.h>

#include <iostream>

extern "C" {
    #include <opus/opus.h>
}

namespace dcppa::Opus
{
    class Encoder
    {
    private:
        OpusEncoder *enc;
        int frameSize;
        int channels;
        int sampleRate;
        int maxBytes;

    public:
        Encoder(std::string application, int sampleRate, int frameSize, int channels);

        void setBitrate(int bitrate);
        void encode(std::istream *input, std::ostream *output);

        ~Encoder();
    };
}

#endif /* OPUS_ENCODER_HPP */