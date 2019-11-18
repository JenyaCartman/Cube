#pragma once

struct Vector
{
    float v[4]; 

    Vector()
    {
        for (int i = 0; i < 4; i++)
        {
            v[i] = 0.0f;
        }
    }

    Vector(float x, float y, float z, float w)
    {
        v[0] = x;
        v[1] = y;
        v[2] = z;
        v[3] = w;
    }

    float& operator[](int index)
    {
        return v[index];
    }

    const float& operator[](int index) const
    {
        return v[index];
    }

    Vector CrossProduct(const Vector& rhs) const
    {
        Vector resultVector(v[1] * rhs[2] - v[2] * rhs[1],
                            v[2] * rhs[0] - v[0] * rhs[2],
                            v[0] * rhs[1] - v[1] * rhs[0],
                            0);

        return resultVector;
    }

    void Normalize()
    {
        float module = SDL_sqrt(SDL_pow(v[0], 2) + SDL_pow(v[1], 2) + SDL_pow(v[2], 2) + SDL_pow(v[3], 2));

        v[0] = v[0] / module;
        v[1] = v[1] / module;
        v[2] = v[2] / module;
        v[3] = v[3] / module;
    }
};