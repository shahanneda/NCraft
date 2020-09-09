#include "UIRenderer.h"
#include <vector>
#include "glm/gtc/matrix_transform.hpp"

using glm::vec2;
using glm::vec3;
using std::vector;

UIRenderer::UIRenderer() : uiBuffer(), uiShader("shaders/ui.vert", "shaders/ui.frag"), crosshair("resources/crosshair.png")
{
	uiShader.Bind();
    uiBuffer.BindVertexArrayBuffer();
    uiBuffer.PutVertexData(verts, indices, textures);
	uiBuffer.BindVertexArrayBuffer();
}

void UIRenderer::Render()
{
    crosshair.BindTexture();
    uiBuffer.BindVertexArrayBuffer();
    uiShader.Bind();

    glEnable(GL_BLEND);
    glm::mat4 model = glm::mat4(1.0f); // model = local space to world space
    model = glm::scale(model, vec3(0.05,0.05,0));
    model = glm::translate(model, vec3(-0.5, -0.5, 0));

    uiShader.setMat4f("model", model);

	uiBuffer.BindVertexArrayBuffer();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    uiBuffer.UnbindVertexArrayBuffer();
}