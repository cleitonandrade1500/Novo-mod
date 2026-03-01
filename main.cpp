#include "natives.h" // Você precisará deste arquivo no seu repo
#include <chrono>
#include <thread>

bool is_pressed = false;
auto start_time = std::chrono::steady_clock::now();

void spawn_john_bodyguard() {
    Ped player = PLAYER::PLAYER_PED_ID();
    Vector3 pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player, 0.0, 3.0, 0.0);
    
    // Hash do John Marston
    Hash model = MISC::GET_HASH_KEY("CS_JOHNMARSTON");
    STREAMING::REQUEST_MODEL(model, false);
    while (!STREAMING::HAS_MODEL_LOADED(model)) std::this_thread::yield();

    Ped john = PED::CREATE_PED(model, pos.x, pos.y, pos.z, 0, true, false, false, false);
    
    // Configura como Guarda-costas
    PED::SET_PED_AS_GROUP_MEMBER(john, PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_ID()));
    PED::SET_PED_RELATIONSHIP_GROUP_HASH(john, MISC::GET_HASH_KEY("PLAYER"));
    
    // IA de combate e loot
    PED::SET_PED_COMBAT_ATTRIBUTES(john, 5, true); // BF_CanDoDriveBys
    PED::SET_PED_CONFIG_FLAG(john, 136, true);    // Can loot bodies
    
    STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
}

void check_buttons() {
    // L2 (INPUT_FRONTEND_LS) + D-Pad Up (INPUT_FRONTEND_UP)
    if (PAD::IS_CONTROL_PRESSED(0, 0x4FD566FE) && PAD::IS_CONTROL_PRESSED(0, 0x91102E97)) {
        if (!is_pressed) {
            is_pressed = true;
            start_time = std::chrono::steady_clock::now();
        } else {
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count() >= 2) {
                spawn_john_bodyguard();
                is_pressed = false; // Evita spawn infinito
            }
        }
    } else {
        is_pressed = false;
    }
}

extern "C" int module_start(size_t argc, const void* args) {
    // Loop principal (em uma thread separada para não travar o console)
    std::thread([]() {
        while (true) {
            check_buttons();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }).detach();
    return 0;
}
