// RGBA color

#pragma once

// RGBA structure
struct RGBA {
    int r, g, b;
    double a;
};

// Cores padronizadas

#define RGBA_RED RGBA { 255, 0, 0, 0.6f }
#define RGBA_WHITE RGBA { 255, 255, 255, 0.6f }
#define RGBA_GREEN RGBA { 0, 128, 0, 0.6f }
