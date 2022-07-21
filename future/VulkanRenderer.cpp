#include "VulkanRenderer.h"


engine::VulkanRenderer::VulkanRenderer(uint32_t width, uint32_t height) : Renderer(width, height) {
    initVulkan();
}

engine::VulkanRenderer::~VulkanRenderer() {

    delete m_window;

    destroyVulkan();
}

void engine::VulkanRenderer::update() {
    m_window->update();
}

void engine::VulkanRenderer::prepass() {

}

void engine::VulkanRenderer::initVulkan() {
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    // Checking validation layers!
    {
        if (enableValidationLayers && !checkValidationLayerSupport()) {
            logErrorAndCrash("Validation layers requested, but not available!");
        }
    }

    // Creating an instance!!! (All extensions wanted go in here)
    {
        VkApplicationInfo applicationInfo{};
        applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.pApplicationName = APPLICATION_NAME;
        applicationInfo.applicationVersion = APPLICATION_VERSION;
        applicationInfo.pEngineName = ENGINE_NAME;
        applicationInfo.engineVersion = ENGINE_VERSION;
        applicationInfo.apiVersion = VK_API_VERSION_1_2;


        VkInstanceCreateInfo instanceCreateInfo{};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pApplicationInfo = &applicationInfo;


        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        std::vector<const char*> wantedExtensions{ };

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        for (uint32_t i = 0; i < glfwExtensionCount; i++) {
            wantedExtensions.push_back(glfwExtensions[i]);
        }

        // Checking if all the extensions wanted are supported!
        // DONT RLLY NEED - i mean, it kinda works without it ig?
        /*{
            uint32_t availableExtensionCount = 0;
            vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, nullptr);
            std::vector<VkExtensionProperties> extensionsAvailable(availableExtensionCount);
            vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, extensionsAvailable.data());
            for (const auto& wantedExtension : wantedExtensions) {
                bool isSupported = false;
                for (const auto& extension : extensionsAvailable) {
                    if (extension.extensionName == wantedExtension) {
                        isSupported = true;
                        break;
                    }
                }
                if (!isSupported) {
                    logError("Instance Extension is not supported by this graphics card: " + std::string(wantedExtension));
                }
            }
        }*/

        instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(wantedExtensions.size());
        instanceCreateInfo.ppEnabledExtensionNames = wantedExtensions.data();

        if (enableValidationLayers) {
            instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            instanceCreateInfo.enabledLayerCount = 0;
        }

        if (vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance) != VK_SUCCESS) {
            logErrorAndCrash("Could not create Vulkan Instance!");
        }

    }

    // Creating the window and its surface!
    {
        m_window = new Window(m_width, m_height, APPLICATION_NAME, &m_instance);
    }

    // Choosing a physical device to use!!
    {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            logErrorAndCrash("There are no GPUs with Vulkan support :((");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

        // rating the device
        uint32_t rate = 0;
        for (const auto& device : devices) {
            uint32_t deviceRate = ratePhyiscalDevice(device);
            if (rate < deviceRate) {
                physicalDevice = device;
                rate = deviceRate;
            }
        }
        if (rate <= 0) {
            logErrorAndCrash("Can't find a suitable GPU that will run this engine properly.");
        }

    }

    // Create a logical device!
    {
        // Queue Families being identified and sent to vulkan
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        auto uniqueQueueFamilies = { m_queueFamilyIndices.graphicsFamily.value(), m_queueFamilyIndices.presentFamily.value() };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};

        // Creating device
        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        // Validation Layers?
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        // Yay ez device creation
        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
            logErrorAndCrash("Cannot create Device :((");
        }

        // Queue Family Handles
        vkGetDeviceQueue(m_device, m_queueFamilyIndices.graphicsFamily.value(), 0, &m_graphicsQueue);
        vkGetDeviceQueue(m_device, m_queueFamilyIndices.presentFamily.value(), 0, &m_presentQueue);

    }

}

uint32_t engine::VulkanRenderer::ratePhyiscalDevice(const VkPhysicalDevice& device) {
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        // Graphics Family
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            m_queueFamilyIndices.graphicsFamily = i;
        }

        // Present Family
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, *m_window->getSurface(), &presentSupport);
        if (presentSupport) {
            m_queueFamilyIndices.presentFamily = i;
        }

        if (m_queueFamilyIndices.isComplete()) {
            break;
        }
        i++;
    }

    if (!m_queueFamilyIndices.isComplete()) {
        return 0;
    }

    // Check device extension support!
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }

    if (!requiredExtensions.empty()) {
        return 0;
    }

    // Device properties and features
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    uint32_t rating = 0;

    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        rating += 1500;
    }

    rating += deviceProperties.limits.maxColorAttachments * 1000;
    rating += deviceProperties.limits.maxImageDimension1D;
    rating += deviceProperties.limits.maxImageDimension2D;
    rating += deviceProperties.limits.maxImageDimension3D;
    rating += deviceProperties.limits.maxMemoryAllocationCount;

    if (!deviceFeatures.geometryShader || !deviceFeatures.tessellationShader) {
        return 0;
    }

    logInfo(std::string(deviceProperties.deviceName) + "\t rating:" + std::to_string(rating));

    return rating;
}

bool engine::VulkanRenderer::checkValidationLayerSupport() {
    uint32_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;
}

void engine::VulkanRenderer::destroyVulkan() {
    vkDestroyDevice(m_device, nullptr);

    // Make sure the windows are destroyed before this ever gets called
    vkDestroyInstance(m_instance, nullptr);
}

engine::Window* engine::VulkanRenderer::getWindow() {
    return m_window;
}
