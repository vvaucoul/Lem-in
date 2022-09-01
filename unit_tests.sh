# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    unit_tests.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 10:28:01 by vvaucoul          #+#    #+#              #
#    Updated: 2022/07/20 20:57:04 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_RED="\033[91m"
COLOR_GREEN="\033[92m"
COLOR_RESET="\033[0m"

ASCII_X=❌
ASCII_V=✔️

make fre && reset && sleep 1

function_test()
{
    MAP=$1
    EXCPECTED_RESULT=$2
    ./lem-in < $MAP > output.txt

    LEN_ORIGINAL=`wc -l $MAP | awk '{print $1}'`
    LEN=`sed -n '/L/,$p' output.txt | wc -l`
    printf "Map: $MAP done in $COLOR_GREEN$LEN$COLOR_RESET turns\n"

    rm output.txt
    if [ $LEN != $EXCPECTED_RESULT ]
    then
        printf "     ${COLOR_RED}FAILED${COLOR_RESET} [$ASCII_X]$COLOR_RESET\n"
        printf "     ${COLOR_RED}Expected: $EXCPECTED_RESULT$COLOR_RESET\n"
    else
        printf "     ${COLOR_GREEN}SUCCESS${COLOR_RESET} [$ASCII_V ]$COLOR_RESET\n"
    fi
}

# MAPS TESTS
function_test maps/basic.map 3
function_test maps/sujet1.map 5
function_test maps/sujet2-1.map 3
function_test maps/sujet2-2.map 3
function_test maps/sujet3.map 5
function_test maps/sujet_example.map 24
function_test maps/test_01.map 5
function_test maps/test_02.map 6
function_test maps/test_03.map 18
function_test maps/others/maps/valid/1k 45
function_test maps/others/maps/valid/map_pdf 27
function_test maps/others/maps/valid/big/map_big_1 50