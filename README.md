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
(cd emsdk && ./emsdk install 3.1.61)
(cd emsdk && ./emsdk activate 3.1.61)
source ./emsdk/emsdk_env.sh

# LibrosaCpp
git clone --depth=1 --branch main https://github.com/ewan-xu/LibrosaCpp

mkdir wasm
# -msimd128 does have slight positive performance impact (i.e. 16.7sec vs 16.5sec on a test case)
# -sSTACK_SIZE=24MB can handle 1h of 8000Hz PCM
# -sMALLOC=mimalloc doesnt seem to affect performance, but increases artifact size
em++ main.cpp -msimd128 -O3 \
	-sSTACK_SIZE=24MB -sINITIAL_MEMORY=25MB -sMAXIMUM_MEMORY=4gb -sALLOW_MEMORY_GROWTH=1 -sIMPORTED_MEMORY=1 \
	-sEXPORTED_FUNCTIONS=_malloc,_mfcc -sEXPORTED_RUNTIME_METHODS=ccall \
	-sMODULARIZE=1 -sEXPORT_NAME=createMFCC -sINVOKE_RUN=0 -sEXIT_RUNTIME=1 \
	-sWASM=1 -sENVIRONMENT=worker -o wasm/mfcc.js
```

## Usage

1. create sample `ffmpeg -i input.mp3 -ac 1 -ar 8000 -acodec pcm_s16le -f s16le output.raw`
2. run https://localhost/demo.html

## Alternatives

- https://github.com/miaobin/web-mfcc/
- https://github.com/meyda/meyda/blob/ecf256616d43292c82cbf96e60a91b19ca10eb64/src/extractors/mfcc.ts