/*
    Definições básicas de câmera
*/

#pragma once

#include <memory>

#include "config/SDL2/graphics/Window.hpp"

#include "utils/system/mouse.hpp"

// definições
constexpr double MAX_ZOOM = 3.f; // zoom máximo permitido
constexpr double MIN_ZOOM = 0.1f; // zoom mínimo permitido
constexpr double ZOOM_INITIAL = 0.6f; // zoom inicial

constexpr double ZOOM_MOD = 0.15f; // alteração do zoom

constexpr int CAMERA_X_LIMIT = 3000;
constexpr int CAMERA_Y_LIMIT = 3000;

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
        void Viewport(const std::shared_ptr<Window>& window, const ObjectInfo& info, double& x, double& y, double& size);

        // controle de posição
        void UpdateCameraPosition(const Mouse& mouse);

        void ZoomIn(void); // aumenta o zoom
        void ZoomOut(void); // dimunui o zoom

        // funções auxiliares

        
        void GetRenderDistance(const std::shared_ptr<Window>& window, double& dist_horiz, double& dist_vert); // obtém o quanto do mundo a câmera está capturando (com acréscimo de 10%)
        void GetAbsolutePosition(const std::shared_ptr<Window>& window, double x, double y, double& absoluteX, double& absoluteY); // a posição real de um ponto x, y a partir da posição da câmera

    private:
        double zoom;

};
