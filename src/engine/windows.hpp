#pragma once

#include <Windows.h>

#include "log.hpp"
#include "platform.hpp"
#include "FoxLib\FoxLib.hpp"

namespace rb {
  struct Window {
    HWND windowHandle;
    WNDCLASSEX windowClass;
    HDC deviceContext;

    /*Tom, this is probably where you will have to handle inputs for touch */
    static LRESULT __stdcall WindowHandleInput(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
      switch(msg) {
        case WM_KEYDOWN: {
          switch(wParam) {
            case 'W':
              // Do thing as in handle input in controls class
              break;
            case 'S':
              // Do thing
              break;
            case 'A':
              // Do thing
              break;
            case 'D':
              // Do thing
              break;
          }
        }

        case WM_KEYUP:{
          switch(wParam) {
            case 'W':
              // Do thing
              break;
            case 'S':
              // Do thing
              break;
            case 'A':
              // Do thing
              break;
            case 'D':
              // Do thing
              break;
          }
        }

        case WM_CLOSE:{
          ExitProgram();
        }

        case WM_QUIT:{
          ExitProgram();
        }

        default:{
          return DefWindowProc(hWnd, msg, wParam, lParam);
        }

      }
      return 0;
    }

    void registerWindowClass() {
      windowClass.cbSize = sizeof(WNDCLASSEX);
      windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
      windowClass.lpfnWndProc = &WindowHandleInput;
      windowClass.cbClsExtra = 0;
      windowClass.cbWndExtra = 0;
      windowClass.hInstance = hInstance;
      windowClass.hIcon = nullptr; // eventually change
      windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
      windowClass.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
      windowClass.lpszMenuName = nullptr;
      windowClass.lpszClassName = "RoonyBin";
      windowClass.hIconSm = nullptr;
      ATOM succeeded0 = RegisterClassEx(&windowClass);
      if(!succeeded0) {
        log.write("[Windows.hpp] Cannot register window class.\n");
      }
    }

    /*Eventually have fullscreen capability */
    bool init() {
      windowHandle = CreateWindowEx(0,
        windowClass.lpszClassName,
        "RoonyBin",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        720,	//Width
        480,	//Height
        nullptr,
        nullptr,
        windowClass.hInstance,
        nullptr);
        if(windowHandle != nullptr) {
          deviceContext = GetDC(windowHandle);
          if(deviceContext == nullptr) {
            log.write("[Windows.hpp] Could not get device context.\n");
          }
          ShowWindow(windowHandle, SW_SHOWDEFAULT);
          UpdateWindow(windowHandle);
          return true;
        } else {
          log.write("[Windows.hpp] Could not create window.\n");
          return false;
        }
      }

      void cleanup() {
        bool destroyed = DestroyWindow(windowHandle);
        if(!destroyed) {
			log.write("[Windows.hpp] Could not destroy window.\n");
        }
      }

      void handleInput() {
        static MSG wndMsg;
        if(PeekMessage(&wndMsg, windowHandle, 0, 0, true)) {
          TranslateMessage(&wndMsg);
          DispatchMessage(&wndMsg);
        }
        /*Handle button messages*/
        SwapBuffers(deviceContext);
      }


    } win;

    HWND GetSharedWndHandle() {
      return win.windowHandle;
    }
  }
