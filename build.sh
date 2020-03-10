#!/bin/bash
dir="build"
file="fourinarow"
useold=0
debug=0

run () {
	echo ""
	if [ $debug -eq 1 ]; then
		echo "Using gdb debug!"
		echo ""
		gdb ./$dir/$file
	else
		./$dir/$file
	fi
}

for arg in "$@"; do
	if [ "$arg" == "-o" ]; then
		useold=1
	elif [ "$arg" == "-d" ]; then
		debug=1
	fi
done

if [ ! -d "$dir" ]; then
	echo "build directory not found, creating it"
	mkdir -p "$dir"
fi
echo "Compiling..."
success=0
out=$(gcc $file.c -g -o ./$dir/$file -Wall)
if [ $? -ne 0 ]; then
	echo "Errors found, aborting run"
else
	if grep "warning:" <<<"${out}" >/dev/null ; then
		echo "Warnings found, aborting run"
	else
		echo "$file OK"
		success=1
		chmod +x ./$dir/$file
		echo "Running build..."
		run
	fi
fi
if [ $success -eq 0 ]; then
	if [ $useold -eq 1 ]; then
		echo "Using old build..."
		run
	fi
fi