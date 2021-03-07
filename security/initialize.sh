#!/bin/zsh

local INTRO=1
local REV=2
local BOF=3
local SC=3
local RTL=3
local FILENAMES=("INTRO" "REV" "BOF" "SC" "RTL")
local FILECOUNT=(INTRO REV BOF SC RTL)

local GROUP_NAME=""
local ROOM_NAME=""
local SAFE_NAME=""
local KEY_FILENAME=""

# (re-)initialize rooms
for number in 1 2 3 4 5
do
	GROUP_NAME="roomE$number"
	ROOM_NAME="roomE$number"
	SAFE_NAME="safe$number"
	KEY_FILENAME="slot$number.key"

	deluser -q --remove-home $ROOM_NAME
	deluser -q $SAFE_NAME
	delgroup -q $GROUP_NAME

	groupadd $GROUP_NAME

	date +%N | md5sum | head -c8 > "$KEY_FILENAME"
	useradd -m -g "$GROUP_NAME" -s $(which zsh) -p $(openssl passwd -crypt $(echo "$ROOM_NAME")) "$ROOM_NAME"
	useradd -g "$GROUP_NAME" -p $(openssl passwd -crypt $(cat "$KEY_FILENAME")) "$SAFE_NAME"

	chmod 750 "/home/$ROOM_NAME"

	cp "./.zshrc" "/home/$ROOM_NAME/"
	cp "./.tmux.conf" "/home/$ROOM_NAME/"
	cp "./.gdbinit" "/home/$ROOM_NAME/"

	cp "$KEY_FILENAME" "/home/$ROOM_NAME/$KEY_FILENAME"
	chown "$SAFE_NAME":"$GROUP_NAME" "/home/$ROOM_NAME/$KEY_FILENAME"
	chmod 440 "/home/$ROOM_NAME/$KEY_FILENAME"
	rm "$KEY_FILENAME"

	echo "1 1 1 1 1" > "./.lock_slots"
done

# compile aslr configuration
gcc -o ".set_aslr" "/home/manager/prototypes/set_aslr.c"
gcc -o ".reset_aslr" "/home/manager/prototypes/reset_aslr.c"

chmod 6755 ".set_aslr"
chmod 6755 ".reset_aslr"

# pick up questions and configure rooms for them
for number in 1 2 3 4 5
do
	GROUP_NAME="roomE$number"
	ROOM_NAME="roomE$number"
	SAFE_NAME="safe$number"

	local RND=$(( $(($RANDOM % ${FILECOUNT[$number]} )) + 1 ))
	local FILENAME="${FILENAMES[$number]}_$RND"
	cp "prototypes/$FILENAME.c" "/home/$ROOM_NAME/"

	sed -i -e "s/#define UID 0/#define UID $(id -u $SAFE_NAME)/g" -e "s/#define GID 0/#define GID $(id -g $SAFE_NAME)/g" "/home/$ROOM_NAME/$FILENAME.c"

	IFS=$'\n' local lines=($(while read line; do; echo $line; done < "prototypes/$FILENAME.gccconf"))

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
		CANARY="stack-protector"
	fi


	echo '#!/bin/zsh' > "/home/$ROOM_NAME/instructions"
	echo 'echo "Hello World!"' >> "/home/$ROOM_NAME/instructions"
	chmod +x "/home/$ROOM_NAME/instructions"

	echo "$ASLR" > "/home/$ROOM_NAME/.aslr"
	# cp "prototypes/.set_aslr" "/home/$ROOM_NAME/"
	# cp "prototypes/.reset_aslr" "/home/$ROOM_NAME/"

	# chmod 6755 "/home/$ROOM_NAME/.set_aslr"
	# chmod 6755 "/home/$ROOM_NAME/.reset_aslr"

	echo "#!/bin/zsh" > "/home/$ROOM_NAME/.zlogin"
	echo "/home/manager/.set_aslr > /dev/null" >> "/home/$ROOM_NAME/.zlogin"
	echo "./instructions" >> "/home/$ROOM_NAME/.zlogin"

	echo "#!/bin/zsh" > "/home/$ROOM_NAME/.zlogout"
	echo "/home/manager/.reset_aslr > /dev/null" >> "/home/$ROOM_NAME/.zlogout"

	gcc -f$CANARY -z $NX -o "/home/$ROOM_NAME/SAFE" "/home/$ROOM_NAME/$FILENAME.c"
	chown "$SAFE_NAME":"$GROUP_NAME" "/home/$ROOM_NAME/SAFE"
	chmod 6755 "/home/$ROOM_NAME/SAFE"
done

chown root:root prototypes
chmod 700 prototypes