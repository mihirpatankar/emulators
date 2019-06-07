/*==============================================================================
 Include Files
 =============================================================================*/

#include "display.h"

/*==============================================================================
 Macros
 =============================================================================*/

#define DISPLAY_MAT_INIT 0
#define DRAW_FLAG_INIT false
#define SDL_WINDOW_NAME "CHIP8 EMULATOR"

/*==============================================================================
 Function declarations
 =============================================================================*/

void initialize_display(display* display)
{
  display->draw_flag = DRAW_FLAG_INIT;
  display->window = NULL;
  display->screen_surface = NULL;

  // Initialize display matrix
  for(int i = 0; i < DEFAULT_DISPLAY_HEIGHT; i++)
  {
    for(int j = 0; j < DEFAULT_DISPLAY_WIDTH; j++)
    {
      display->display_matrix[i][j] = DISPLAY_MAT_INIT;
    }
  }

  //Initialize SDL
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    printf("ERROR : SDL could not initialize! SDL_Error : %s\n", SDL_GetError());
  }
  else
  {
    //Create window
    display->window = SDL_CreateWindow(SDL_WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, MAPPED_DISPLAY_WIDTH, MAPPED_DISPLAY_HEIGHT,
        SDL_WINDOW_SHOWN);
    if(NULL == display->window)
    {
      printf("ERROR : Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
      //Get window surface
      display->screen_surface = SDL_GetWindowSurface(display->window);
    }
  }
}
