/*==============================================================================
 Include Files
 =============================================================================*/

#include <argp.h>
#include "common.h"
#include "emulator.h"
#include "debug.h"

/*==============================================================================
 Macros
 =============================================================================*/

#define LOAD_PROGRAM_OFFSET 0x200
#define DEBUG_DELAY 1 // 1Hz
#define CHIP8_DELAY 0.001 // 100Hz
/*==============================================================================
 Public data
 =============================================================================*/

bool debug = false;

/*==============================================================================
 Static data
 =============================================================================*/

static FILE* file_handle = NULL;

/*==============================================================================
 Static functions
 =============================================================================*/

static void load_program(FILE* file_handle, memory* memory)
{
  int file_size = 0;

  //Get the file size
  fseek(file_handle, 0L, SEEK_END);
  file_size = ftell(file_handle);
  fseek(file_handle, 0L, SEEK_SET);

  fread(&memory->RAM[LOAD_PROGRAM_OFFSET], file_size, 1, file_handle);
  fclose(file_handle);
}

static FILE* get_file_handle(char* rom_path)
{
  FILE* file_handle = fopen(rom_path, "rb");
  if(NULL == file_handle)
  {
    printf("ERROR : Invalid input path\n");
    exit(1);
  }
  return file_handle;
}

static int parse_arg(int key, char* arg, struct argp_state *state)
{
  switch(key)
  {
    case 'r':
    {
      file_handle = get_file_handle(arg);
      break;
    }
    case 'd':
    {
      debug = (atoi(arg) != 0);
      break;
    }
  }
  return 0;
}

/*==============================================================================
 Function definitions
 =============================================================================*/

int main(int argc, char** argv)
{
  printf("Chip8 emulator\n");

  int rc = 0;

  // Seed random number
  srand(time(NULL));

  // Parse arguments
  struct argp_option options[] =
  {
    { "rom", 'r', "path", 0, "Enter the absolute RAM path"},
    { "debug", 'd', "<0/1>", 0, "Enter 0/1 to debug the program"},
    { 0 }
  };

  struct argp argp = {options, parse_arg, 0, 0};

  if(argp_parse(&argp, argc, argv, 0, 0, 0))
  {
    printf("ERROR : Failed to parse arguments\n");
    exit(1);
  }

  // Declare chip8
  chip8 chip8;

  // Initialize
  init(&chip8);

  // Load program into memory
  load_program(file_handle, &chip8.memory);

  while(true)
  {
    // emulate cycle
    emulate_cycle(&chip8);

    // process inputs
    process_input(&chip8.input);

    // update display
    update_display(&chip8.display);

    if(debug)
    {
      sleep(DEBUG_DELAY);
    }
    else
    {
      sleep(CHIP8_DELAY);
    }
  }
  // process keyboard input

  // emulate cycle

  // Debug state
  if(debug)
  {
    debug_state(&chip8);
  }

  // delay (60Hz)

  printf("Chip8 emulation COMPLETE\n");
  return rc;
}
