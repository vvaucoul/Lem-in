# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    push.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 17:29:37 by vvaucoul          #+#    #+#              #
#    Updated: 2022/07/12 16:36:57 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/sh

if [ -z "$1" ]
then
    echo "Usage: ./push.sh <commit name>"
    exit 1
fi

make -C . fclean > /dev/null 2>&1
git add --all && git commit -am "$1" && git push