#!/bin/bash

# rmdir 명령어 구현
rmdir_command() {
    if [ -d "$1" ]; then
        rmdir "$1" && echo "Directory '$1' removed successfully."
    else
        echo "Error: Directory '$1' does not exist or is not empty."
    fi
}

# ln 명령어 구현
ln_command() {
    if [ -e "$1" ]; then
        ln "$1" "$2" && echo "Hard link from '$1' to '$2' created successfully."
    else
        echo "Error: Source file '$1' does not exist."
    fi
}

# cp 명령어 구현
cp_command() {
    if [ -e "$1" ]; then
        cp "$1" "$2" && echo "File '$1' copied to '$2' successfully."
    else
        echo "Error: Source file '$1' does not exist."
    fi
}

# 사용자 입력 처리
echo "Welcome to Mini Shell!"
while true; do
    echo -n "mini_shell> "
    read -r cmd arg1 arg2
    case "$cmd" in
        rmdir) rmdir_command "$arg1" ;;
        ln) ln_command "$arg1" "$arg2" ;;
        cp) cp_command "$arg1" "$arg2" ;;
        exit) echo "Exiting Mini Shell. Goodbye!"; break ;;
        *) echo "Unknown command: $cmd" ;;
    esac
done

