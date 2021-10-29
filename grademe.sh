#!/bin/bash

TESTER_FT="./tester_ft"
TESTER_STL="./tester_stl"

OUTPUT_LOG_FT="result_ft.log"
OUTPUT_LOG_STL="result_stl.log"

BENCHMARK_LOG_FT="benchmark_ft.log"
BENCHMARK_LOG_STL="benchmark_stl.log"

TIME_FT="time_ft"
TIME_STL="time_stl"

COLOR_OK="\e[32m"
COLOR_KO="\e[31m"
COLOR_RESET="\e[0m"

print_ok_ko () {
    code=$1
    if [ ${code} -eq 0 ]; then
        printf "[${COLOR_OK}OK${COLOR_RESET}]\n"
    else
        printf "[${COLOR_KO}KO${COLOR_RESET}]\n"
    fi
}

print_arguments () {
    if [ $# -eq 0 ]; then
        echo "test all containers"
    else
        echo "test: $@"
    fi
}

test_output () {
    echo "** test output **"

    echo "< stl vs ft >"
    (time "${TESTER_STL}" $@ > "${OUTPUT_LOG_STL}") > "${TIME_STL}" 2>&1
    (time "${TESTER_FT}" $@ > "${OUTPUT_LOG_FT}") > "${TIME_FT}" 2>&1
    sdiff -w 60 <(cat "${TIME_STL}" | tail -n +2) <(cat "${TIME_FT}" | tail -n +2)

    echo -n "diff: "
    diff_result=$(diff "${OUTPUT_LOG_STL}" "${OUTPUT_LOG_FT}")
    print_ok_ko $?

    rm -f "${TIME_STL}" "${TIME_FT}"
    echo
}

test_benchmark () {
    echo "** test benchmark **"

    "${TESTER_STL}" -b $@ > "${BENCHMARK_LOG_STL}"
    "${TESTER_FT}" -b $@ > "${BENCHMARK_LOG_FT}"
    echo "< stl vs ft >"
    sdiff -w 80 "${BENCHMARK_LOG_STL}" "${BENCHMARK_LOG_FT}"
}

main () {
    print_arguments $@
    test_output $@
    test_benchmark $@
}

main $@
exit 0
