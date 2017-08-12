#!/bin/bash

path_to_repository=$(cd $(dirname ${0});cd ..;pwd)

filelist=$(find ${path_to_repository}/gns -name '*.cc' -or -name '*.h')
for filename in ${filelist}; do
  clang-format -i ${filename}
done
