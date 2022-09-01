# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/15 17:25:57 by vvaucoul          #+#    #+#              #
#    Updated: 2022/07/19 00:21:24 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

make -C . fre
if [ $? -ne 0 ]; then
    echo "Error: make failed"
    exit 1
fi

MAP=$1
if [ -z $MAP ]
then
    echo "Using default Map: test_01.map"
    MAP=maps/test_01.map
fi

GRAPHIC=$2
if [ -z $GRAPHIC ]
then
    echo "Using no graphic options..."
    GRAPHIC=""
fi

reset
time ./lem-in < $MAP $GRAPHIC
