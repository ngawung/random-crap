#!/bin/sh

# Check if backup specified.
if [ "$#" -ne 1 ]; then
	echo "Backup dirname wasn't specified."
	echo "NOTE: It must be a dirname without symlinks pointing outside of the current directory."
	exit 1
fi

# Check if backup based on root.
first_char="$(printf '%s' "$1" | cut -c1)"
if [ "$first_char" = "/" ]; then
	echo "Backup dirname can't be based on root."
	echo "NOTE: It must be a dirname without symlinks pointing outside of the current directory."
	exit 2
fi

# Check if backup already exists.
if [ -d "/host/$1" ]; then
	echo "Backup dirname already exists."
	exit 3
fi

# Create backup directories.
mkdir -p /host/$1/config
if [ ! -d "/host/$1/config" ]; then
	echo "There was a problem creating the directory $1/config ."
	echo "NOTE: It must be a dirname without symlinks pointing outside of the current directory."
	exit 4
fi
mkdir -p /host/$1/log
mkdir -p /host/$1/world

# Do backup.
cp -a /tshock/config/. /host/$1/config/
cp -a /tshock/log/. /host/$1/log/
cp -a /tshock/world/. /host/$1/world/
