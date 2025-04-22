#include "vr.h"

#include "Common/OpenXRHelper.h"

VRManager::VRManager(GraphicsAPI_Type apiType): apiType(apiType) {
    
}

VRManager::~VRManager() {

}

void VRManager::run() {
    CreateInstance();
}

void VRManager::CreateInstance() {
    XrApplicationInfo appInfo;
    strncpy(appInfo.applicationName, "VRDewValley", XR_MAX_APPLICATION_NAME_SIZE);
    appInfo.applicationVersion = 1;
    strncpy(appInfo.engineName, "SPEX REAL Engine", XR_MAX_ENGINE_NAME_SIZE);
    //Real Eel All L
    appInfo.engineVersion = 1;
    appInfo.apiVersion = XR_CURRENT_API_VERSION;

    instanceExtensions.push_back(XR_EXT_DEBUG_UTILS_EXTENSION_NAME);
    // Ensure m_apiType is already defined when we call this line.
    instanceExtensions.push_back(GetGraphicsAPIInstanceExtensionString(apiType));
}