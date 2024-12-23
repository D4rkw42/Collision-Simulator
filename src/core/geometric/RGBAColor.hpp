// RGBA color

#pragma once

// RGBA structure
struct RGBA {
    int r, g, b;
    double a;
};

// Cores padronizadas

const RGBA RGBA_RED = RGBA { 255, 0, 0, 0.6f };
const RGBA RGBA_WHITE = RGBA { 255, 255, 255, 0.6f };
const RGBA RGBA_GREEN = RGBA { 0, 128, 0, 0.6f };
