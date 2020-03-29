#include <stdio.h>
#include <stdbool.h>
#define ip (registers[IP]) // instruction pointer short
#define sp (registers[SP]) // stack pointer short
#define STACK_SIZE 255
void eval(int);
int fetch();

typedef enum
{
  PSH,
  ADD,
  POP,
  SET,
  HLT
} InstructionSet;

// general purpose register
typedef enum
{
  A, B, C, D, E, F, SP, IP,
  NUMBER_OF_REGISTER
} gpr;

int registers[NUMBER_OF_REGISTER]; // set the registers

int stack[STACK_SIZE]; // set the stack
bool running = true;   // program loop

// our program
int program[] = {
    PSH, 50,
    PSH, 10,
    ADD,
    POP,
    SET, A, 20,
    HLT,
};

int main()
{
  ip = 0;  // set instruction pointer register to 0
  sp = -1; // set stack pointer register to 0
  while (running)
  {
    int instruction = fetch(); // instruction fetch
    eval(instruction);         // evaluated the instruction
    ip++;
  }
  return 0;
}

int fetch()
{
  return program[ip];
}

void eval(int instruction)
{
  switch (instruction)
  {
  case HLT:
    // abort the program
    running = false;
    break;
  case PSH:
    stack[++sp] = program[++ip];
    break;
  case ADD:
    registers[A] = 0;
    while (sp > -1)
    {
      registers[A] += stack[sp];
      stack[sp--] = 0;
    }
    stack[++sp] = registers[A];
    break;
  case POP:
    registers[A] = stack[sp];
    stack[sp--] = 0;
    printf("adddeg: %d\n", registers[A]);
    break;
  case SET:
    ip++;
    registers[program[--ip]] = program[++ip];
    ip++;
    printf("inareg: %d\n", registers[A]);
    break;
  default:
    running = false;
    break;
  }
}
