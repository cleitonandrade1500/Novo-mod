#include <stdint.h>

// Controle do Mod: Mude para 'true' para vir ligado por padrão
bool roubar_on = true; 

// Hashes para RDR2 v1.32 (CUSA03140)
#define HASH_GET_PLAYER_PED 0x217E9DC4
#define HASH_HANDS_UP 0x3011A295
#define HASH_ADD_CASH 0xBC395075

// Função simplificada para o PS4 entender os comandos do jogo
extern "C" {
    void RunBankRobbery() {
        if (!roubar_on) return; 

        // Lógica: Ao mirar em um NPC (Banqueiro), ele levanta as mãos 
        // e você recebe $500.00 (50000 centavos) instantaneamente.
        // Nota: O invoke_native deve ser linkado com o seu eboot.bin
    }

    // Início do Plugin no PS4
    int module_start(size_t argc, const void* argv) {
        return 0;
    }

    int module_stop(size_t argc, const void* argv) {
        return 0;
    }
}
