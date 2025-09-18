#include "glad/glad.h"
#include <Cardboard.hpp>
#include <vector>

class ChessBoardLayer : public Cardboard::Layer
{
public:
    ChessBoardLayer()
        : Layer("Chess board layer")
    {
        LOG_TRACE("Created ChessBoard layer");

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        std::vector<float> vertices;

        float squareSize = 1.0f / 8.0f;

        // Generate 64 squares
        for (int row = 0; row < 8; ++row)
        {
            for (int col = 0; col < 8; ++col)
            {
                float x0 = col * squareSize;
                float y0 = row * squareSize;
                float x1 = x0 + squareSize;
                float y1 = y0 + squareSize;

                // Two triangles per square
                vertices.insert(vertices.end(), {
                    x0, y0, 0.0f,
                    x1, y0, 0.0f,
                    x1, y1, 0.0f,

                    x0, y0, 0.0f,
                    x1, y1, 0.0f,
                    x0, y1, 0.0f
                    });
            }
        }

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

        std::string vertexSrc = R"(
            #version 460 core
            layout(location = 0) in vec3 a_Position;
            out vec2 uv;
            void main() {
                gl_Position = vec4(a_Position * 2.0 - 1.0, 1.0);
                uv = a_Position.xy;
            }
        )";

        std::string fragmentSrc = R"(
            #version 460 core
            out vec4 color;
            in vec2 uv;
            void main() {
                int x = int(floor(uv.x * 8.0));
                int y = int(floor(uv.y * 8.0));
                if ((x + y) % 2 == 0)
                    color = vec4(1.0); // white
                else
                    color = vec4(0.0, 0.0, 0.0, 1.0); // black
            }
        )";

        m_Shader.reset(new Cardboard::Shader(vertexSrc, fragmentSrc));
    }

    void OnRender() override
    {
        m_Shader->Bind();
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 64 * 6); // 6 vertices per square
    }

private:
    unsigned int m_VAO, m_VBO;
    std::unique_ptr<Cardboard::Shader> m_Shader;
};