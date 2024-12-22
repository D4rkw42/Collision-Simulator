/*
    Apenas definições que guardam o estado do mouse
*/

#pragma once

// informações de botões específicos
struct MouseInfo {
    bool hold; // se está segurando
    int hold_x, hold_y; // posição que começou a segurar
};

// definições de mouse
struct Mouse {
    int x, y; // posição do mouse em tempo real
    double velX, velY; // velocidade instantânea do mouse em tempo real
    
    MouseInfo right;
    MouseInfo left;
};
