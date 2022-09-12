# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_all_maps.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 16:01:13 by vvaucoul          #+#    #+#              #
#    Updated: 2022/09/07 19:53:58 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/sh

COLOR_RED="\033[91m"
COLOR_GREEN="\033[92m"
COLOR_RESET="\033[0m"
COLOR_CYAN="\033[96m"

ASCII_X=❌
ASCII_V=✔️

DIRECTORY=$1

if [ -z "$DIRECTORY" ]
then
    echo "Usage: ./test_all_maps.sh [DIRECTORY]"
    exit 1
fi

printf "$COLOR_CYAN - Loading...\n$COLOR_RESET"
clear && make fre > /dev/null && reset

for f in $DIRECTORY/*
do
    if [ -f $f ]
    then
        clear
        printf "Testing map $COLOR_GREEN$f$COLOR_RESET\n"
        sleep .2
        ./lem-in < $f
        RET=$?
        if [ $RET != 0 ]
        then
           printf "\n${COLOR_RED}FAILED${COLOR_RESET} [$ASCII_X]\n"
          sleep 1
        else
            printf "\n${COLOR_GREEN}SUCCESS${COLOR_RESET} [$ASCII_V ]\n"
        fi
        sleep .2
    fi
done