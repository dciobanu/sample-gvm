#include <algorithm>
#include <vector>
#include <iostream>
#include <cstring>

#include "genesys_vm.hpp"

using namespace std;

GenesysVM::GenesysVM(uint16_t code[], uint16_t len, uint64_t limit)
{
    if (len > 1000)
    {
        throw std::invalid_argument("Code size exceeds 1000 instructions");
    }

    ilimit = limit;
    ip = 0;
    ic = 0;

    for (int i=0; i<10; i++) {
        regs[i] = 0;
    }

    int i;
    for (i=0; i<1000 && i<len; i++) {
        memory[i] = code[i];
    }
    
    for (; i<1000; i++) {
        memory[i] = 0;
    }
}

void GenesysVM::Step()
{
    // std::cout << "Step()" << std::endl;
    uint16_t instruction, d1, d2, d3, addr;

    if (ic > ilimit)
    {
        throw std::length_error("Execution limits exceeded");
    }

    if (ip > 999)
    {
        throw std::out_of_range("IP out of range");
    }

    ic++;
    instruction = memory[ip];

    if (instruction > 999)
    {
        throw std::range_error("Invalid instruction encountered");
    }

    d1 = instruction / 100;
    d2 = (instruction / 10) % 10;
    d3 = instruction % 10;

    switch (d1)
    {
        case 1:
            // HALT
            if (instruction == 100) {
                running = false;
                return;
            }
            else {
                throw std::range_error("Invalid instruction - HALT does not take parameters");
            }
            break;

        case 2:
            // MOV register, value
            regs[d2] = d3;
            ip++;
            break;

        case 3:
            // ADD register, value
            regs[d2] = (regs[d2] + d3) % 1000;
            ip++;
            break;
        
        case 4:
            // MUL register, value
            regs[d2] = (regs[d2] * d3) % 1000;
            ip++;
            break;
        
        case 5:
            // MOV register1, register2
            regs[d2] = regs[d3]; 
            ip++;
            break;
            
        case 6:
            // ADD register1, register2
            regs[d2] = (regs[d2] + regs[d3]) % 1000;
            ip++;
            break;

        case 7:
            // MUL register1, register2
            regs[d2] = uint16_t((int(regs[d2]) * int(regs[d3])) % 1000);
            ip++;
            break;
        
        case 8:
            // MOV register1, memory[register2]
            addr = regs[d3];
            if (addr > 999) {
                throw std::overflow_error("Invalid memory reference");
            }
            else {
                regs[d2] = memory[addr];
            } 
            
            ip++;
            break;
            
        case 9 :
            // MOV memory[register2], register1
            addr = regs[d3]; 
            if (addr > 999) {
                throw std::overflow_error("Invalid memory reference");
            }
            else {
                memory[addr] = regs[d2];
            } 
            
            ip++;
            break;
        
        case 0 :
            // CMP register2,0
            // JNZ register1

            if (regs[d3] == 0) {
                ip++;
            }
            else {
                addr = regs[d2];
                ip = addr;
            }
            break;

        default:
            throw std::range_error("Invalid instruction");
    }
}

void GenesysVM::Execute()
{
    // std::cout << "Execute()" << std::endl;

    while (running) {
        Step();
    }
}

uint64_t GenesysVM::GetIC()
{
    return ic;
}

bool GenesysVM::IsRunning()
{
    return running;
}