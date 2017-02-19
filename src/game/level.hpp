#pragma once
#include <vector>
#include <glm/glm.hpp>

#include"FoxLib\FoxLib.hpp"

#include "object.hpp"

#include "src/engine/renderer/sprite.hpp"
#include "src/engine/renderer/assetmanager.hpp"
//glm, gl

namespace rb {
struct Level {
  std::vector<Object> Tiles;


  void load(const char* file, uint8 levelWidth, GLuint levelHeight) {
	  Tiles.clear();

	  uint8 tileCode;
	  Level level;
	  std::string line;
	  std::ifstream fstream(file);
	  std::vector<std::vector<uint8>> tileData;
	  if (fstream) {
		  while (std::getline(fstream, line)) {
			  std::istringstream sstream(line);
			  std::vector<uint8> row;
			  while (sstream >> tileCode) // Read each word seperated by spaces
				  row.push_back(tileCode);
			  tileData.push_back(row);
		  }
		  if (tileData.size() > 0){
			  //init(tileData, levelWidth, levelHeight);
		  }

	  }
  }

  void draw(Sprite &renderer) {
	  for (Object &tile : Tiles) {
		  tile.draw(renderer);
	  }
  }

};

}
