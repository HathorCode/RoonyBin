#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

namespace rb {
  struct IO{
    /*Balls to the wall no error checking, totally wont ever bite us in the ass*/
    char* loadFromFile(const char* fileName) {
      char *fileContents;
      long inputSize;
      FILE *inputFile = fopen(fileName, "rb");
      fseek(inputFile, 0, SEEK_END);
      inputSize = ftell(inputFile);
      rewind(inputFile);
      fileContents = (char*)malloc(inputSize * (sizeof(char)));
      fread(fileContents, sizeof(char), inputSize, inputFile);
      fclose(inputFile);                                // close the stream
      return fileContents;
  }
  }io;
}
