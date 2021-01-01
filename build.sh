#!/bin/bash

# g++ -o 15Puzzle -Wall -std=c++17 src/*.cpp

# Print extensive warnings if -w argument provided  
if [[ $1 == "-w" ]]
  then
    g++ -o 15Puzzle -Wall -std=c++17 src/*.cpp
else
    g++ -o 15Puzzle -std=c++17 src/*.cpp
fi
