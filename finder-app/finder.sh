#!/bin/sh


if [ $# -ne 2 ];
then
    echo "number of arguments doesn't match the expected value"
    exit 1
fi

filesdir="$1"
searchstr="$2"

if [ ! -d $filesdir ]; then
    echo "$filesdir is not a directory."
    exit 1
fi


numberOfFiles=$(ls -l $filesdir | wc -l)

numberOfMatchingLines=$(grep -rl $searchstr $filesdir | wc -l)

echo "The number of files are $numberOfFiles and the number of matching lines are $numberOfMatchingLines"


