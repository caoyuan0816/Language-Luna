#!/bin/sh

#Setting paths
SCRIPT_PATH=$(readlink -f "$0")
ROOT_PATH=$(dirname "$SCRIPT_PATH")

echo "Running path: ${ROOT_PATH}"
echo ""

#Check build dependencies
echo "Checking Build dependencies..."
echo "------------------------------------------------------"
echo ""

if command -v cmake >/dev/null 2>&1 ; then
	echo "cmake found"
	echo "version: $(cmake --version)"
else
	echo "cmake not found"
	echo ""
	echo "Please install cmake before building project"
	echo "For Ubuntu: sudo apt-get install cmake"
	echo "For Mac: "
	exit 1
fi
echo ""

if command -v flex >/dev/null 2>&1 ; then
	echo "flex found"
	echo "version: $(flex --version)"
else
	echo "flex not found"
	echo ""
	echo "Please install flex before building project"
	echo "For Ubuntu: sudo apt-get install flex"
	echo "For Mac: "
	exit 1
fi
echo ""

if command -v bison >/dev/null 2>&1 ; then
	echo "bison found"
	echo "version: $(bison --version)"
else
	echo "bison not found"
	echo ""
	echo "Please install bison before building project"
	echo "For Ubuntu: sudo apt-get install bison"
	echo "For Mac: "
	exit 1
fi
echo ""

#Compile luna
echo "Compiling luna & lunac..."
echo "------------------------------------------------------"
echo ""

rm -rf "${ROOT_PATH}/build"
rm luna
rm lunac
mkdir "${ROOT_PATH}/build"
cd "${ROOT_PATH}/build"
cmake .. && make
cp ./bin/lunac ../
cp ./bin/luna  ../

cd ${ROOT_PATH}

# Finished
echo ""
echo "------------------------------------------------------"
echo "Compile Success"
echo ""
echo "luna & lunac has been saved in your current directory: ${ROOT_PATH}"
echo ""
echo "To install luna & luna to your computer:"
echo ""
echo "   cd build && sudo make install && cd .."
echo ""
echo "Then you can use command luna & lunac everywhere."
echo "------------------------------------------------------"
