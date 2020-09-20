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
    glBindBuffer(GL_ARRAY_BUFFER, uiBuffer.vertexArrayBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiBuffer.elementsBufferId);
    uiShader.Bind();

    RenderItemsOnHotbar();
    RenderCrosshair();
    RenderHotbar();


    uiBuffer.UnbindVertexArrayBuffer();
}


void UIRenderer::RenderCrosshair(){
    // Crosshair
    glEnable(GL_BLEND);
    crosshair.BindTexture();

    uiBuffer.BindVertexArrayBuffer();
    uiBuffer.PutVertexData(verts, indices, textures);
    uiBuffer.BindVertexArrayBuffer();

    glm::mat4 model = glm::mat4(1.0f); // model = local space to world space
    model = glm::scale(model, vec3(0.05,0.05,0));
    model = glm::translate(model, vec3(-0.5, -0.5, 0));
    uiShader.setMat4f("model", model);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void UIRenderer::RenderHotbar(){
    // hotbar
    glEnable(GL_BLEND);
    hotbar.BindTexture();
    glm::mat4 model = glm::mat4(1.0f); // model = local space to world space
    model = glm::translate(model, vec3(0, -1.f, 0));
    model = glm::scale(model, vec3(1.0f,0.2,0));
    uiShader.setMat4f("model", model);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void UIRenderer::RenderItemsOnHotbar(){
    // Items
    glDisable(GL_BLEND);
    atlas.BindTexture();

    vector<vec3> groupedVert;
    vector<int> groupedIndices;
    vector<vec2> groupedTexts;

    for(int i =0; i<items.size(); i++){
        BLOCK_TYPE type = items[i];

        // copy the originals
        vector<vec3> newVert; 
        vector<int> newIndices;

        for(auto vert : verts){
            newVert.push_back(vec3(vert.x + i * 1.0f, vert.y, vert.z));
        }

        int indicesShift = verts.size() * i; // because each face has vert.size and we want to add that to all our indices
        for(auto index : indices){
            newIndices.push_back(index + indicesShift);
        }
        

        std::vector<glm::vec2> texts = TextureManager::GetTextureForBlockFace(type, POS_Y);


        // insert all of our data into the grouped
        groupedVert.insert(groupedVert.end(), newVert.begin(), newVert.end());
        groupedIndices.insert(groupedIndices.end(), newIndices.begin(), newIndices.end());
        groupedTexts.insert(groupedTexts.end(), texts.begin(), texts.end());
    }


    uiBuffer.BindVertexArrayBuffer();
    uiBuffer.PutVertexData(groupedVert, groupedIndices, groupedTexts);
    uiBuffer.BindVertexArrayBuffer();

    glm::mat4 model = glm::mat4(1.0f); // model = local space to world space
    model = glm::translate(model, vec3(0, -1.f, 0));
    model = glm::scale(model, vec3(0.20f,0.20f, 0));
    uiShader.setMat4f("model", model);
    glDrawElements(GL_TRIANGLES, groupedIndices.size(), GL_UNSIGNED_INT, 0);
}