#include "hud.h"

namespace Game
{
    Crosshair::Crosshair(Rendering::Application& screen)
    {
        this->squareCenter.x = screen.width / 2;
        this->squareCenter.y = screen.height / 2;
    }

    void Crosshair::drawSquare()
    {
        ImDrawList* draw_list = ImGui::GetForegroundDrawList();

        draw_list->AddRectFilled(ImVec2(this->squareCenter.x - this->squareSize * 0.5f,
            this->squareCenter.y - this->squareSize * 0.5f),
            ImVec2(this->squareCenter.x + this->squareSize * 0.5f, squareCenter.y + squareSize * 0.5f),
            IM_COL32(255, 0, 0, 255)); // Rouge pour visibilité
    }

    void Crosshair::drawCrosshair()
    {
        ImVec2 windowCenter = ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
        ImDrawList* draw_list = ImGui::GetForegroundDrawList();

        // Dessinez un carré ou un cercle
        if (this->isOverSquare) {
            // Crosshair carré
            draw_list->AddRectFilled(ImVec2(windowCenter.x - this->squareSize, windowCenter.y - this->squareSize),
                ImVec2(windowCenter.x + this->squareSize, windowCenter.y + this->squareSize),
                IM_COL32(255, 255, 255, 255)); // Blanc
        }
        else {
            // Crosshair rond
            draw_list->AddCircle(windowCenter, this->squareSize, IM_COL32(255, 255, 255, 255), 12); // Blanc
        }
    }

	Phone::Phone(float posX, float posY, float posZ, Resources::ResourcesManager& manager)
	{
		this->SetModel(manager.CreateRessource<Resources::Model>("Assets/Meshes/sphere.obj"));

        this->local *= LibMath::Mat4::Translate(LibMath::Vec3(posX, posY, posZ));

        this->local *= LibMath::Mat4::Scale(LibMath::Vec3(0.25, 0.3, 0.25));
    }
}



//#include <GLFW/glfw3.h>
//#include <irrKlang.h>
//#include "stb_image.h"
//#include <iostream>
//
//using namespace irrklang;
//
//// Function to load texture 
//GLuint loadTexture(const char* filename) {
//    int width, height, channels;
//    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
//    if (!data) {
//        std::cerr << "Error loading texture: " << filename << std::endl;
//        return 0;
//    }
//
//    GLuint textureID;
//    glGenTextures(1, &textureID);
//    glBindTexture(GL_TEXTURE_2D, textureID);
//
//    // Set texture parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    // Choose format with number of channels
//    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
//    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//    glGenerateMipmap(GL_TEXTURE_2D);
//
//    glBindTexture(GL_TEXTURE_2D, 0);
//    stbi_image_free(data);
//    return textureID;
//}
//
//// Function to trigger the screamer
//void triggerScreamer(GLFWwindow* window, GLuint textureID, ISoundEngine* soundEngine) {
//    double startTime = glfwGetTime(); // Start time for screamer
//    soundEngine->play2D("scream.mp3", false); // Play sound effect
//
//    while (!glfwWindowShouldClose(window) && (glfwGetTime() - startTime) < 10.0) { // Run for 10 seconds
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // Display the texture
//        glEnable(GL_TEXTURE_2D);
//        glBindTexture(GL_TEXTURE_2D, textureID);
//        glBegin(GL_QUADS);
//        glTexCoord2f(0.0, 0.0); glVertex2f(-1.0f, -1.0f);
//        glTexCoord2f(1.0, 0.0); glVertex2f(1.0f, -1.0f);
//        glTexCoord2f(1.0, 1.0); glVertex2f(1.0f, 1.0f);
//        glTexCoord2f(0.0, 1.0); glVertex2f(-1.0f, 1.0f);
//        glEnd();
//        glBindTexture(GL_TEXTURE_2D, 0);
//        glDisable(GL_TEXTURE_2D);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//}

//-----------------------------------------------------------------------------------------//


