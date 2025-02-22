#include "Cube.h"

namespace isaacGraphicsEngine
{
    Cube::Cube(const glm::vec3& position)
        : m_Position(position)
    {
        // Set index count for our cube (36 indices)
        m_IndicesCount = 36;

        // Create the VertexArray
        m_VertexArray = std::make_unique<VertexArray>();

        // Create the VertexBuffer with our vertex data
        m_VertexBuffer = std::make_unique<VertexBuffer>(m_CubeVertices, sizeof(m_CubeVertices));

        // Define the vertex layout: 3 floats for position, 3 for normal
        VertexBufferLayout vb_layout;
        vb_layout.Push<float>(3); // Positions
        vb_layout.Push<float>(3); // Normals
        m_VertexArray->AddBuffer(*m_VertexBuffer, vb_layout);

        // Create the IndexBuffer with our index data
        m_IndexBuffer = std::make_unique<IndexBuffer>(m_CubeIndices, m_IndicesCount);

        m_Color = DEFAULT_COLOR;
        m_Scale = glm::vec3(1.0f);
        m_Rotation = glm::vec3(0.0f);
    }

    Cube::~Cube()
    {
        // Resources are managed by unique_ptr.
    }

    void Cube::Update()
    {
        // (Update logic if necessary)
    }

    void Cube::Render(const Renderer& renderer, Shader& shader, const glm::mat4& view, const glm::mat4& projection)
    {
        // Compute model matrix
        auto model = GetModelMatrix();

        // Bind shader and set uniforms
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setVec3("objectColor", m_Color);

        // Render using indexed drawing:
        renderer.Render(*m_VertexArray, *m_IndexBuffer, shader);
    }

    void Cube::SetScale(const glm::vec3& scale)
    {
        m_Scale = scale;
    }

    void Cube::SetRotation(const glm::vec3& rotation)
    {
        m_Rotation = rotation;
    }

    glm::mat4 Cube::GetModelMatrix() const
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, m_Position);
        model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, m_Scale);
        return model;
    }
}
