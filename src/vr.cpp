#include "vr.h"

VRManager::VRManager() {

}

VRManager::~VRManager() {

}

int VRManager::setup() {
    vr::EVRInitError initError;

    if(!vr::VR_IsHmdPresent()) {
        printf("Headset is not connected\n");
        return 1;
    }

    if(!vr::VR_IsRuntimeInstalled()) {
        printf("OpenVR runtime not installed\n");
        return 2;
    }

    //maybe change to XR scene?
    vrSystem = vr::VR_Init(&initError, vr::EVRApplicationType::VRApplication_Scene);

    if(initError) {
        printf("OpenVR Initialization failure: %s\n", vr::VR_GetVRInitErrorAsEnglishDescription(initError));
        return 3;
    }

    if(!vr::VRCompositor()) {
        printf("Compositor wasn't\n");
        return 4;
    }

    vr::VRInput()->SetActionManifestPath("C:/Users/Admin/Documents/manifest.json");

    vr::VRInput()->GetActionHandle("/actions/main/in/place", &actionPlace);
	vr::VRInput()->GetActionHandle("/actions/main/in/break", &actionBreak);
	vr::VRInput()->GetActionHandle("/actions/main/in/move", &actionMove);
	vr::VRInput()->GetActionSetHandle("/actions/main", &actionSetMain);

    pose = new vr::TrackedDevicePose_t[vr::k_unMaxTrackedDeviceCount];
    actionSet = new vr::VRActiveActionSet_t[2];
    tracked = new glm::mat4[vr::k_unMaxTrackedDeviceCount];

    printf("OpenVR Initialized");

    int w, h;

    return 0;
}