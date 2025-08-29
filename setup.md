How to be able to build ts. Thanks A LOT to https://github.com/aws/amazon-chime-sdk-cpp/tree/main/chime-sdk-signaling-cpp/demo/cli
### Please use a container, I use distrobox and debian so that's how I'm developing this. IG it should work with others but idk


## Setup commands to setup the env vars when you have already done the install part
```sh
export CHIME_SDK_DEMO_DIRECTORY=$(pwd) # set CHIME_SDK_DEMO_DIRECTORY to the root of this repo
export PATH=$CHIME_SDK_DEMO_DIRECTORY/webrtc-build/depot_tools:$PATH # Add depot tools to path

export BORING_SSL_LIB=$CHIME_SDK_DEMO_DIRECTORY/webrtc-build/webrtc/out/Default/obj/libwebrtc.a
export BORING_SSL_INCLUDE_DIR=$CHIME_SDK_DEMO_DIRECTORY/webrtc-build/webrtc/third_party/boringssl/src/include
```
And the build commands
```sh
cd $CHIME_SDK_DEMO_DIRECTORY/djhakkun # GO TO THE djhakkun dir
cmake -S . -B build -GNinja
cmake --build build
```

## Installation
### Fetch depot tools and libwebrtc
```sh
export CHIME_SDK_DEMO_DIRECTORY=$(pwd) # set CHIME_SDK_DEMO_DIRECTORY to the root of this repo

# create webrtc-build, fetch it and build it. You will need around 60GBs of free storage for this
mkdir webrtc-build
cd webrtc-build
git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git

# Do this so you don't get rate limited by the chromium git repo
git config http.postBuffer 524288000
git config http.maxRequestBuffer 100M

# more chromium stuff
export PATH=$CHIME_SDK_DEMO_DIRECTORY/webrtc-build/depot_tools:$PATH
fetch --nohooks webrtc

cd src 
git checkout -b M128 refs/remotes/branch-heads/6613
cd ..
gclient sync -D --force --reset --with_branch_heads
cd src
./build/install-build-deps.sh
```
### build libwebrtc

idk atp this is what the docs said
```sh
cd $CHIME_SDK_DEMO_DIRECTORY/webrtc-build/src

cat <<EOL >> BUILD.gn
rtc_static_library("webrtc_extras") {
  visibility = [ "//:default" ]
  sources = []
  complete_static_lib = true
  suppressed_configs += [ "//build/config/compiler:thin_archive" ]

  deps = [
    "api:enable_media_with_defaults",
    "modules/audio_device:test_audio_device_module",
  ]
}
EOL
```
actually build it and rename it to use it as a dependency
```sh
cd $CHIME_SDK_DEMO_DIRECTORY/webrtc-build/src

gn_args='target_os="linux" 
        rtc_use_h264=false
        rtc_include_tests=false 
        use_custom_libcxx=false
        rtc_enable_protobuf=false
        rtc_include_pulse_audio=false'
gn gen out/Default --args="${gn_args}"
ninja -C out/Default
ninja -C out/Default webrtc_extras
cd .. && mv src webrtc
```


### Download and build the aws chime sdk 
Now the actual thing for the actual library 
```sh
cd $CHIME_SDK_DEMO_DIRECTORY
git clone https://github.com/aws/amazon-chime-sdk-cpp.git
cd amazon-chime-sdk-cpp/chime-sdk-signaling-cpp

export BORING_SSL_LIB=$CHIME_SDK_DEMO_DIRECTORY/webrtc-build/webrtc/out/Default/obj/libwebrtc.a
export BORING_SSL_INCLUDE_DIR=$CHIME_SDK_DEMO_DIRECTORY/webrtc-build/webrtc/third_party/boringssl/src/include
cmake -S . -B build \
    -DLWS_OPENSSL_LIBRARIES=$BORING_SSL_LIB \
    -DLWS_OPENSSL_INCLUDE_DIRS=$BORING_SSL_INCLUDE_DIR \
    -DLWS_WITH_BORINGSSL=ON \
    -DLWS_HAVE_OPENSSL_STACK=OFF \
    -GNinja
cmake --build build
```