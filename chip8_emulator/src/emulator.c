/*==============================================================================
 Include Files
 =============================================================================*/

#include "emulator.h"

/*==============================================================================
 Function definitions
 =============================================================================*/

void init(chip8* chip8)
{
  initialize_cpu(&chip8->cpu);
  initialize_memory(&chip8->memory);
  initialize_display(&chip8->display);
  initialize_input(&chip8->input);
}

void emulate_cycle(chip8* chip8)
{
  // Get pointers to cpu, memory and display
  cpu* cpu = &chip8->cpu;
  memory* memory = &chip8->memory;
  display* display = &chip8->display;
  input* input = &chip8->input;

  // Get opcode from RAM
  uint16_t opcode = (memory->RAM[cpu->PC] << 8) | (memory->RAM[cpu->PC + 1]);

  // disassemble opcodes
  switch(opcode & 0xF000)
  {
    case 0x0000:
    {
      switch(opcode & 0x00FF)
      {
        case 0x00E0://CLS
        {
          for(int i = 0; i < DEFAULT_DISPLAY_HEIGHT; i++)
          {
            for(int j = 0; j < DEFAULT_DISPLAY_WIDTH; j++)
            {
              display->display_matrix[i][j] = 0;
            }
          }
          display->draw_flag = true;
        }
        case 0x00EE://RET
        {
          cpu->PC = memory->stack[cpu->SP];
          cpu->SP--;
        }
      }
    }
    case 0x1000://JP addr
    {
      cpu->PC = (opcode & 0x0FFF);
    }
    case 0x2000: //2nnn : CALL addr
    {
      cpu->SP++;
      memory->stack[cpu->SP] = cpu->PC;
      cpu->PC = (opcode & 0x0FFF);
    }
    case 0x3000: //3xkk : SE Vx, byte
    {
      uint8_t x = (opcode & 0x0F00) >> 8;
      uint8_t byte = (opcode & 0x00FF);
      if(cpu->V[x] == byte)
      {
        cpu->PC += 2;
      }
    }
    case 0x4000: //4xkk : SNE Vx, byte
    {
      uint8_t x = (opcode & 0x0F00) >> 8;
      uint8_t byte = (opcode & 0x00FF);
      if(cpu->V[x] != byte)
      {
        cpu->PC += 2;
      }
    }
    case 0x5000: //5xy0 : SE Vx, Vy
    {
      uint8_t x = (opcode & 0x0F00) >> 8;
      uint8_t y = (opcode & 0x00F0) >> 4;
      if(cpu->V[x] != cpu->V[y])
      {
        cpu->PC += 2;
      }
    }
    case 0x6000: //6xkk : LD Vx, byte
    {
      uint8_t x = (opcode & 0x0F00) >> 8;
      uint8_t byte = (opcode & 0x00FF);
      cpu->V[x] = byte;
    }
    case 0x7000: //7xkk : ADD Vx, byte
    {
      uint8_t x = (opcode & 0x0F00) >> 8;
      uint8_t byte = (opcode & 0x00FF);
      cpu->V[x] += byte;
    }
    case 0x8000:
    {
      uint8_t x = (opcode & 0x0F00) >> 8;
      uint8_t y = (opcode & 0x00F0) >> 4;
      switch(opcode & 0x000F)
      {
        case 0x0000://8xy0 : LD Vx, Vy
        {
          cpu->V[x] = cpu->V[y];
        }
        case 0x0001://8xy1 : OR Vx, Vy
        {
          cpu->V[x] |= cpu->V[y];
        }
        case 0x0002://8xy2 : AND Vx, Vy
        {
          cpu->V[x] &= cpu->V[y];
        }
        case 0x0003://8xy3 : XOR Vx, Vy
        {
          cpu->V[x] ^= cpu->V[y];
        }
        case 0x0004://8xy4 : ADD Vx, Vy
        {
          uint16_t sum = cpu->V[x] + cpu->V[y];
          cpu->V[x] = (sum & 0x00FF);
          cpu->V[0xF] = 0;
          if(sum > 255)
          {
            cpu->V[0xF] = 1;
          }
        }
        case 0x0005://8xy5 : SUB Vx, Vy
        {
          cpu->V[0xF] = 0;
          if(cpu->V[x] > cpu->V[y])
          {
            cpu->V[0xF] = 1;
          }
          cpu->V[x] = cpu->V[x] - cpu->V[y];
        }
        case 0x0006://8xy6 : SHR Vx {,Vy}
        {
          uint8_t lsb = cpu->V[x] & 0x01;
          cpu->V[0xF] = 0;
          if(0x1 == lsb)
          {
            cpu->V[0xF] = 1;
          }
          cpu->V[x] = cpu->V[x] >> 1;
        }
        case 0x0007://8xy7 : SUBN Vx, Vy
        {
          cpu->V[0xF] = 0;
          if(cpu->V[y] > cpu->V[x])
          {
            cpu->V[0xF] = 1;
          }
          cpu->V[x] = cpu->V[y] - cpu->V[x];
        }
        case 0x000E://8xyE : SHL Vx {,Vy}
        {
          uint8_t msb = cpu->V[x] & 0x80;
          cpu->V[0xF] = 0;
          if(0x80 == msb)
          {
            cpu->V[0xF] = 1;
          }
          cpu->V[x] = cpu->V[x] << 1;
        }
      }
    }
    case 0x9000: //9xy0 : SNE Vx, Vy
    {
      uint8_t x = (opcode & 0x0F00) >> 8;
      uint8_t y = (opcode & 0x00F0) >> 4;
      if(cpu->V[x] != cpu->V[y])
      {
        cpu->PC += 2;
      }
    }
    case 0xA000: //Annn : LD I, addr
    {
      cpu->I = (opcode & 0x0FFF);
    }
    case 0xB000: //Bnnn : JP V0, addr
    {
      uint16_t addr = (opcode & 0x0FFF);
      cpu->PC = addr + cpu->V[0];
    }
    case 0xC000: //Cxkk : RND Vx, byte
    {
      uint8_t x = (opcode & 0x0F00) >> 8;
      uint8_t byte = (opcode & 0x00FF);
      uint8_t random_num = rand() % 256;
      cpu->V[x] = random_num & byte;
    }
    case 0xD000: //Dxyn : DRW Vx, Vy, nibble
    {
      uint8_t x = (opcode & 0x0F00) >> 8;
      uint8_t y = (opcode & 0x00F0) >> 4;
      uint8_t height = (opcode & 0x000F);
      uint8_t pixel = 0;
      cpu->V[0xF] = 0;

      //TODO
    }
    case 0xF000:
    {
      uint8_t x = (opcode & 0x0F00) >> 8;
      switch(opcode & 0x00FF)
      {
        case 0x0007://0xFx07 : LD Vx, DT
        {
          cpu->V[x] = cpu->delay_timer;
        }
        case 0x000A://0xFx0A : LD Vx, K
        {
          // wait for key press, store the value in Vx
        }
        case 0x0015://0xFx15 : LD DT, Vx
        {
          cpu->delay_timer = cpu->V[x];
        }
        case 0x0018://0xFx18 : LD ST, Vx
        {
          cpu->sound_timer = cpu->V[x];
        }
        case 0x001E://0xFx1E : ADD I, Vx
        {
          cpu->I += cpu->V[x];
        }
        case 0x0029://0xFx29 : LD F, Vx
        {
        }
        case 0x0033://0xFx33 : LD B, Vx
        {
        }
        case 0x0055://0xFx55 : LD [I], Vx
        {
          uint8_t index = (opcode & 0x0F00) >> 8;
          for(int i = 0; i < index; i++)
          {
            memory->RAM[cpu->I + i] = cpu->V[i];
          }
        }
        case 0x0065://0xFx65 : LD Vx, [I]
        {
          uint8_t index = (opcode & 0x0F00) >> 8;
          for(int i = 0; i < index; i++)
          {
            cpu->V[i] =  memory->RAM[cpu->I + i];
          }
        }
      }
    }
  }

  // update timers
  if(cpu->delay_timer > 0)
  {
    --cpu->delay_timer;
  }

  if(cpu->sound_timer > 0)
  {
    if(1 == cpu->sound_timer)
    {
      //TODO sound implementation
    }
    --cpu->sound_timer;
  }

}
