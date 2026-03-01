#include "natives.h"
#include "types.h"
#include <chrono>
#include <thread>

// Definições de Botões PS4 (RAGE Engine)
#define INPUT_L2 0x4FD566FE
#define INPUT_DPAD_UP 0x91102E97

bool is_timer_active = false;
auto start_time = std::chrono::steady_clock::now();

void spawn_john_bodyguard() {
    Ped player = PLAYER::PLAYER_PED_ID();
    Vector3 pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player, 0.0, 3.0, 0.0);
    
    Hash model = MISC::GET_HASH_KEY("CS_JOHNMARSTON");
    STREAMING::REQUEST_MODEL(model, false);
    while (!STREAMING::HAS_MODEL_LOADED(model)) std::this_thread::yield();

    // Spawn do John
    Ped john = PED::CREATE_PED(model, pos.x, pos.y, pos.z, 0, true, false, false, false);
    
    // Configura Grupo (Guarda-costas)
    int groupID = PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_ID());
    PED::SET_PED_AS_GROUP_MEMBER(john, groupID);
    PED::SET_PED_NEVER_LEAVES_GROUP(john, true);
    
    // IA de Defesa e Saque (Loot)
    PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(john, true);
    PED::SET_PED_COMBAT_ATTRIBUTES(john, 5, true); // Can fight
    PED::SET_PED_CONFIG_FLAG(john, 136, true);    // Can loot
    
    STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
}

extern "C" int module_start(size_t argc, const void* args) {
    std::thread([]() {
        while (true) {
            // Verifica L2 + D-Pad Cima
            if (PAD::IS_CONTROL_PRESSED(0, INPUT_L2) && PAD::IS_CONTROL_PRESSED(0, INPUT_DPAD_UP)) {
                if (!is_timer_active) {
                    is_timer_active = true;
                    start_time = std::chrono::steady_clock::now();
                } else {
                    auto now = std::chrono::steady_clock::now();
                    if (std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count() >= 2) {
                        spawn_john_bodyguard();
                        is_timer_active = false; 
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Delay para não spawnar vários
                    }
                }
            } else {
                is_timer_active = false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }).detach();
    return 0;
}

extern "C" int module_stop(size_t argc, const void* args) { return 0; }
