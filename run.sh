#!/bin/sh
#Setting paths
SCRIPT_PATH=$(readlink -f "$0")
ROOT_PATH=$(dirname "$SCRIPT_PATH")

cd "${ROOT_PATH}/data"

echo "Running path: ${ROOT_PATH}"
echo ""

echo "Running Test Files...."
echo ""

echo "----------------------------------------------------"
echo "Compiling error.lu"
../lunac error.lu
echo "Running error.luo"
echo "!THERE SHOULD BE ERRORS!"
../luna error.luo

echo "----------------------------------------------------"

echo "Compiling expressions.lu"
../lunac expressions.lu
echo "Running expressions.luo"
../luna expressions.luo

echo "----------------------------------------------------"

echo "Compiling fibonacci.lu"
../lunac fibonacci.lu
echo "Running fibonacci.luo"
../luna fibonacci.luo

echo "----------------------------------------------------"
echo "Compiling loop.lu"
../lunac loop.lu
echo "Running loop.luo"
../luna loop.luo

echo "----------------------------------------------------"
echo "Compiling nested_loop.lu"
../lunac nested_loop.lu
echo "Running nested_loop.luo"
../luna nested_loop.luo

echo "----------------------------------------------------"
echo "Compiling gcd.lu"
../lunac gcd.lu
echo "Running gcd.luo"
../luna gcd.luo

echo "----------------------------------------------------"


