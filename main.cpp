#include <iostream>
#include <string>
#include <cstdint>
#include <memory>

#include "genesys_vm.hpp"

using namespace std;

const bool debugPrint = false;

void executeSample(uint16_t code[], uint16_t len) {
    unique_ptr<GenesysVM> vm(new GenesysVM(code, len, 100000));
    vm->Execute();
    cout << vm->GetIC() << endl;
}

int main()
{
    int samples = 0;
    string input_line;

    cin >> samples;
    cin.ignore();

    if (debugPrint) {
        cout << "Number of samples: " << samples << endl;
    }

    uint16_t code[1000];
    int instructionsCount = 0;

    while (cin) {
        try {
            getline(cin, input_line);

            if (debugPrint) {
                cout << "Read: '" << input_line << "'" << endl;
            }

            code[instructionsCount++] = std::stoi(input_line);
        } catch(std::invalid_argument& e) {

            // Debug output
            if (debugPrint) {
                cout << "Executing " << instructionsCount << " instructions:" << endl;
                for (int i=0; i<instructionsCount; i++) {
                    cout << code[i] << " ";
                }
                cout << endl;
            }

            executeSample(code, instructionsCount);
            instructionsCount = 0;
        }
    };

    if (instructionsCount != 0) {
        executeSample(code, instructionsCount);
    }

    return 0;
}
