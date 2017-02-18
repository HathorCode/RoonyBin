#pragma once

#include <stdio.h>

namespace rb {
  struct IO{
    /*Balls to the wall no error checking, totally wont ever bite us in the ass*/
    char* loadFromFile(const char* fileName) {
      char * buffer = 0;
      long length;
      FILE * f = fopen (fileName, "rb");

      if (f) {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = malloc (length + 1);
        if (buffer) {
          fread (buffer, 1, length, f);
        }
        fclose (f);
        buffer[length] = '\0';
      }

    }

  }io;

}
