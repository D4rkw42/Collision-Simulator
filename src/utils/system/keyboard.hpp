// definições para guardar o estado do teclado

#pragma once

#include <memory>
#include <vector>
#include <string>

#include <SDL2/SDL.h>

// estados de uma tecla
struct KeyState {
    bool clickDown, clickUp, hold;
};

// definição de tecla
class Key {
    public:
        SDL_Scancode id;
        std::string name;

        KeyState state;

        Key(SDL_Scancode id, const std::string& name) {
            this->id = id;
            this->name = name;

            this->state = KeyState { false, false, false };
        }
};

// lista de keys
typedef std::vector<std::shared_ptr<Key>> KeyList;

// utility

// criação de keys

inline std::shared_ptr<Key> CreateKey(SDL_Scancode id, const std::string& name) {
    return std::make_shared<Key>(id, name);
}

inline void RegisterNewKey(KeyList& keyList, SDL_Scancode id, const std::string& name) {
    keyList.push_back(CreateKey(id, name));
}

// Obtendo keys e states

inline std::shared_ptr<Key> GetKey(const KeyList& keyList, SDL_Scancode id) {
    for (auto key : keyList) {
        if (key->id == id) {
            return key;
        }
    }

    return nullptr;
}

inline KeyState GetKeyState(const KeyList& keyList, const std::string& name) {
    for (auto key : keyList) {
        if (key->name == name) {
            return key->state;
        }
    }
}
