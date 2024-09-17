#!/bin/bash -eu

cd "$SRC/cjsonobject"
mkdir -p "fuzz/build"
cmake -G Ninja \
      -S fuzz \
      -B fuzz/build
cmake --build fuzz/build

$CXX $CXXFLAGS \
    -fsanitize=fuzzer,address \
    -I. \
    ./CJsonObject.cpp \
    ./cJSON.c \
    ./fuzz/fuzzy_target.cpp \
    -o "$OUT/fuzzy_target" \
    $LIB_FUZZING_ENGINE \
    ./fuzz/build/libcjsonobject.a
