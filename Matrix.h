#pragma once
#include "Vector.h"

struct Matrix
{
    Vector m[4];

    Matrix()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m[i][j] = 0.0f;
            }
        }

        for (int i = 0; i < 4; i++)
        {
            m[i][i] = 1.0f;
        }
    }

    Matrix(const Vector& row0, const Vector& row1, const Vector& row2, const Vector& row3)
    {
        m[0] = row0;
        m[1] = row1;
        m[2] = row2;
        m[3] = row3;
    }

    Vector& operator[](int index)
    {
        return m[index];
    }

    const Vector& operator[](int index) const
    {
        return m[index];
    }

    Matrix operator*(const Matrix& rhs)
    {
        Matrix resultMatrix;

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                resultMatrix[i][j] = (m[i][0] * rhs[0][j]) + (m[i][1] * rhs[1][j]) + (m[i][2] * rhs[2][j]) + (m[i][3] * rhs[3][j]);
            }
        }

        return resultMatrix;
    }

    Vector operator*(Vector& vector)
    {
        Vector resultVector;

        for (int i = 0; i < 4; ++i)
        {
            resultVector[i] = (m[i][0] * vector[0]) + (m[i][1] * vector[1]) + (m[i][2] * vector.v[2]) + (m[i][3] * vector.v[3]);
        }

        return resultVector;
    }
};