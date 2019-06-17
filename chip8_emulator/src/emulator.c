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
  // Get pointers
  cpu* cpu = &chip8->cpu;
  memory* memory = &chip8->memory;
  display* display = &chip8->display;
  input* input = &chip8->input;

  // Get opcode from RAM
  uint16_t opcode = (memory->RAM[cpu->PC] << 8) | (memory->RAM[cpu->PC + 1]);

  printf("Opcode : 0x%04X\n", opcode);

  uint8_t x = (opcode & 0x0F00) >> 8;
  uint8_t y = (opcode & 0x00F0) >> 4;
  uint8_t byte = (opcode & 0x00FF);
  uint16_t addr = (opcode & 0x0FFF);

  //update PC
  cpu->PC += 2;

  // disassemble opcodes
  switch(opcode & 0xF000)
  {
    case 0x0000:
    {
      switch(opcode & 0x00FF)
      {
        case 0x00E0://CLS
        {
          for(int i = 0; i < DISPLAY_MAT_SIZE; i++)
          {
            display->display_matrix[i] = 0;
          }
          display->draw_flag = true;
          break;
        }

        case 0x00EE://RET
        {
          cpu->SP--;
          cpu->PC = memory->stack[cpu->SP];
          break;
        }
      }
      break;
    }

    case 0x1000://JP addr
    {
      cpu->PC = addr;
      break;
    }

    case 0x2000: //2nnn : CALL addr
    {
      memory->stack[cpu->SP] = cpu->PC;
      cpu->SP++;
      cpu->PC = (opcode & 0x0FFF);
      break;
    }

    case 0x3000: //3xkk : SE Vx, byte
    {
      if(cpu->V[x] == byte)
      {
        cpu->PC += 2;
      }
      break;
    }

    case 0x4000: //4xkk : SNE Vx, byte
    {
      if(cpu->V[x] != byte)
      {
        cpu->PC += 2;
      }
      break;
    }

    case 0x5000: //5xy0 : SE Vx, Vy
    {
      if(cpu->V[x] == cpu->V[y])
      {
        cpu->PC += 2;
      }
      break;
    }

    case 0x6000: //6xkk : LD Vx, byte
    {
      cpu->V[x] = byte;
      break;
    }

    case 0x7000: //7xkk : ADD Vx, byte
    {
      uint16_t sum = cpu->V[x] + byte;
      cpu->V[x] = (sum & 0x00FF);
      break;
    }
    case 0x8000:
    {
      switch(opcode & 0x000F)
      {
        case 0x0000://8xy0 : LD Vx, Vy
        {
          cpu->V[x] = cpu->V[y];
          break;
        }

        case 0x0001://8xy1 : OR Vx, Vy
        {
          cpu->V[x] |= cpu->V[y];
          break;
        }

        case 0x0002://8xy2 : AND Vx, Vy
        {
          cpu->V[x] &= cpu->V[y];
          break;
        }

        case 0x0003://8xy3 : XOR Vx, Vy
        {
          cpu->V[x] ^= cpu->V[y];
          break;
        }

        case 0x0004://8xy4 : ADD Vx, Vy
        {
          uint16_t sum = cpu->V[x] + cpu->V[y];
          cpu->V[x] = (sum & 0x00FF);
          cpu->V[0xF] = 0;
          if(sum > 0xFF)
          {
            cpu->V[0xF] = 1;
          }
          break;
        }

        case 0x0005://8xy5 : SUB Vx, Vy
        {
          cpu->V[0xF] = 0;
          if(cpu->V[x] > cpu->V[y])
          {
            cpu->V[0xF] = 1;
          }
          cpu->V[x] = cpu->V[x] - cpu->V[y];
          break;
        }

        case 0x0006://8xy6 : SHR Vx {,Vy}
        {
          uint8_t lsb = cpu->V[x] & 0x01;
          cpu->V[0xF] = 0;
          if(0x01 == lsb)
          {
            cpu->V[0xF] = 1;
          }
          cpu->V[x] = cpu->V[x] >> 1;
          break;
        }

        case 0x0007://8xy7 : SUBN Vx, Vy
        {
          cpu->V[0xF] = 0;
          if(cpu->V[y] > cpu->V[x])
          {
            cpu->V[0xF] = 1;
          }
          cpu->V[x] = cpu->V[y] - cpu->V[x];
          break;
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
          break;
        }
      }
      break;
    }

    case 0x9000: //9xy0 : SNE Vx, Vy
    {
      if(cpu->V[x] != cpu->V[y])
      {
        cpu->PC += 2;
      }
      break;
    }

    case 0xA000: //Annn : LD I, addr
    {
      cpu->I = (opcode & 0x0FFF);
      break;
    }

    case 0xB000: //Bnnn : JP V0, addr
    {
      uint16_t addr = (opcode & 0x0FFF);
      cpu->PC = addr + cpu->V[0];
      break;
    }

    case 0xC000: //Cxkk : RND Vx, byte
    {
      uint8_t random_num = rand() % 256;
      cpu->V[x] = random_num & byte;
      break;
    }

    case 0xD000: //Dxyn : DRW Vx, Vy, nibble
    {
      uint8_t height = (opcode & 0x000F);
      uint8_t pixel = 0;
      cpu->V[0xF] = 0;
      display->draw_flag = true;

      // TODO implement instruction

      break;
    }

    case 0xE000:
    {
      switch(opcode & 0x00FF)
      {
        case 0x009E:
        {
          if(1 == input->keys[cpu->V[x]])
          {
            cpu->PC += 2;
          }
          break;
        }

        case 0x00A1:
        {
          if(0 == input->keys[cpu->V[x]])
          {
            cpu->PC += 2;
          }
        }
      }
      break;
    }
    case 0xF000:
    {
      switch(opcode & 0x00FF)
      {
        case 0x0007://0xFx07 : LD Vx, DT
        {
          cpu->V[x] = cpu->delay_timer;
          break;
        }

        case 0x000A://0xFx0A : LD Vx, K
        {
          // TODO implement instruction

          break;
        }

        case 0x0015://0xFx15 : LD DT, Vx
        {
          cpu->delay_timer = cpu->V[x];
          break;
        }

        case 0x0018://0xFx18 : LD ST, Vx
        {
          cpu->sound_timer = cpu->V[x];
          break;
        }

        case 0x001E://0xFx1E : ADD I, Vx
        {
          cpu->I += cpu->V[x];
          cpu->V[0xF] = 0;
          if(cpu->I > 0xFFF)
          {
            cpu->V[0xF] = 1;
          }
          break;
        }

        case 0x0029://0xFx29 : LD F, Vx
        {
          cpu->I = cpu->V[x] * 5;
          break;
        }

        case 0x0033://0xFx33 : LD B, Vx
        {
          memory->RAM[cpu->I] = cpu->V[x] / 100;
          memory->RAM[cpu->I + 1] = (cpu->V[x] /10) % 10;
          memory->RAM[cpu->I + 2] = cpu->V[x] % 10;
          break;
        }

        case 0x0055://0xFx55 : LD [I], Vx
        {
          uint8_t index = (opcode & 0x0F00) >> 8;
          for(int i = 0; i < index; i++)
          {
            memory->RAM[cpu->I + i] = cpu->V[i];
          }
          break;
        }

        case 0x0065://0xFx65 : LD Vx, [I]
        {
          uint8_t index = (opcode & 0x0F00) >> 8;
          for(int i = 0; i < index; i++)
          {
            cpu->V[i] =  memory->RAM[cpu->I + i];
          }
          break;
        }
      }
      break;
    }

    default:
    {
      printf("ERROR: Unimplemented opcode : 0x%04X", opcode);
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
      printf("Sound timer : BEEP\n");
      //TODO sound implementation
    }
    --cpu->sound_timer;
  }

}
