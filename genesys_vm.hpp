#ifndef HEADER_HPP_GENESYS_VM
#define HEADER_HPP_GENESYS_VM

#include <cstdint>

class GenesysVM {
    private:
        uint16_t memory[1000];
        uint16_t regs[10];
        uint16_t ip;
        uint64_t ic;
        uint64_t ilimit;
        bool     running;

    public:
        GenesysVM(uint16_t code[], uint16_t len, uint64_t limit);
        void Step();
        void Execute();

        uint64_t GetIC();
        bool IsRunning();

    friend class GenesysVMTest;
};

#endif