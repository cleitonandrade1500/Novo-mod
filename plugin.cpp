#include <stdint.h>
#include <stdbool.h>
#include <orbis/libkernel.h>

// Importa a lógica que você criou no main.cpp
extern void RunBankRobbery();
extern bool roubar_on;

// Estrutura de exportação do GoldHEN para plugins PRX
extern "C" {
    // Informações do Plugin para o sistema do PS4
    int __module_stop(size_t argc, const void* argv) { return 0; }
    
    // Função de entrada principal (Onde o Gancho acontece)
    int __module_start(size_t argc, const void* argv) {
        
        // Cria uma Thread (Linha de execução) separada para o seu mod
        // Isso evita que o jogo trave (Freeze) enquanto o mod roda
        int thread_id = sceKernelCreateThread("RDR2_BankMod_Thread", [](void* arg) -> int {
            
            // Loop Infinito do Mod
            while (true) {
                // Aqui o "gancho" chama a sua lógica de assalto
                RunBankRobbery();
                
                // Delay de 16ms (Equivale a 60 FPS) para não sobrecarregar a CPU do PS4
                sceKernelUsleep(16000); 
            }
            return 0;
            
        }, 0, 0x1000, 0, 0);

        if (thread_id >= 0) {
            sceKernelStartThread(thread_id, 0, NULL);
        }

        return 0;
    }
}
