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