#pragma once
typedef unsigned long DWORD;
		typedef const wchar_t* LPCWSTR;
		typedef void* HANDLE;
		typedef struct HINSTANCE__* HINSTANCE;
		typedef struct HWND__* HWND;
		typedef struct HMONITOR__* HMONITOR;
		typedef struct _SECURITY_ATTRIBUTES SECURITY_ATTRIBUTES;
struct Win
{
  HWND window;
  
  
  explicit constexpr Win(HINSTANCE instance): window(init(instance)) {};
  [[nodiscard]] auto init(HINSTANCE) const -> HWND;
  
};