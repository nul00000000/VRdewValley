#pragma once

#include <stdio.h>
#include "openvr_mingw.hpp"
#include "glm/glm.hpp"
#include <glm/ext/matrix_transform.hpp>
#include "fbo.h"
#include "shader.h"
#include "world.h"

typedef struct {
    glm::vec3 pos;
    glm::quat rot;
    glm::vec3 scale; //this cannot possibly do anything
} TrackedDevice;

class VRManager {
    public:
        VRManager(void (*renderFunc)(BasicShader* shader));
        ~VRManager();

        TrackedDevice leftController;
        TrackedDevice rightController;

        int setup();
        
        void updateInput();
        void render(glm::vec3 camPos, BasicShader* shader);
    private:
        void (*renderFunc)(BasicShader* shader);

        vr::Texture_t leftTexture;
        vr::Texture_t rightTexture;
        
        vr::IVRSystem* vrSystem;
        vr::TrackedDevicePose_t* pose;
        vr::VRActiveActionSet_t* actionSet;
        
        vr::VRActionHandle_t actionPlace;
        vr::VRActionHandle_t actionBreak;
        vr::VRActionHandle_t actionMove;
        
        vr::VRActionSetHandle_t actionSetMain;
        
        glm::mat4* tracked;
        
        FBO* leftFBO;
        FBO* rightFBO;

        glm::quat rotL;
        glm::quat rotR;

        glm::mat4 eyes[2];

        void createEyesViewMatrix(glm::vec3 translation, glm::mat4 hmdTrans);
        void renderWithOverlay(glm::vec3 camPos, BasicShader* shader);
};

glm::mat4 hmdToGLM(vr::HmdMatrix44_t hmd);
glm::mat4 hmdToGLM(vr::HmdMatrix34_t hmd);
