#pragma once
#ifdef MRS_PLATFORM_WINDOWS
	#ifdef MRS_BUILD_DLL
		#define MIROS_API _declspec(dllexport)
	#else 
		#define MIROS_API _declspec(dllimport)
	#endif
#else
	#error Miros only supports Windows!
#endif

#ifdef MRS_ENABLE_ASSERTS
	#define  MRS_ASSERT(x,...) {if(!(x)){MRS_ERROR("Assertion Failed: {0}",__VA_ARGS__);__debugbreak();}}
	#define  MRS_CORE_ASSERT(x,...) {if(!(x)){MRS_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__);__debugbreak();}}
#else
	#define MRS_ASSET(x,...)
	#define MRS_CORE_ASSERT(x,...)
#endif 


#define BIT(x) (1<<x)


