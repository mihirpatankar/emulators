#pragma once
/*==============================================================================
 Include Files
 =============================================================================*/

#include "common.h"
#include <SDL2/SDL.h>

/*==============================================================================
 Macros
 =============================================================================*/

#define DEFAULT_DISPLAY_WIDTH 64
#define DEFAULT_DISPLAY_HEIGHT 32

#define MAPPED_DISPLAY_WIDTH 640
#define MAPPED_DISPLAY_HEIGHT 320

/*==============================================================================
 Type definitions
 =============================================================================*/

typedef struct
{
  uint8_t display_matrix[DEFAULT_DISPLAY_HEIGHT][DEFAULT_DISPLAY_WIDTH];
  bool draw_flag;
  //The window we'll be rendering to
  SDL_Window* window;
  //The surface contained by the window
  SDL_Surface* screen_surface;
} display;

/*==============================================================================
 Function declarations
 =============================================================================*/

void initialize_display(display* display);
