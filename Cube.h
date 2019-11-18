#pragma once
#include "Math.h"
constexpr int WIDTH = 800, HEIGHT = 600;

class Cube
{
public:
    Cube(const Vector& position, const Vector& scale, float angle, const Vector& color = {0xFF, 0xFF, 0xFF, 0xFF})
        : m_position(position), m_scale(scale), m_angle(angle), m_color(color)
    {}

    Cube() : m_position({ 0, 0, 0, 1 }), m_scale({ 0, 0, 0, 0 }), m_angle(0), m_color({ 0xFF, 0xFF, 0xFF, 0xFF })
    {}

    Vector& operator[](int index)
    {
        return m_points[index];
    }

    void RenderCube()
    {
        Matrix translation = GetTranslationMatrix(m_position[0], m_position[1], m_position[2]);
        Matrix rotation = GetRotationMatrixByY(DegreeToRadian(m_angle));
        Matrix scale = GetScalingMatrix(m_scale[0], m_scale[1], m_scale[2]);

        Matrix model = translation * rotation * scale;
        Matrix view = GetViewMatrix({ 0, 0, 0, 1 }, { 0, 0, 1, 0 }, { 0, 1, 0, 0 });
        Matrix projection = GetProjectionMatrix(DegreeToRadian(90), static_cast<float>(WIDTH) / HEIGHT, 1, 10000);

        Matrix mvp = view * projection * model;

        Cube baseCube;

        for (int i = 0; i < 8; ++i)
        {
            m_points[i] = mvp * baseCube.m_points[i];
            
            m_points[i][0] = (m_points[i][0] / m_points[i][3]);
            m_points[i][1] = (m_points[i][1] / m_points[i][3]);

            m_points[i][0] = (m_points[i][0] + 1.0f) / 2.0f * WIDTH;
            m_points[i][1] = (m_points[i][1] + 1.0f) / 2.0f * HEIGHT;
        }
    }

public:
    float GetAngle() const { return m_angle; }
    void SetAngle(float angle) { m_angle = angle; }
    Vector GetColor() const { return m_color; }
    void SetColor(const Vector& color) { m_color = color; }
    Vector GetPosition() const { return m_position; }
    void SetPosition(const Vector& position) { m_position = position; }

private:
    Vector m_points[8] = {{-1, -1, -1, 1},
                        {-1, 1, -1, 1},
                        {1, 1, -1, 1},
                        {1, -1, -1, 1},
                        {-1, -1, 1, 1},
                        {-1, 1, 1, 1},
                        {1, 1, 1, 1},
                        {1, -1, 1, 1}};

    float m_angle;
    Vector m_position;
    Vector m_scale;

    Vector m_color;
};