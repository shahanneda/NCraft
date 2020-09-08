#include "UIRenderer.h"
#include <vector>
#include "glm/gtc/matrix_transform.hpp"

using glm::vec2;
using glm::vec3;
using std::vector;

UIRenderer::UIRenderer() : uiBuffer(), uiShader("shaders/ui.vert", "shaders/ui.frag")
{
    uiBuffer.BindVertexArrayBuffer();
    uiBuffer.PutVertexData(verts, indices, textures);
    std::cout << glGetError() << std::endl;
}

void UIRenderer::Render()
{

    uiBuffer.BindVertexArrayBuffer();
    uiShader.Bind();

    glm::mat4 model = glm::mat4(1.0f); // model = local space to world space
    model = glm::translate(model, vec3(0, 0, 0));

    std::cout << glGetError() << std::endl;
    uiShader.setMat4f("model", model);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    std::cout << glGetError() << std::endl;
    uiBuffer.UnbindVertexArrayBuffer();
}