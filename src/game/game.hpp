
namespace rb{
  struct Game{
    GameState state;
  }

  /* We can include more gamestates as we need them*/
  enum GameState {
    GAME_ACTIVE,
    GAME_MENU
  }
}
