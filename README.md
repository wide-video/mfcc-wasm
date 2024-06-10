# mfcc-wasm

## Build

```sh
docker run -it -v $(pwd):/mfcc-wasm -w /mfcc-wasm debian:12.5
#docker ps -q -l              # find container ID (or discover via Docker desktop)
#docker start a34faaf8d614    # restart in the background
#docker attach a34faaf8d614   # reattach the terminal & stdin

apt-get update
apt-get install -y git python3.11 xz-utils
ln -sf /usr/bin/python3.11 /usr/bin/python

# Emscripten
git clone --depth=1 --branch main https://github.com/emscripten-core/emsdk/
(cd emsdk && ./emsdk install 3.1.47)
(cd emsdk && ./emsdk activate 3.1.47)
source ./emsdk/emsdk_env.sh

# LibrosaCpp
git clone --depth=1 --branch main https://github.com/ewan-xu/LibrosaCpp

mkdir wasm
em++ main.cpp -s WASM=1 -s EXPORTED_FUNCTIONS=_malloc,_mfcc,_free -s EXPORTED_RUNTIME_METHODS=ccall -s STACK_SIZE=1MB -s MODULARIZE=1 -s EXPORT_NAME=createMFCC -s INVOKE_RUN=0 -s EXIT_RUNTIME=1 -s MAXIMUM_MEMORY=4gb -s IMPORTED_MEMORY=1 -s ALLOW_MEMORY_GROWTH=1 -s ENVIRONMENT=web -O3 -o wasm/mfcc.js
```

## Usage

1. create sample `ffmpeg -i input.mp3 -ac 1 -ar 8000 -acodec pcm_s16le -f s16le output.raw `
2. run https://localhost/demo.html

## Alternatives

- https://github.com/miaobin/web-mfcc/
- https://github.com/meyda/meyda/blob/ecf256616d43292c82cbf96e60a91b19ca10eb64/src/extractors/mfcc.ts