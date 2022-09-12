# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    unit_tests.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 10:28:01 by vvaucoul          #+#    #+#              #
#    Updated: 2022/09/08 20:01:15 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_RED="\033[91m"
COLOR_GREEN="\033[92m"
COLOR_RESET="\033[0m"
COLOR_CYAN="\033[96m"

ASCII_X=❌
ASCII_V=✔️

printf "$COLOR_CYAN - Loading...\n$COLOR_RESET"
make fre > /dev/null && reset

function_test()
{
    MAP=$1
    EXCPECTED_RESULT=$2
    ./lem-in < $MAP > output.txt

    LEN_ORIGINAL=`wc -l $MAP | awk '{print $1}'`
    LEN=`sed -n '/L/,$p' output.txt | wc -l`
    printf "Map: $MAP done in $COLOR_GREEN$LEN$COLOR_RESET turns\n"

    rm output.txt
    if [ $EXCPECTED_RESULT != -1 ]
    then
        if [ $LEN != $EXCPECTED_RESULT ]
        then
            printf "     ${COLOR_RED}FAILED${COLOR_RESET} [$ASCII_X]$COLOR_RESET\n"
            printf "     ${COLOR_RED}Expected: $EXCPECTED_RESULT$COLOR_RESET\n"
        else
            printf "     ${COLOR_GREEN}SUCCESS${COLOR_RESET} [$ASCII_V ]$COLOR_RESET\n"
        fi
    else
        printf "     ${COLOR_GREEN}SUCCESS${COLOR_RESET} [$ASCII_V ]$COLOR_RESET\n"
    fi
}

function_valgrind()
{
    MAP=$1
    printf "Leak: $COLOR_GREEN$MAP$COLOR_RESET\n"

    STR_CHECK="All heap blocks were freed"
    valgrind ./lem-in < $MAP > output.txt 2>&1
    cat output.txt | grep "$STR_CHECK" > /dev/null
    RES=$?

    rm output.txt
    if [ $RES != 0 ]
    then
        printf "     ${COLOR_RED}FAILED${COLOR_RESET} [$ASCII_X]$COLOR_RESET\n"
        printf "     ${COLOR_RED}Map: $MAP has leaks$COLOR_RESET\n"
        exit 1
    else
        printf "     ${COLOR_GREEN}SUCCESS${COLOR_RESET} [$ASCII_V ]$COLOR_RESET\n"
    fi
}

function_check_generator()
{
    MAP=$1
    printf "Generator: $COLOR_GREEN$MAP$COLOR_RESET\n"

    ./lem-in < $MAP > output.txt
    RES=$?

    if [ $RES != 0 ]
    then
        return 1
    else
        printf "     ${COLOR_GREEN}SUCCESS${COLOR_RESET} [$ASCII_V ]$COLOR_RESET\n"
        return 0
    fi
}

function_generator()
{
    LOOPS=$1

    for i in `seq 1 $LOOPS`
    do
        printf "Generating map $COLOR_GREEN$i$COLOR_RESET/$COLOR_CYAN$LOOPS\n$COLOR_RESET"
        sleep .05
        ROOM_COUNTS=`shuf -i 3-50 -n 1`
        ANT_COUNTS=`shuf -i 1-100 -n 1`
        printf "Params: $COLOR_CYAN$ROOM_COUNTS $COLOR_CYAN$ANT_COUNTS\n$COLOR_RESET"
        sleep .05
        python3 generator.py $ROOM_COUNTS $ANT_COUNTS > map.map
        sleep .05
        function_check_generator map.map
        RES=$?

        if [ $RES -eq 0 ]
        then
            function_test map.map -1
            sleep .05
            function_valgrind map.map
            sleep .05
            rm map.map
        else
            i=$((i - 1))
        fi
        printf "\n$COLOR_RESET"
    done
}

# MAPS TESTS
function_test maps/basic.map 3
function_test maps/sujet1.map 5
function_test maps/sujet2-1.map 3
function_test maps/sujet2-2.map 3
function_test maps/sujet3.map 4
function_test maps/sujet_example.map 24
function_test maps/test_01.map 5
function_test maps/test_02.map 6
function_test maps/test_03.map 18
function_test maps/others/maps/valid/1k 60
function_test maps/others/maps/valid/map_pdf 27
function_test maps/others/maps/valid/big/map_big_1 55
function_test maps/others/maps/valid/6k 118

# INPUT TEST

printf "\n\n"
printf "Check: ${COLOR_GREEN}program without stdin:${COLOR_RESET}\n"
<&- ./lem-in

printf "\n\n"
printf "Check Leaks: \n"
function_valgrind maps/basic.map
function_valgrind maps/basic.map
function_valgrind maps/sujet1.map
function_valgrind maps/sujet2-1.map
function_valgrind maps/sujet2-2.map
function_valgrind maps/sujet3.map
function_valgrind maps/sujet_example.map
function_valgrind maps/test_01.map
function_valgrind maps/test_02.map
function_valgrind maps/test_03.map
function_valgrind maps/others/maps/valid/1k
function_valgrind maps/others/maps/valid/map_pdf
function_valgrind maps/others/maps/valid/big/map_big_1
function_valgrind maps/others/maps/valid/6k

# Generator
printf "\n\n"
printf "Generator: \n"
function_generator 100
