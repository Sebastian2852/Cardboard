#include "../Primitives.hpp"
#include "glad/glad.h"

namespace Cardboard
{
    Triangle::Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 color)
        : m_Color(color)
    {
        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        glGenBuffers(1, &m_VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

        float vertexArray[3 * 6] = {
            v1.x, v1.y, v1.z, color.x, color.y, color.z,
            v2.x, v2.y, v2.z, color.x, color.y, color.z,
            v3.x, v3.y, v3.z, color.x, color.y, color.z
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, nullptr);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
    }

    void Triangle::UpdateVertexPositions(Vector3 v1, Vector3 v2, Vector3 v3)
    {
        float vertexArray[3 * 6] = {
            v1.x, v1.y, v1.z, m_Color.x, m_Color.y, m_Color.z,
            v2.x, v2.y, v2.z, m_Color.x, m_Color.y, m_Color.z,
            v3.x, v3.y, v3.z, m_Color.x, m_Color.y, m_Color.z
        };

        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexArray), vertexArray);
    }

    void Triangle::Render()
    {
        glBindVertexArray(m_VertexArray);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    Triangle::~Triangle()
    {
        glDeleteBuffers(1, &m_VertexBuffer);
        glDeleteVertexArrays(1, &m_VertexArray);
    }
}
