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

class GenesysVMTest {
    public:
        static void test_errors();
        static void test_halting();
        static void test_SetR();
        static void test_AddNtoR();
        static void test_MulRbyN();
        static void test_MovRtoR();
        static void test_AddRtoR();
        static void test_MulRtoR();
        static void test_MoveMemToR();
        static void test_MoveRToMem();
        static void test_Jmp();
        
        static void test_sample1();

        static void run() {
            test_errors();
            test_halting();
            test_SetR();
            test_AddNtoR();
            test_MulRbyN();
            test_MovRtoR();
            test_AddRtoR();
            test_MulRtoR();
            test_MoveMemToR();
            test_MoveRToMem();
            test_Jmp();
            test_sample1();
        }
};

#endif