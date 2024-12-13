// Determina como as regras da física funcionam no mundo

#include "physics.hpp"

#include <cmath>

void BodyElasticCollision(double &velX1, double &velY1, double &velX2, double &velY2) {
    double dVelX = velX1 - velX2;
    double dVelY = velY1 - velY2;

    double angle = atan2(abs(velY1), abs(velX1)); // ângulo da colisão

    // O objeto 1 aplica energia no objeto 2 e este perde energia também
    velX2 += dVelX * ELASTIC_COEFFICIENT * abs(cos(angle));
    velX1 -= dVelX * ELASTIC_COEFFICIENT * abs(cos(angle));

    velY2 += dVelY * ELASTIC_COEFFICIENT * abs(sin(angle));
    velY1 -= dVelY * ELASTIC_COEFFICIENT * abs(sin(angle));

    // Verificação e correção de velocidade terminal

}
