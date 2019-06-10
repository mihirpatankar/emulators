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
#define DISPLAY_MAT_SIZE (DEFAULT_DISPLAY_WIDTH * DEFAULT_DISPLAY_HEIGHT)

#define MAPPED_DISPLAY_WIDTH 640
#define MAPPED_DISPLAY_HEIGHT 320

/*==============================================================================
 Type definitions
 =============================================================================*/

typedef struct
{
  uint8_t display_matrix[DISPLAY_MAT_SIZE];
  bool draw_flag;
  SDL_Window* window;
  SDL_Renderer *renderer;
  SDL_Texture* texture;
} display;

/*==============================================================================
 Function declarations
 =============================================================================*/

void initialize_display(display* display);
void update_display(display* display);
