#!/bin/bash

script_dir=$(cd $(dirname ${0});pwd)
path_to_repository=${script_dir}/../generalized_niederreiter_sequence
repository_name=$(basename ${path_to_repository})
path_to_repository_in_docker=/tmp/${REPOSITORY_NAME}

docker run -it --rm \
  --volume ${path_to_repository}:${path_to_repository_in_docker} \
  sphinx-breathe:alpine-1.6.3 \
  doxygen -g ${path_to_repository_in_docker}/Doxyfile
