#include "UIRenderer.h"
#include <vector>
#include "glm/gtc/matrix_transform.hpp"
#include "../TextureManager.h"

using glm::vec2;
using glm::vec3;
using std::vector;

UIRenderer::UIRenderer() : uiBuffer(), uiShader("shaders/ui.vert", "shaders/ui.frag"), crosshair("resources/crosshair.png"),  hotbar("resources/hotbar.png"), atlas("resources/texture_atlas.png")
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
    glEnable(GL_BLEND);

    // uiBuffer.PutVertexData(verts, indices, textures);
    // Crosshair
    crosshair.BindTexture();
    glm::mat4 model = glm::mat4(1.0f); // model = local space to world space
    model = glm::scale(model, vec3(0.05,0.05,0));
    model = glm::translate(model, vec3(-0.5, -0.5, 0));
    uiShader.setMat4f("model", model);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // glDisable(GL_BLEND);
    hotbar.BindTexture();
    model = glm::mat4(1.0f); // model = local space to world space
    model = glm::translate(model, vec3(0, -1.f, 0));
    model = glm::scale(model, vec3(1.0f,0.2,0));
    uiShader.setMat4f("model", model);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // glDisable(GL_BLEND);
    // atlas.BindTexture();
    // uiBuffer.PutVertexData(verts, indices, TextureManager::GetTextureForBlockFace(DIRT,POS_X));
    // model = glm::mat4(1.0f); // model = local space to world space
    // model = glm::translate(model, vec3(0, -1.f, 0));
    // model = glm::scale(model, vec3(0.2f,0.2,0));
    // uiShader.setMat4f("model", model);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    uiBuffer.UnbindVertexArrayBuffer();
}