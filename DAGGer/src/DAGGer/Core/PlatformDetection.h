#ifdef _WIN32
	//  Windows x64/x86 //
	#ifdef _WIN64
		// Windows x64  //
		#define Dr_PLATFORM_WINDOWS
	#else
		#define Dr_PLATFORM_WINDOWS
		//#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)   //  Apple Platforms
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "iOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define Dr_PLATFORM_IOS	 //  iOS
		#error "iOS is not supported!"
	#elif TARGET_OS_MAC == 1		MacOS
		#define Dr_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
	//  Android is based off the linux kernel, so __ANDROID__ must be checked first
#elif defined(__ANDROID__)		  //  Android
	#define Dr_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)			//  Linux
	#define Dr_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	//  Unknown compiler/platform   //
	#error "Unknown platform!"
#endif  //	END platform detection
