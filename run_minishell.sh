#!/bin/bash

if [ "$1" == "-c" ];
	then clear
fi

make re
echo -e "\n\033[36m========================== Output ==========================\033[0m\n"
./minishell
echo -e "\n\033[36m============================================================\033[0m\n"
