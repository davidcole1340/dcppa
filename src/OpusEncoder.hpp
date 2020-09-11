#ifndef OPUS_ENCODER_HPP
#define OPUS_ENCODER_HPP

extern "C" {
    #include <opus/opus.h>
}

namespace dcppa
{
    class Encoder
    {
    private:
        OpusEncoder *enc;

        int application;
        int sampleRate;
        int frameSize;
        int channels;

    public:
        Encoder(int application, int sampleRate, int frameSize, int channels);

        ~Encoder();
    };
}

#endif /* OPUS_ENCODER_HPP */