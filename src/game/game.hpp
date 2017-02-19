#pragma once

namespace rb{
  struct Game{
	/* We can add more states eventually, I can't think of more rn though*/
	enum GameState {
		GAME_ACTIVE = 0,
		GAME_MENU = 1,
		GAME_FINISHED = 2
	};

	GameState state;
  }game;
}
