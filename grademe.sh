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

print_benchmark_output () {
    paste "${BENCHMARK_LOG_STL}" "${BENCHMARK_LOG_FT}" | awk '{
        if ($2 > $5) {
            printf "%-20s%8s %s", $1, $2, $3
            printf " | "
            printf "\033[32m%-20s%8s %s\033[0m", $4, $5, $6
        }
        else {
            printf "\033[32m%-20s%8s %s\033[0m", $1, $2, $3
            printf " | "
            printf "%-20s%8s %s", $4, $5, $6
        }
        printf "\n"
    }'
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
    print_benchmark_output
}

main () {
    print_arguments $@
    test_output $@
    test_benchmark $@
}

main $@
exit 0
