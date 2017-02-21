#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

namespace rb {
  struct IO{
    /*Balls to the wall no error checking, totally wont ever bite us in the ass*/
    char* loadFromFile(const char* fileName) {
      FILE *f = fopen(fileName, "rb");
  		fseek(f, 0, SEEK_END);
  		long fsize = ftell(f);
  		fseek(f, 0, SEEK_SET);

  		char *string = (char *)malloc(fsize + 1);
  		fread(string, fsize, 1, f);
  		fclose(f);

  		string[fsize] = 0;
  		return string;
  }
  }io;
}
