/*==============================================================================
 Include Files
 =============================================================================*/

#include "debug.h"

/*==============================================================================
 Macros
 =============================================================================*/

#define DEBUG_FILE "debug_state.txt"
#define HEADER_START "/*==================================================================\n"
#define HEADER_END "===================================================================*/\n"
#define SECTION_END "\n\n"
#define BYTES_PER_ROW 4

/*==============================================================================
 Static data
 =============================================================================*/



/*==============================================================================
 Static functions
 =============================================================================*/

static FILE* get_file_handle()
{
  FILE* file_handle = fopen(DEBUG_FILE, "wb");
  if(NULL == file_handle)
  {
    printf("ERROR : Could not open file\n");
    exit(1);
  }
  return file_handle;
}

static void register_dump(FILE* f, cpu* cpu)
{
  fprintf(f, HEADER_START);
  fprintf(f, "Register Dump\n");
  fprintf(f, HEADER_END);

  fprintf(f, "Index register = 0x%04X\n", cpu->I);
  fprintf(f, "Program counter = 0x%04X\n", cpu->PC);
  fprintf(f, "Stack pointer = 0x%02X\n", cpu->SP);
  for(int i = 0; i < GP_REGISTER_COUNT; i++)
  {
    fprintf(f, "General purpose register : V[%X] = 0x%02X\n", i, cpu->V[i]);
  }
  fprintf(f, "Delay timer = 0x%02X\n", cpu->delay_timer);
  fprintf(f, "Sound timer = 0x%02X\n", cpu->sound_timer);
  fprintf(f, SECTION_END);
}

static void memory_dump(FILE* f, memory* memory)
{
  fprintf(f, HEADER_START);
  fprintf(f, "RAM Dump\n");
  fprintf(f, HEADER_END);

  for(int i = 0; i < RAM_SIZE; i++)
  {
    if(0 == i%BYTES_PER_ROW)
    {
      fprintf(f, "\n 0x%03X  -->  ", i);
    }
    fprintf(f, "0x%02X  ", memory->RAM[i]);
  }
  fprintf(f, SECTION_END);

  fprintf(f, HEADER_START);
  fprintf(f, "Stack Dump\n");
  fprintf(f, HEADER_END);

  for(int i = 0; i < STACK_SIZE; i++)
  {
    fprintf(f, "%X --> 0x%04X\n", i, memory->stack[i]);
  }
  fprintf(f, SECTION_END);
}

static void display_dump(FILE* f, display* display)
{
  fprintf(f, HEADER_START);
  fprintf(f, "Display Dump\n");
  fprintf(f, HEADER_END);

  //TODO reimplement display dump

  fprintf(f, SECTION_END);
}

/*==============================================================================
 Function declarations
 =============================================================================*/

void debug_state(chip8* chip8)
{
  FILE* file_handle = NULL;

  file_handle = get_file_handle();

  register_dump(file_handle, &chip8->cpu);

  memory_dump(file_handle, &chip8->memory);

  display_dump(file_handle, &chip8->display);

  fclose(file_handle);

  exit(1);
}
