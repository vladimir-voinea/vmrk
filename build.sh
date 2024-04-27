#!/usr/bin/env sh

cmake -S . -B out
cmake --build out --parallel `nproc`
