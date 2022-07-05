#include "Win.hpp"
#include "Vks.tpp"
#include <windef.h>
#include <winuser.h>
#include <WindowsX.h>
#include <iostream>

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
      std::cout <<std::hex <<"0x"<< uMsg << "OK!" << "\n";
      std::cout <<std::dec <<"wParam"<<"0x"<< wParam << "OK!" << "\n";
      std::cout <<std::left <<"lParam"<<"0x"<< lParam << "OK!" << "\n";
      std::cout <<std::dec <<"W"<< (GET_X_LPARAM(lParam)) << "OK!" << "\n";
      std::cout <<std::dec <<"H"<< (GET_Y_LPARAM(lParam)) << "OK!" << "\n";
    //   VkInit::X=(GET_X_LPARAM(lParam));
    //   VkInit::Y=(GET_Y_LPARAM(lParam));

  switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        return 0;
    case WM_NCCREATE:
    
          std::cout << "NCCreate Window!" << "\n";
          return true;
    
    case WM_NCDESTROY:
    
      std::cout << "NCDestroy Window!" << "\n";
      return 0;
    case WM_INPUT:
    {
      std::cout << "INPUT!" << "\n";
      auto a =GET_RAWINPUT_CODE_WPARAM(wParam);
      std::cout << a << "\n";
      return 0;
    }
    case WM_CREATE:
       std::cout << "Create Window" << "\n";
       return true;
    case WM_NCACTIVATE:
       std::cout << "CreateActivat Window" << "\n";
      return(!wParam)?false: -1;
      return 1;
    case WM_SETCURSOR:
      return false;
    case WM_GETMINMAXINFO:
      return 0;
    case WM_NCCALCSIZE:
      if(wParam)
      {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
      }
      else return true;
    
    case WM_MOVE:
      std::cout << "MOVE!" << "\n";
      return true;
    
   

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
};

auto Win::init(HINSTANCE instance) const -> HWND
{

 

  
 WNDCLASS wc = { };
    wc.style=CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = instance;
    // wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    // wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    // wc.hbrBackground = nullptr;//(HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "main";
    RegisterClass(&wc);
    auto w =CreateWindowEx(wc.style,
                                           "main",
                                           nullptr,
                                           NULL,
                                           0, 0,
                                           width, height,
                                           nullptr, // No parent window
                                           NULL, // No window menu
                                           instance,
                                           (LPVOID) nullptr);

    if (w == nullptr)
    {
        return nullptr;
    }

    ShowWindow(w, 10);

 
  std::cout << "OK!" << "\n";
  return  w;
};