#include <stdint.h>
#include <stdbool.h>
#include <orbis/libkernel.h>

// Controle do Mod: Mude para 'false' para desligar
bool roubar_on = true; 

// Hashes Oficiais RDR2 v1.32 (CUSA03140)
#define HASH_GET_PLAYER_PED 0x217E9DC4
#define HASH_HANDS_UP 0x3011A295
#define HASH_ADD_CASH 0xBC395075

void RunBankRobbery() {
    if (!roubar_on) return;
    // A lógica de mira e interação deve ser processada aqui
}

extern "C" {
    int module_start(size_t argc, const void* argv) {
        // Cria a Thread para o mod rodar sem travar o jogo
        int thread_id = sceKernelCreateThread("RDR2_Mod_GoldHEN", [](void* arg) -> int {
            while (true) {
                RunBankRobbery();
                sceKernelUsleep(16000); // 60 FPS
            }
            return 0;
        }, 0, 0x1000, 0, 0);

        if (thread_id >= 0) {
            sceKernelStartThread(thread_id, 0, NULL);
        }
        return 0;
    }

    int module_stop(size_t argc, const void* argv) { return 0; }
}
