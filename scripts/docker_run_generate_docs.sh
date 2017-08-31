#!/bin/bash

set -x

parent_dir=$(cd $(dirname ${0});cd ..;pwd)
path_to_repository=${parent_dir}
repository_name=$(basename ${parent_dir})
path_to_repository_in_docker=/tmp/${repository_name}

command=$(cat << EOS
cd ${path_to_repository_in_docker};
doxygen ${path_to_repository_in_docker}/Doxyfile;
sphinx-build ${path_to_repository_in_docker}/docs/source ${path_to_repository_in_docker}/docs/build;
EOS
)

docker run -it --rm \
  --volume ${path_to_repository}:${path_to_repository_in_docker} \
  i05nagai/sphinx-breathe:ubuntu-1.6.3 \
  /bin/bash -c "${command}"
