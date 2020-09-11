/**
 * dcppa - opus encoder
 * 
 * Author: David Cole
 */

#include <iostream>
#include <fstream>

#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>
#include <cxxopts.hpp>

extern "C" {
    #include <opus/opus.h>
}

#include "src/Opus/Encoder.hpp"

cxxopts::ParseResult parseOptions(int argc, const char** argv)
{
    cxxopts::Options options("dcppa", "opus encoder - dca format");

    try {
        options.add_options()
            ("h,help", "prints usage")
            ("a,application", "audio application - voip, audio or lowdelay", cxxopts::value<std::string>()->default_value("audio"))
            ("e,encodingrate", "audio encoding rate in kb/s, range 8-128", cxxopts::value<int>()->default_value("64"))
            ("r,bitrate", "audio sampling rate in b/s", cxxopts::value<int>()->default_value("48000"))
            ("s,framesize", "audio frame size - 960, 1920, 2880", cxxopts::value<int>()->default_value("960"))
            ("c,channels", "number of channels to encode", cxxopts::value<int>()->default_value("2"))
            ("f,coverformat", "format the cover art will be encoded with", cxxopts::value<std::string>()->default_value("jpeg"))
            ("raw", "raw opus data without metadata")
            ("vol", "volume, range of 0-255", cxxopts::value<int>()->default_value("255"))
            ("i,input", "input file, default stdin", cxxopts::value<std::string>()->default_value("/dev/stdin"))
            ("o,output", "output file, default stdout", cxxopts::value<std::string>()->default_value("/dev/stdout"))
        ;

        cxxopts::ParseResult result = options.parse(argc, argv);

        // Print help
        if (result.count("help")) std::cout << options.help() << std::endl;
        
        // Set up logger - if verbose is not set, log at err unless specified in argv.
        spdlog::cfg::load_env_levels();

        return result;
    } catch (const cxxopts::OptionException &e) {
        spdlog::error("error parsing options: {}", e.what());
        exit(1);
    }
}

int main(int argc, const char** argv)
{
    cxxopts::ParseResult options = parseOptions(argc, argv);

    try {
        dcppa::Opus::Encoder *encoder = new dcppa::Opus::Encoder(
            options["application"].as<std::string>(),
            options["bitrate"].as<int>(),
            options["framesize"].as<int>(),
            options["channels"].as<int>()
        );
    } catch (const char* err) {
        spdlog::error("error creating opus encoder: {}", err);
    }

    spdlog::debug("opening input file {} and output file {}",
                  options["input"].as<std::string>(),
                  options["output"].as<std::string>());

    std::ifstream input(options["input"].as<std::string>(), std::ios::binary);
    std::ofstream output(options["output"].as<std::string>(), std::ios::binary);

    if (! input.is_open()) {
        spdlog::error("unable to open input file");
        exit(1);
    }

    if (! output.is_open()) {
        spdlog::error("unable to open output file");
        exit(1);
    }

    return 0;
}