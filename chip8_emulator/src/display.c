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
  display->renderer = NULL;
  display->texture = NULL;

  // Initialize display matrix
  for(int i = 0; i < DISPLAY_MAT_SIZE; i++)
  {
    display->display_matrix[i] = DISPLAY_MAT_INIT;
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
      display->renderer = SDL_CreateRenderer(display->window, -1, 0);
      SDL_RenderSetLogicalSize(display->renderer, MAPPED_DISPLAY_WIDTH,
          MAPPED_DISPLAY_HEIGHT);
      display->texture = SDL_CreateTexture(display->renderer,
          SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
          DEFAULT_DISPLAY_WIDTH, DEFAULT_DISPLAY_HEIGHT);
    }
  }
}

void update_display(display* display)
{
  uint8_t pixels[DISPLAY_MAT_SIZE];
  if(display->draw_flag)
  {
    display->draw_flag = false;
    for(int i = 0; i < DISPLAY_MAT_SIZE; i++)
    {
        pixels[i] = display->display_matrix[i];
    }

    SDL_UpdateTexture(display->texture, NULL, pixels,
        DEFAULT_DISPLAY_WIDTH * sizeof(uint32_t));
    // Clear screen and render
    SDL_RenderClear(display->renderer);
    SDL_RenderCopy(display->renderer, display->texture, NULL, NULL);
    SDL_RenderPresent(display->renderer);
  }
}
