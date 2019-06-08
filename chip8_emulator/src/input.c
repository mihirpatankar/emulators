/*==============================================================================
 Include Files
 =============================================================================*/

#include "input.h"

/*==============================================================================
 Static Data
 =============================================================================*/

// 1 2 3 C   --->   1 2 3 4
// 4 5 6 D   --->   q w e r
// 7 8 9 E   --->   a s d f
// A 0 B F   --->   z x c v
static uint8_t keymap[16] = {
    SDLK_x,
    SDLK_1,
    SDLK_2,
    SDLK_3,
    SDLK_q,
    SDLK_w,
    SDLK_e,
    SDLK_a,
    SDLK_s,
    SDLK_d,
    SDLK_z,
    SDLK_c,
    SDLK_4,
    SDLK_r,
    SDLK_f,
    SDLK_v,
};

/*==============================================================================
 Function definitions
 =============================================================================*/

void initialize_input(input* input)
{
  for(int i = 0; i < KEY_INPUT_COUNT; i++)
  {
    input->keys[i] = 0;
  }
}

void process_input(input* input)
{
  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
      if(event.type == SDL_QUIT)
      {
        exit(0);
      }

      // Process key down events
      if(event.type == SDL_KEYDOWN)
      {
        if(event.key.keysym.sym == SDLK_ESCAPE)
        {
          exit(0);
        }

        for(int i = 0; i < KEY_INPUT_COUNT; i++)
        {
          if(event.key.keysym.sym == keymap[i])
          {
            input->keys[i] = 1;
          }
        }
      }

      // Process key up events
      if(event.type == SDL_KEYUP)
      {
        for(int i = 0; i < KEY_INPUT_COUNT; i++)
        {
          if(event.key.keysym.sym == keymap[i])
          {
            input->keys[i] = 0;
          }
        }
      }
  }
}
