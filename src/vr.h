#pragma once

#include <stdio.h>
#include "openvr.h"
#include "glm/glm.hpp"

class VRManager {
    public:
        VRManager();
        ~VRManager();

        int setup();
    private:
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
};