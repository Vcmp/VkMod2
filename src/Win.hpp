#pragma once
#include <cstdint>

using DWORD = unsigned long;
		using  LPCWSTR = const wchar_t*;
		using  HANDLE = void* ;
		using  HINSTANCE = struct HINSTANCE__*;
		using  HWND = struct HWND__*;
		using  HMONITOR = struct HMONITOR__*;
		using SECURITY_ATTRIBUTES = struct _SECURITY_ATTRIBUTES ;
          using WPARAM = unsigned long long;
  using LPARAM = long long;
  using LRESULT = long long;
  using UINT = unsigned int;
struct [[clang::trivial_abi]] Win
{
  HWND window;
  
  uint16_t X;
  uint16_t Y;
  explicit constexpr Win(HINSTANCE instance): window(init(instance)) {};
  [[nodiscard]] auto init(HINSTANCE) const -> HWND;
  static __int64 __stdcall WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
  
};