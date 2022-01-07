#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <iostream>
#define final consts
#define boolean bool
#include <vulkan/vulkan.h>
#include <GLFW//glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
static GLFWwindow* window;
static GLFWmonitor* monitor;
static VkInstance vkInstance;

static VkSurfaceKHR surface;

__stdcall HANDLE_PTR clPPPI(HANDLE_PTR strct, HANDLE_PTR funcPtr)
{

};

long permuteMat(long, long);

struct VkUtils2
{
	
//    private static final long[] pDebugMessenger = new long[1];
    //    X(),
    //    Y
    //    KEY(1)
	 
    static boolean debug;
    static boolean checks;
	 static void extracted();
	 static void createInstance();
	 static void createSurface();
	
};


static void setupWindow()
{
		glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_ROBUSTNESS);
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
        glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR , GLFW_RELEASE_BEHAVIOR_NONE);


        window = glfwCreateWindow(854, 480, "VKMod", monitor, 0);


        if(window == NULL) exit(1);

        glfwSetWindowShouldClose(window, false);
        glfwMakeContextCurrent(window);
}


static void extracted()
{
	 std::cout <<1<< "\n";
	 // VkUtils2::createInstance;
}

static void createInstance()
    {
       std::cout <<("Creating Instance") << "\n";
        // if (ENABLE_VALIDATION_LAYERS && !checkValidationLayerSupport())
        // {
            // System.out.println(MemSysm.stack);
            // throw new RuntimeException("Validation requested but not supported");
        // }
        // IntBuffer a = MemSysm.ints(EXTValidationFeatures.VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT, EXTValidationFeatures.VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT, EXTValidationFeatures.VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT, EXTValidationFeatures.VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT);
        // VkValidationFeaturesEXT extValidationFeatures = VkValidationFeaturesEXT.create(MemSysm.calloc(VkValidationFeaturesEXT.SIZEOF)).sType$Default()
                // .pEnabledValidationFeatures(a);

        VkApplicationInfo vkApplInfo = {
                //memSet(vkApplInfo, 0,VkApplicationInfo.SIZEOF);
                .sType=VK_STRUCTURE_TYPE_APPLICATION_INFO,
				 .pApplicationName="VKMod",
                 .applicationVersion=VK_MAKE_VERSION(1, 0, 0),
                 .pEngineName="No Engine",
                 .engineVersion=VK_MAKE_VERSION(1, 0, 0),
                 .apiVersion=VK_API_VERSION_1_2
		};
//        MemSysm.Memsys2.free(a);
        // MemSysm.Memsys2.free(vkApplInfo);
        //nmemFree(vkApplInfo);

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        VkInstanceCreateInfo InstCreateInfo = {};
//                InstCreateInfo.sType(VK10.VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO);
        InstCreateInfo.pApplicationInfo=&vkApplInfo;
		InstCreateInfo.enabledLayerCount = 0;
        // PointerBuffer glfwExtensions = getRequiredExtensions();
        InstCreateInfo.ppEnabledExtensionNames=glfwExtensions;
        // InstCreateInfo.pNext(extValidationFeatures.address());

        InstCreateInfo.enabledExtensionCount=glfwExtensionCount;
        InstCreateInfo.enabledLayerCount=0;
        // if(ENABLE_VALIDATION_LAYERS) {
            // memPutLong(InstCreateInfo.address() + VkInstanceCreateInfo.PPENABLEDLAYERNAMES, (asPointerBuffer()));
            // memPutLong(InstCreateInfo.address() + VkInstanceCreateInfo.ENABLEDLAYERCOUNT, VALIDATION_LAYERS.size());
        // }
// //            else InstCreateInfo.pNext(NULL);

        // PointerBuffer instancePtr = memPointerBuffer(MemSysm.address, 1);	
        // vkCreateInstance(InstCreateInfo, MemSysm.pAllocator, instancePtr);


        vkCreateInstance(&InstCreateInfo, nullptr, &vkInstance);
        // getVersion();
    }

    static void createSurface()
    {
        VkWin32SurfaceCreateInfoKHR createSurfaceInfo = {};
        createSurfaceInfo.sType=VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        createSurfaceInfo.hwnd=
        
    }