#!/bin/bash
dir="build"
if [ ! -d "$dir" ]; then
	echo "build directory not found, creating it"
	mkdir -p "$dir"
fi
echo "Compiling..."
gcc fourinarow.c -o ./$dir/fourinarow
chmod +x ./$dir/fourinarow
echo "Complete! Running build."
echo ""
./$dir/fourinarow