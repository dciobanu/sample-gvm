#include <iostream>
#include <memory>
#include <assert.h>
#include "genesys_vm.hpp"

using namespace std;

void GenesysVMTest::test_errors() {
    // Checking for memory addressing error
    { 
        unique_ptr<GenesysVM> vm1(new GenesysVM({}, 0, 10000));                

        bool expected = false;
        try {
            vm1->Execute();
        } catch(std::out_of_range e) {
            expected = true;
        }
        assert(expected);
        assert(vm1->ic == 1000);
        assert(vm1->ip == 1000);
    }

    // Bad HALT instruction
    {
        uint16_t badhalt[] = {123};
        bool expected = false;
        unique_ptr<GenesysVM> vm1(new GenesysVM(badhalt, 1, 10000));
        try {
            vm1->Execute();
        } catch(std::range_error e) {
            expected = true;
        }
        assert(expected);
    }

    // Bad instruction
    {
        uint16_t badinstruction[] = {9999};
        bool expected = false;
        unique_ptr<GenesysVM> vm1(new GenesysVM(badinstruction, 1, 10000));
        try {
            vm1->Execute();
        } catch(std::range_error e) {
            expected = true;
        }
        assert(expected);
    }            
}

void GenesysVMTest::test_halting() {
    uint16_t code[] = {100};
    unique_ptr<GenesysVM> vm(new GenesysVM(code, 1, 10000));
    vm->Execute();

    assert(vm->ic == 1);
    assert(vm->ip == 0);
    assert(!vm->running);
}

void GenesysVMTest::test_SetR() {
    uint16_t code[11];
    for (int i=0; i<10; i++) {
        code[i] = 200+10*i+i;
    }
    code[10] = 100;

    unique_ptr<GenesysVM> vm(new GenesysVM(code, 11, 10000));
    vm->Execute();

    for (int i=0; i<10; i++) {
        assert(vm->regs[i] == i);
    }

    assert(vm->ip == 10);
    assert(vm->ic == 11);
    assert(!vm->running);
}

void GenesysVMTest::test_AddNtoR() {
    cout << "TODO: implement" << endl;
}

void GenesysVMTest::test_MulRbyN() {
    cout << "TODO: implement" << endl;
}

void GenesysVMTest::test_MovRtoR() {
    cout << "TODO: implement" << endl;
}

void GenesysVMTest::test_AddRtoR() {
    cout << "TODO: implement" << endl;
}

void GenesysVMTest::test_MulRtoR() {
    cout << "TODO: implement" << endl;
}

void GenesysVMTest::test_MoveMemToR() {
    cout << "TODO: implement" << endl;
}

void GenesysVMTest::test_MoveRToMem() {
    cout << "TODO: implement" << endl;
}

void GenesysVMTest::test_Jmp() {
    cout << "TODO: implement" << endl;
}

void GenesysVMTest::test_sample1() {
    uint16_t sample1[] = {299, 492, 495, 399, 492, 495, 399, 283, 279, 689, 78, 100, 0, 0, 0};
    unique_ptr<GenesysVM> vm(new GenesysVM(sample1, sizeof(sample1)/sizeof(uint16_t), 10000));
    vm->Execute();
    cout<<(vm->ic)<<endl;
    assert((vm->ic) == 16);
};

int main() {
    cout << "Testing GenesysVM" << endl;
    GenesysVMTest::run();
    return 0;
}