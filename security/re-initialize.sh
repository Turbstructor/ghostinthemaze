#!/bin/zsh

# this is run from another user, "manager", not by "sector*".
local INTRO=1
local REV=2
local BOF=3
local SC=3
local RTL=3
local FILENAMES=("INTRO" "REV" "BOF" "SC" "RTL")
local FILECOUNT=(INTRO REV BOF SC RTL)

local SECTOR="E"
local MAIN_GROUP_NAME="sector$SECTOR"
local GROUP_NAME=""
local ROOM_NAME=""
local SAFE_NAME=""
local KEY_FILENAME=""

# (re-)initialize rooms
for number in 1 2 3 4 5
do
	GROUP_NAME="room$SECTOR$number"
	ROOM_NAME="room$SECTOR$number"
	SAFE_NAME="safe$number"
	KEY_FILENAME="slot$number.key"

	deluser -q --remove-home $ROOM_NAME
	deluser -q $SAFE_NAME
	delgroup -q $GROUP_NAME

	groupadd $GROUP_NAME

	date +%N | md5sum | head -c8 > "$KEY_FILENAME"
	# useradd -m -g "$MAIN_GROUP_NAME" -G "$GROUP_NAME" -s $(which zsh) -p $(openssl passwd -crypt $(echo "$ROOM_NAME")) "$ROOM_NAME"
	useradd -m -g "$MAIN_GROUP_NAME" -G "$GROUP_NAME" -s $(which zsh) "$ROOM_NAME" && passwd -d "$ROOM_NAME"
	useradd -g "$GROUP_NAME" -p $(openssl passwd -crypt $(cat "$KEY_FILENAME")) "$SAFE_NAME"

	chmod 750 "/home/$ROOM_NAME"

	cp "/home/manager/.zshrc" "/home/$ROOM_NAME/"
	cp "/home/manager/.tmux.conf" "/home/$ROOM_NAME/"
	cp "/home/manager/.gdbinit" "/home/$ROOM_NAME/"

	cp "$KEY_FILENAME" "/home/$ROOM_NAME/$KEY_FILENAME"
	chown "$SAFE_NAME":"$GROUP_NAME" "/home/$ROOM_NAME/$KEY_FILENAME"
	chmod 440 "/home/$ROOM_NAME/$KEY_FILENAME"
	rm "$KEY_FILENAME"
done

echo "1 1 1 1 1" > "/home/sector$SECTOR/.lock_slots"

# pick up questions and configure rooms for them
for number in 1 2 3 4 5
do
	GROUP_NAME="room$SECTOR$number"
	ROOM_NAME="room$SECTOR$number"
	SAFE_NAME="safe$number"

	local RND=$(( $(($RANDOM % ${FILECOUNT[$number]} )) + 1 ))
	local FILENAME="${FILENAMES[$number]}_$RND"
	cp "/home/manager/prototypes/$FILENAME.c" "/home/$ROOM_NAME/"

	sed -i -e "s/#define UID 0/#define UID $(id -u $SAFE_NAME)/g" -e "s/#define GID 0/#define GID $(id -g $SAFE_NAME)/g" "/home/$ROOM_NAME/$FILENAME.c"
    sed -i -e "s/#define KEY 0x0/#define KEY 0x$(./generate_key)/g" "/home/$ROOM_NAME/$FILENAME.c"

	IFS=$'\n' local lines=($(while read line; do; echo $line; done < "/home/manager/prototypes/$FILENAME.gccconf"))

	local ASLR=""
	local NX=""
	local CANARY=""

	if [ $lines[1] = 0 ]; then
		ASLR=0
	else
		ASLR=2
	fi

	if [ $lines[2] = 0 ]; then
		NX="execstack"
	else
		NX="noexecstack"
	fi

	if [ $lines[3] = 0 ]; then
		CANARY="no-stack-protector"
	else
		CANARY="stack-protector-all"
	fi


	echo '#!/bin/zsh' > "/home/$ROOM_NAME/instructions"
	echo 'clear; cat readme.md' >> "/home/$ROOM_NAME/instructions"
	chmod +x "/home/$ROOM_NAME/instructions"

	echo "$ASLR" > "/home/$ROOM_NAME/.aslr"
	# cp "prototypes/.set_aslr" "/home/$ROOM_NAME/"
	# cp "prototypes/.reset_aslr" "/home/$ROOM_NAME/"

	# chmod 6755 "/home/$ROOM_NAME/.set_aslr"
	# chmod 6755 "/home/$ROOM_NAME/.reset_aslr"

    cp "${FILENAMES[$number]}_readme.md" "/home/$ROOM_NAME/readme.md"

	echo "#!/bin/zsh" > "/home/$ROOM_NAME/.zlogin"
	echo "/home/manager/.set_aslr > /dev/null" >> "/home/$ROOM_NAME/.zlogin"
	echo "./instructions" >> "/home/$ROOM_NAME/.zlogin"

	echo "#!/bin/zsh" > "/home/$ROOM_NAME/.zlogout"
	echo "/home/manager/.reset_aslr > /dev/null" >> "/home/$ROOM_NAME/.zlogout"

	gcc -f"$CANARY" -z $NX -o "/home/$ROOM_NAME/SAFE" "/home/$ROOM_NAME/$FILENAME.c"

    if [ $number -le 3 ]; then
        rm "/home/$ROOM_NAME/$FILENAME.c"
    fi

	chown "$SAFE_NAME":"$GROUP_NAME" "/home/$ROOM_NAME/SAFE"
	chmod 6755 "/home/$ROOM_NAME/SAFE"
done