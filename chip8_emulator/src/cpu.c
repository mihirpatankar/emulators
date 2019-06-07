/*==============================================================================
 Include Files
 =============================================================================*/

#include "cpu.h"

/*==============================================================================
 Macros
 =============================================================================*/

#define PC_INIT 0x200
#define I_INIT 0
#define SP_INIT 0
#define TIMER_INIT 0
#define GP_REG_INIT 0

/*==============================================================================
 Function definitions
 =============================================================================*/

void initialize_cpu(cpu* cpu)
{
  cpu->I = I_INIT;
  cpu->PC = PC_INIT;
  cpu->SP = SP_INIT;
  cpu->delay_timer = TIMER_INIT;
  cpu->sound_timer = TIMER_INIT;
  for(int i = 0; i < GP_REGISTER_COUNT; i++)
  {
    cpu->V[i] = GP_REG_INIT;
  }
}
