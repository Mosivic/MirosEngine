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