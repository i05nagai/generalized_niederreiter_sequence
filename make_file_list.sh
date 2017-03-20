#!/bin/sh

function usage {
    cat <<EOF
make_file_list is a tool for generating source list and header list of cmake.

Usage:
    make_file_list [/path/to/source/dir targt_name] [<option>] 

Options:
    --version, -v     print make_file_list version
    --help, -h        print this
EOF
}

function version {
    echo "make_file_list version 0.0.1"
}    

function make_file_list() {
    local num=$#
    local search_dir=$1
    local target_name=$2
    local output_path=cmake/${target_name}.cmake
    local output_test_path=cmake/${target_name}_test.cmake

    if [ $num -ne 2 ]; then
        exit 1
    fi

    # source files without test files
    find $search_dir -name "*.c[(pp)|c]" -and -not -name "*_test.c[(pp)|c]" -and -not -name "*Test.c[(pp)|c]" -and -not -name "main.c[(pp)|c]" | sed -e 's/\s\+/\n/g' | sort > srcs.tmp
    # test files
    find $search_dir -name "*_test.cpp" -or -name "*_test.cc" -or -name "*Test.cpp" -or -name "*Test.cc" -or -name "main.c[(pp)|c]" | sed -e 's/\s\+/\n/g' | sort > test_srcs.tmp
    find $search_dir -name "*.h" | sed -e 's/\s\+/\n/g' | sort > c_headers.tmp
    find $search_dir -name "*.hpp" | sed -e 's/\s\+/\n/g' | sort > cpp_headers.tmp

    echo "LIST (APPEND ${target_name}_SOURCES" > ${output_path}
    cat srcs.tmp | sed -e 's/^/    /g' >> ${output_path}
    echo ')' >> ${output_path}

    echo "LIST (APPEND ${target_name}_HEADERS" >> ${output_path}
    cat c_headers.tmp | sed -e 's/^/    /g' >> ${output_path}
    cat cpp_headers.tmp | sed -e 's/^/    /g' >> ${output_path}
    echo ')' >> ${output_path}

    echo "LIST (APPEND ${target_name}_test_SOURCES" > ${output_test_path}
    cat test_srcs.tmp | sed -e 's/^/    /g' >> ${output_test_path}
    echo ')' >> ${output_test_path}

    rm -f srcs.tmp c_headers.tmp cpp_headers.tmp test_srcs.tmp
    return 1
}

if [ $# -eq 2 ]; then
    make_file_list $1 $2
    ret=$?
    exit $ret
fi

while [ $# -gt 0 ];
do
    case $1 in
        --help|-h)
            usage
            exit 0
        ;;

        --version|-v)
            version
            exit 0
        ;;

        *)
            echo "[ERROR] Invalid option $1"
            usage
            exit 1
        ;;
    esac
    shift
done    


