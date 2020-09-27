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

# Check if backup looks legit.
if [ ! -d "/host/$1/config" ]; then
	echo "Directory $1/config not found. Are you sure its a actual backup?"
	echo "NOTE: It must be a dirname without symlinks pointing outside of the current directory."
	exit 3
fi
if [ ! -d "/host/$1/log" ]; then
	echo "Directory $1/log not found. Are you sure its a actual backup?"
	echo "NOTE: It must be a dirname without symlinks pointing outside of the current directory."
	exit 4
fi
if [ ! -d "/host/$1/world" ]; then
	echo "Directory $1/world not found. Are you sure its a actual backup?"
	echo "NOTE: It must be a dirname without symlinks pointing outside of the current directory."
	exit 5
fi

# Restore volumes content.
rm -rf /tshock/{config,log,world}/* && cp -a /host/$1/. /tshock/
