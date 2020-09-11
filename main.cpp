#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>
#include <cxxopts.hpp>

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
            ("f,coverformat", "format the cover art will be encoded with", cxxopts::value<std::string>()->default_value("jpeg"))
            ("decode", "running in decode mode?")
            ("raw", "raw opus data without metadata")
            ("vol", "volume, range of 0-255", cxxopts::value<int>()->default_value("255"));

        cxxopts::ParseResult result = options.parse(argc, argv);

        // Print help
        if (result.count("help")) std::cout << options.help() << std::endl;
        
        // Set up logger - if verbose is not set, log at err unless specified in argv.
        spdlog::cfg::load_env_levels();

        spdlog::info("test");

        return result;
    } catch (const cxxopts::OptionException &e) {
        spdlog::error("error parsing options: {}", e.what());
        exit(1);
    }
}

int main(int argc, const char** argv)
{
    cxxopts::ParseResult options = parseOptions(argc, argv);

    return 0;
}