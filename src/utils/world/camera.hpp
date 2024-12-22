/*
    Definições básicas de câmera
*/

#pragma once

#include <memory>

#include "config/SDL2/graphics/Window.hpp"

#include "utils/world/mouse.hpp"

// definições
const double MAX_ZOOM = 3.f; // zoom máximo permitido
const double MIN_ZOOM = 0.4f; // zoom mínimo permitido
const double ZOOM_INITIAL = 0.8f; // zoom inicial

const double ZOOM_MOD = 0.15f; // alteração do zoom

// dados que serão passados como referência dos cálculos
struct ObjectInfo {
    double size, x, y;
};

// classe básica
class Camera {
    public:
        double x, y;

        Camera(int x, int y);

        // Cálculo de viewport
        void Viewport(std::shared_ptr<Window> window, ObjectInfo info, double& x, double& y, double& size);

        // controle de posição
        void UpdateCameraPosition(Mouse mouse);

        void ZoomIn(void); // aumenta o zoom
        void ZoomOut(void); // dimunui o zoom

        // funções auxiliares

        
        void GetRenderDistance(std::shared_ptr<Window> window, double& dist_horiz, double& dist_vert); // obtém o quanto do mundo a câmera está capturando (com acréscimo de 10%)
        void GetAbsolutePosition(std::shared_ptr<Window> window, double x, double y, double& absoluteX, double& absoluteY); // a posição real de um ponto x, y a partir da posição da câmera

    private:
        double zoom;

};
