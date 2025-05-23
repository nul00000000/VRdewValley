#include "vr.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

extern World *world;

VRManager::VRManager(void (*renderFunc)(BasicShader* shader)) {
    this->renderFunc = renderFunc;

    eyes[0] = glm::mat4(1);
    eyes[1] = glm::mat4(1);
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

    // //maybe change to XR scene?
    vrSystem = vr::VR_Init(&initError, vr::EVRApplicationType::VRApplication_Scene);

    if(initError != vr::EVRInitError::VRInitError_None) {
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

    uint32_t w, h;
    vrSystem->GetRecommendedRenderTargetSize(&w, &h);
	rightFBO = new FBO(w, h);
	leftFBO = new FBO(w, h);
    printf("OpenVR Initialized\n");
	

    return 0;
}

glm::mat4 hmdToGLM(vr::HmdMatrix44_t hmd) {
	glm::mat4 dest;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			dest[i][j] = hmd.m[j][i];
		}
	}
	return dest;
}

glm::mat4 hmdToGLM(vr::HmdMatrix34_t hmd) {
	glm::mat4 dest;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			dest[i][j] = hmd.m[j][i];
		}
		dest[i][3] = 0.0f;
	}
	dest[3][3] = 1.0f;
	return dest;
}

void VRManager::createEyesViewMatrix(glm::vec3 translation, glm::mat4 hmdTrans) {
	eyes[0] = hmdToGLM(vrSystem->GetEyeToHeadTransform(vr::Eye_Left));
	eyes[0] = glm::translate(glm::mat4(1), translation) * hmdTrans * eyes[0];
	// eyes[0] = glm::translate(glm::mat4(1), translation) * eyes[0];
	eyes[1] = hmdToGLM(vrSystem->GetEyeToHeadTransform(vr::Eye_Right));
	eyes[1] = glm::translate(glm::mat4(1), translation) * hmdTrans * eyes[1];
	// eyes[1] = glm::translate(glm::mat4(1), translation) * eyes[1];
}

void VRManager::updateInput() {
	glm::vec3 scale;
	glm::vec3 posL;
	glm::vec3 posR;
	glm::vec3 skew;
	glm::vec4 pers;
	glm::decompose(tracked[1], scale, rotL, posL, skew, pers);
	glm::decompose(tracked[2], scale, rotR, posR, skew, pers);
	leftController.pos = posL;
	leftController.rot = rotL;
	rightController.pos = posR;
	rightController.rot = rotR;
	//rotL = glm::conjugate(rotL);
	//rotR = glm::conjugate(rotR);
}

void VRManager::renderWithOverlay(glm::vec3 camPos, BasicShader* shader) {
	glm::vec3 posL = leftController.pos+camPos;
	glm::vec3 posR = rightController.pos+camPos;
	glm::mat4 transformL = glm::translate(glm::identity<glm::mat4>(), posL);
	glm::mat4 transformR = glm::translate(glm::identity<glm::mat4>(), posR);

	world->leftHand->moveTo(posL);
	world->leftHand->setRotation(glm::eulerAngles(rotL));

	world->rightHand->moveTo(posR);
	world->rightHand->setRotation(glm::eulerAngles(rotR));
}

void VRManager::render(glm::vec3 camPos, BasicShader* shader) {
	vr::VRCompositor()->WaitGetPoses(pose, vr::k_unMaxTrackedDeviceCount, NULL, 0);
	for (int i = 0; i < vr::k_unMaxTrackedDeviceCount; i++) {
		if (pose[i].bPoseIsValid) {
			tracked[i] = hmdToGLM(pose[i].mDeviceToAbsoluteTracking);
		}
	}
    createEyesViewMatrix(camPos, tracked[vr::k_unTrackedDeviceIndex_Hmd]);
	
	glm::mat4 proj;
	proj = hmdToGLM(vrSystem->GetProjectionMatrix(vr::Eye_Right, 0.1, 1000));
    shader->loadProjection(proj);
	shader->loadCamera(eyes[1]);

	// glEnable(GL_MULTISAMPLE);
	glBindFramebuffer(GL_FRAMEBUFFER, rightFBO->rbHandle);
	glViewport(0, 0, rightFBO->width, rightFBO->height);
	renderWithOverlay(camPos, shader);
    renderFunc(shader);
    // glDisable(GL_MULTISAMPLE);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, rightFBO->rbHandle);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, rightFBO->handle);

	glBlitFramebuffer(0, 0, rightFBO->width, rightFBO->height, 0, 0, rightFBO->width, rightFBO->height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    proj = hmdToGLM(vrSystem->GetProjectionMatrix(vr::Eye_Left, 0.1, 1000));
	
	shader->loadProjection(proj);
	shader->loadCamera(eyes[0]);
	// glEnable(GL_MULTISAMPLE);
	glBindFramebuffer(GL_FRAMEBUFFER, leftFBO->rbHandle);
	glViewport(0, 0, leftFBO->width, leftFBO->height);
	renderWithOverlay(camPos, shader);
	renderFunc(shader);
	// glDisable(GL_MULTISAMPLE);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, leftFBO->rbHandle);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, leftFBO->handle);

	glBlitFramebuffer(0, 0, leftFBO->width, leftFBO->height, 0, 0, leftFBO->width, leftFBO->height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 640, 360);
	renderWithOverlay(camPos, shader);
	renderFunc(shader);

	leftTexture.eColorSpace = vr::EColorSpace::ColorSpace_Gamma;
	leftTexture.eType = vr::ETextureType::TextureType_OpenGL;
	leftTexture.handle = (void*)(uintptr_t)(leftFBO->resolveHandle);

	rightTexture.eColorSpace = vr::EColorSpace::ColorSpace_Gamma;
	rightTexture.eType = vr::ETextureType::TextureType_OpenGL;
	rightTexture.handle = (void*)(uintptr_t)(rightFBO->resolveHandle);
	vr::VRCompositor()->Submit(vr::Eye_Left, &leftTexture, NULL);
	vr::VRCompositor()->Submit(vr::Eye_Right, &rightTexture, NULL);
	glFlush();
}