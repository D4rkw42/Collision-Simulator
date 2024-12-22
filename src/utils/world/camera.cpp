/*
    Definições básicas de câmera
*/

#include "camera.hpp"

#include <iostream>

// classe básica
Camera::Camera(int x, int y) : x(x), y(y), zoom(ZOOM_INITIAL) {}

// Calculando viewport
void Camera::Viewport(std::shared_ptr<Window> window, ObjectInfo info, double& x, double& y, double& size) {
    double cam_x = this->x;
    double cam_y = this->y;

    // cálculo baseado no mundo
    x = info.x - cam_x;
    y = info.y - cam_y;

    // transformações para amostragem na tela
    x *= this->zoom;
    y *= this->zoom;

    size = info.size * this->zoom;

    int w_width, w_height;
    window->GetDimensions(w_width, w_height);

    x += w_width / 2;
    y += w_height / 2;
}

//

void Camera::UpdateCameraPosition(Mouse mouse) {
    static int last_cam_x = this->x;
    static int last_cam_y = this->y;

    if (mouse.left.hold) {
        int x_diff = mouse.x - mouse.left.hold_x;
        int y_diff = mouse.y - mouse.left.hold_y;

        this->x = last_cam_x - x_diff * (1.f / this->zoom);
        this->y = last_cam_y - y_diff * (1.f / this->zoom);
    } else {
        last_cam_x = this->x;
        last_cam_y = this->y;
    }
}

void Camera::ZoomIn(void) {
    this->zoom += ZOOM_MOD;

    if (this->zoom > MAX_ZOOM) {
        this->zoom = MAX_ZOOM;
    }
}

void Camera::ZoomOut(void) {
    this->zoom -= ZOOM_MOD;

    if (this->zoom < MIN_ZOOM) {
        this->zoom = MIN_ZOOM;
    }
}

//

// funções auxiliares

// obtém o quanto do mundo a câmera está capturando (com acréscimo de 10%)
void Camera::GetRenderDistance(std::shared_ptr<Window> window, double& dist_horiz, double& dist_vert) {
    int w_width, w_height;

    // obtendo dimensões da janela
    window->GetDimensions(w_width, w_height);

    // calculando distância observada (top-bottom, left-right)
    dist_horiz = 1.3f * (w_width * (1.f / this->zoom));
    dist_vert = 1.3f * (w_height * (1.f / this->zoom));
}

void Camera::GetAbsolutePosition(std::shared_ptr<Window> window, double x, double y, double &absoluteX, double &absoluteY) {
    int w_width, w_height;
    window->GetDimensions(w_width, w_height);

    double xRelativeToWindow = x - w_width/2;
    double yRelativeToWindow = y - w_height/2;

    double xRelativeToWorld = xRelativeToWindow * 1.f/this->zoom;
    double yRelativeToWorld = yRelativeToWindow * 1.f/this->zoom;

    absoluteX = this->x + xRelativeToWorld;
    absoluteY = this->y + yRelativeToWorld;
}
