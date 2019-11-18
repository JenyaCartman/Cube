#pragma once
#include "Matrix.h"

Matrix GetTranslationMatrix(float x, float y, float z)
{
    Matrix mat({ 1, 0, 0, x },
        { 0, 1, 0, y },
        { 0, 0, 1, z },
        { 0, 0, 0, 1 });

    return mat;
}

Matrix GetScalingMatrix(float x, float y, float z)
{
    Matrix mat({ x, 0, 0, 0 },
        { 0, y, 0, 0 },
        { 0, 0, z, 0 },
        { 0, 0, 0, 1 });

    return mat;
}

Matrix GetRotationMatrixByX(float angle)
{
    Matrix mat({ 1, 0, 0, 0 },
        { 0, SDL_cosf(angle), -SDL_sinf(angle), 0 },
        { 0, SDL_sinf(angle), SDL_cosf(angle), 0 },
        { 0, 0, 0, 1 });

    return mat;
}

Matrix GetRotationMatrixByY(float angle)
{
    Matrix mat({ SDL_cosf(angle), 0, SDL_sinf(angle), 0 },
        { 0, 1, 0, 0 },
        { -SDL_sinf(angle), 0, SDL_cosf(angle), 0 },
        { 0, 0, 0, 1 });

    return mat;
}

Matrix GetRotationMatrixByZ(float angle)
{
    Matrix mat({ SDL_cosf(angle), -SDL_sinf(angle), 0, 0 },
        { SDL_sinf(angle), SDL_cosf(angle), 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 });

    return mat;
}

Matrix GetViewMatrix(const Vector& eye, float pitch, float yaw)
{
    float cosPitch = SDL_cosf(pitch);
    float sinPitch = SDL_sinf(pitch);
    float cosYaw = SDL_cosf(yaw);
    float sinYaw = SDL_sinf(yaw);

    Vector xAxis = { cosYaw, 0, -sinYaw, 0 };
    Vector yAxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch, 0 };
    Vector zAxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw, 0 };

    Matrix orientation({ xAxis.v[0], xAxis.v[1], xAxis.v[2], 0 },
        { yAxis.v[0], yAxis.v[1], yAxis.v[2], 0 },
        { zAxis.v[0], zAxis.v[1], zAxis.v[2], 0 },
        { 0, 0, 0, 1 });

    Matrix translation({ 1, 0, 0, -eye.v[0] },
        { 0, 1, 0, -eye.v[1] },
        { 0, 0, 1, -eye.v[2] },
        { 0, 0, 0, 1 });

    return orientation * translation;
}

Matrix GetViewMatrix(const Vector& eye, const Vector& at, const Vector& up)
{
    Vector n({ eye.v[0] - at.v[0], eye.v[1] - at.v[1], eye.v[2] - at.v[2], eye.v[3] - at.v[3] });
    n.Normalize();

    Vector u(up.CrossProduct(n));
    u.Normalize();

    Vector v(n.CrossProduct(u));
    v.Normalize();

    Matrix orientation({ u.v[0], u.v[1], u.v[2], 0 },
        { v.v[0], v.v[1], v.v[2], 0 },
        { n.v[0], n.v[1], n.v[2], 0 },
        { 0, 0, 0, 1 });

    Matrix translation({ 1, 0, 0, -eye.v[0] },
        { 0, 1, 0, -eye.v[1] },
        { 0, 0, 1, -eye.v[2] },
        { 0, 0, 0, 1 });

    return orientation * translation;
}

Matrix GetProjectionMatrix(float fovy, float aspect, float near, float far)
{
    Matrix resultMatrix({ 1 / (aspect * SDL_tanf(fovy / 2)), 0, 0, 0 },
        { 0, 1 / (SDL_tanf(fovy / 2)), 0, 0 },
        { 0, 0, -((far + near) / (far - near)), -((2 * far * near) / (far - near)) },
        { 0, 0, -1, 0 });

    return resultMatrix;
}

float DegreeToRadian(float degree)
{
    return degree * (M_PI / 180);
}