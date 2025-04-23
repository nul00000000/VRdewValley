#include "vr.h"

#include "Common/OpenXRHelper.h"
#include "DebugOutput.h"

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

    // Get all the API Layers from the OpenXR runtime.
    uint32_t apiLayerCount = 0;
    std::vector<XrApiLayerProperties> apiLayerProperties;
    OPENXR_CHECK(xrEnumerateApiLayerProperties(0, &apiLayerCount, nullptr), "Failed to enumerate ApiLayerProperties.");
    apiLayerProperties.resize(apiLayerCount, {XR_TYPE_API_LAYER_PROPERTIES});
    OPENXR_CHECK(xrEnumerateApiLayerProperties(apiLayerCount, &apiLayerCount, apiLayerProperties.data()), "Failed to enumerate ApiLayerProperties.");

    // Check the requested API layers against the ones from the OpenXR. If found add it to the Active API Layers.
    for (auto &requestLayer : apiLayers) {
        for (auto &layerProperty : apiLayerProperties) {
            // strcmp returns 0 if the strings match.
            if (strcmp(requestLayer.c_str(), layerProperty.layerName) != 0) {
                continue;
            } else {
                activeAPILayers.push_back(requestLayer.c_str());
                break;
            }
        }
    }

    // Get all the Instance Extensions from the OpenXR instance.
    uint32_t extensionCount = 0;
    std::vector<XrExtensionProperties> extensionProperties;
    OPENXR_CHECK(xrEnumerateInstanceExtensionProperties(nullptr, 0, &extensionCount, nullptr), "Failed to enumerate InstanceExtensionProperties.");
    extensionProperties.resize(extensionCount, {XR_TYPE_EXTENSION_PROPERTIES});
    OPENXR_CHECK(xrEnumerateInstanceExtensionProperties(nullptr, extensionCount, &extensionCount, extensionProperties.data()), "Failed to enumerate InstanceExtensionProperties.");

    // Check the requested Instance Extensions against the ones from the OpenXR runtime.
    // If an extension is found add it to Active Instance Extensions.
    // Log error if the Instance Extension is not found.
    for (auto &requestedInstanceExtension : instanceExtensions) {
        bool found = false;
        for (auto &extensionProperty : extensionProperties) {
            // strcmp returns 0 if the strings match.
            if (strcmp(requestedInstanceExtension.c_str(), extensionProperty.extensionName) != 0) {
                continue;
            } else {
                activeInstanceExtensions.push_back(requestedInstanceExtension.c_str());
                found = true;
                break;
            }
        }
        if (!found) {
            XR_TUT_LOG_ERROR("Failed to find OpenXR instance extension: " << requestedInstanceExtension);
        }
    }

    XrInstanceCreateInfo instanceCI{XR_TYPE_INSTANCE_CREATE_INFO};
    instanceCI.createFlags = 0;
    instanceCI.applicationInfo = appInfo;
    instanceCI.enabledApiLayerCount = static_cast<uint32_t>(activeAPILayers.size());
    instanceCI.enabledApiLayerNames = activeAPILayers.data();
    instanceCI.enabledExtensionCount = static_cast<uint32_t>(activeInstanceExtensions.size());
    instanceCI.enabledExtensionNames = activeInstanceExtensions.data();
    OPENXR_CHECK(xrCreateInstance(&instanceCI, &xrInstance), "Failed to create Instance.");
}

void VRManager::DestroyInstance() {
    OPENXR_CHECK(xrDestroyInstance(xrInstance), "Failed to destroy Instance.");
}

void VRManager::GetInstanceProperties() {
    XrInstanceProperties instanceProperties{XR_TYPE_INSTANCE_PROPERTIES};
    OPENXR_CHECK(xrGetInstanceProperties(xrInstance, &instanceProperties), "Failed to get InstanceProperties.");

    XR_TUT_LOG("OpenXR Runtime: " << instanceProperties.runtimeName << " - "
                                << XR_VERSION_MAJOR(instanceProperties.runtimeVersion) << "."
                                << XR_VERSION_MINOR(instanceProperties.runtimeVersion) << "."
                                << XR_VERSION_PATCH(instanceProperties.runtimeVersion));
}