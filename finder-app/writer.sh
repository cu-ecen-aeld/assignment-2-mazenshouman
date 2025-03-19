#!/bin/sh


if [ $# -ne 2 ];
then
    echo "number of arguments doesn't match the expected value"
    exit 1
fi

writefile="$1"
writestr="$2"

directory=$(dirname "$writefile")

# Create the directory if it doesn't exist
if [ ! -d "$directory" ]; then
    mkdir -p "$directory" || { echo "Error: Could not create directory '$directory'."; exit 1;};
fi

if echo $writestr > $writefile; then
    echo "File "$writefile" created with the string: "$writestr""
else
    echo "Error: Could not create file '$writefile'."
    exit 1
fi