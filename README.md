# dcppa

Implementation of the [dca](https://github.com/bwmarrin/dca) audio format in C++.

## Why?

Using this project as a way of expanding my knowledge of C++.

## Building

```sh
git clone https://github.com/davidcole1340/dcppa.git && cd dcppa
mkdir build && cd build
cmake .. && cmake --build .
./dcppa --help
```

### Requirements

- CMake >=3.1
- [libopus](https://opus-codec.org/)
- [spdlog](https://github.com/gabime/spdlog)
- [cxxopts](https://github.com/jarro2783/cxxopts)

## License

[GPLv3](LICENSE.md)

## Credits

- David Cole
- [bwmarrin](https://github.com/bwmarrin) (DCA)