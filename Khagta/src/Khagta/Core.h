#pragma once

#ifdef KG_PLATFORM_WINDOWS
   #ifdef KG_BUILD_DLL
        #define KHAGTA_API _declspec(dllexport)
   #else
        #define KHAGTA_API _declspec(dllimport)
   #endif // KG_BUILD_DLL
#else
   #error Khagta only supports windows
#endif

#ifdef KG_ENABLE_ASSERTS
#define KG_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define KG_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define KG_ASSERT(x, ...)
#define KG_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)