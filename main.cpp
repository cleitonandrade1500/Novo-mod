#include <stdint.h>
#include <stdbool.h>

// Toggle: ON/OFF
bool roubar_on = true; 

extern "C" {
    void RunBankRobbery() {
        if (!roubar_on) return;
        // Códigos para a 1.32:
        // Hands Up: 0x3011A295 | Money: 0xBC395075
    }

    int module_start(size_t argc, const void* argv) { return 0; }
    int module_stop(size_t argc, const void* argv) { return 0; }
}
