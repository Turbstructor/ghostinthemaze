#!/bin/zsh

local SECTOR="E"
local MAIN_GROUP_NAME="sector$SECTOR"

groupadd "$MAIN_GROUP_NAME"

cp -r . "/home/manager/"

gcc -o "decode" decode.c
gcc -o ".set_aslr" "prototypes/set_aslr.c"
gcc -o ".reset_aslr" "prototypes/reset_aslr.c"
gcc -o "generate_key" generate_key.c

cp ".set_aslr" "/home/manager/" && chmod 6755 "/home/manager/.set_aslr"
cp ".reset_aslr" "/home/manager/" && chmod 6755 "/home/manager/.reset_aslr"

cp "decode" "/home/$MAIN_GROUP_NAME/" && chmod 6755 "/home/$MAIN_GROUP_NAME/decode"
cp "generate_key" "/home/$MAIN_GROUP_NAME/"

cp "../.zshrc" "/home/$MAIN_GROUP_NAME/"
cp "../.gdbinit" "/home/$MAIN_GROUP_NAME/"
cp "../.tmux.conf" "/home/$MAIN_GROUP_NAME/"

chown root:root "re-initialize.sh"
cp "re-initialize.sh" "/home/$MAIN_GROUP_NAME/" && chmod 700 "/home/$MAIN_GROUP_NAME/re-initialize.sh"