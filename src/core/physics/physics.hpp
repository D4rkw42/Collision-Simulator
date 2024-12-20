// Determina como as regras da física funcionam no mundo

#pragma once

// Definições padrões da física
const double ELASTIC_COEFFICIENT = 1.f;

void BodyElasticCollision(double& velX1, double& velY1, double& velX2, double& velY2); // usado para calcular as novas velocidades de um corpo após uma colisão
void ApplyTorqueByCollision(double& velAngle1, double& velAngle2, double x1, double y1, double x2, double y2, double size1, double size2); // aplica velocidade angular aos objetos
