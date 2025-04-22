#pragma once

#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>
#include <GraphicsAPI_OpenGL.h>

class VRManager {
    public:
        VRManager(GraphicsAPI_Type apiType);
        ~VRManager();

        void run();
    private:
        void CreateInstance();
        void DestroyInstance();
        void CreateDebugMessager();
        void DestroyDebugMessager();
        void GetInstanceProperties();
        void GetSystemID();
        void PollSystemEvents();

        XrInstance xrInstance = {};
        std::vector<const char *> activeAPILayers = {};
        std::vector<const char *> activeInstanceExtensions = {};
        std::vector<std::string> apiLayers = {};
        std::vector<std::string> instanceExtensions = {};

        XrDebugUtilsMessengerEXT debugUtilsMessenger = {};

        XrFormFactor formFactor = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;
        XrSystemId systemID = {};
        XrSystemProperties systemProperties = {XR_TYPE_SYSTEM_PROPERTIES};

        GraphicsAPI_Type apiType = UNKNOWN;

        bool applicationRunning = true;
        bool sessionRunning = false;
};