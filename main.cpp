#include <stdint.h>

bool roubar_on = false; // Comando para ligar/desligar

extern "C" {
    void RunBankRobbery() {
        if (!roubar_on) return; // Se estiver OFF, não faz nada

        // Hashes para a Versão 1.32 (CUSA03140)
        uint64_t playerPed = 0x217E9DC4; 
        uint64_t handsUp = 0x3011A295;
        uint64_t addMoney = 0xBC395075;

        // Lógica: Se mirar, o banqueiro rende e ganha $500
        // (Aqui o seu Invoker deve processar os hashes acima)
    }
}
