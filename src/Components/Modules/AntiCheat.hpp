#pragma once

#ifndef DEBUG
// Hide AntiCheat in embeded symbol names
#define AntiCheat SubComponent
#endif

// Uncomment to enable process protection (conflicts with steam!)
#define PROCTECT_PROCESS

namespace Components
{
	class AntiCheat : public Component
	{
	public:
		AntiCheat();
		~AntiCheat();

		static void CrashClient();

		static void InitLoadLibHook();

		static void ReadIntegrityCheck();
		static void ScanIntegrityCheck();
		static void FlagIntegrityCheck();

		static unsigned long ProtectProcess();

		static void PatchVirtualProtect(void* vp, void* vpex);

	private:
		enum IntergrityFlag
		{
			NO_FLAG = (0),
			INITIALIZATION = (1 << 0),
			MEMORY_SCAN = (1 << 1),
			SCAN_INTEGRITY_CHECK = (1 << 2),

#ifdef PROCTECT_PROCESS
			READ_INTEGRITY_CHECK = (1 << 3),
#endif

			MAX_FLAG,
		};

		static Utils::Time::Interval LastCheck;
		static std::string Hash;
		static unsigned long Flags;

		static void PerformScan();
		static void PatchWinAPI();

		static void NullSub();

		static bool IsPageChangeAllowed(void* callee, void* addr, size_t len);
		static void AssertCalleeModule(void* callee);

		static void UninstallLibHook();
		static void InstallLibHook();

#ifdef DEBUG_LOAD_LIBRARY
		static HANDLE LoadLibary(std::wstring library, HANDLE file, DWORD flags, void* callee);
		static HANDLE WINAPI LoadLibaryAStub(const char* library);
		static HANDLE WINAPI LoadLibaryWStub(const wchar_t* library);
		static HANDLE WINAPI LoadLibaryExAStub(const char* library, HANDLE file, DWORD flags);
		static HANDLE WINAPI LoadLibaryExWStub(const wchar_t* library, HANDLE file, DWORD flags);
#endif

		static BOOL WINAPI VirtualProtectStub(LPVOID lpAddress, SIZE_T dwSize, DWORD  flNewProtect, PDWORD lpflOldProtect);
		static BOOL WINAPI VirtualProtectExStub(HANDLE hProcess,LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect,PDWORD lpflOldProtect);

		static void LostD3DStub();
		static void CinematicStub();
		static void SoundInitStub(int a1, int a2, int a3);
		static void SoundInitDriverStub();

		static void DObjGetWorldTagPosStub();
		static void AimTargetGetTagPosStub();

		static void AcquireDebugPriviledge(HANDLE hToken);

		static Utils::Hook LoadLibHook[4];
		static Utils::Hook VirtualProtectHook[2];
	};
}
