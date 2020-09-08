#include "UIRenderer.h"
#include <vector>
#include "glm/gtc/matrix_transform.hpp"

using glm::vec2;
using glm::vec3;
using std::vector;

UIRenderer::UIRenderer() : uiBuffer(), uiShader("shaders/ui.vert", "shaders/ui.frag")
{
	uiShader.Bind();
    uiBuffer.BindVertexArrayBuffer();
    uiBuffer.PutVertexData(verts, indices, textures);
	uiBuffer.BindVertexArrayBuffer();

}

void UIRenderer::Render()
{

    uiBuffer.BindVertexArrayBuffer();
    uiShader.Bind();

    glm::mat4 model = glm::mat4(1.0f); // model = local space to world space
    model = glm::translate(model, vec3(0, 0, 0));

    uiShader.setMat4f("model", model);

	uiBuffer.BindVertexArrayBuffer();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    uiBuffer.UnbindVertexArrayBuffer();
}