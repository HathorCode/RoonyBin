#pragma once

#include <Windows.h>
#include <windowsx.h>
#include "touchme.hpp"
#include "log.hpp"
#include "platform.hpp"
#include "FoxLib\FoxLib.hpp"
#include <tchar.h>
#include <stdio.h>

#include "game\controls.hpp"


namespace rb {

  struct Window {
    HWND windowHandle;
    WNDCLASSEX windowClass;
    HDC deviceContext;



    /*Tom, this is probably where you will have to handle inputs for touch */
	/*>>Tom successfully handled inputs for touch here probably*/
    static LRESULT __stdcall WindowHandleInput(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		
		// For double buffering
		static HDC memDC = 0;
		static HBITMAP hMemBmp = 0;
		HBITMAP hOldBmp = 0;

		// For tracking dwId to points
		int index;

		// For dealing with WM_TOUCH
		UINT cInputs;
		PTOUCHINPUT pInputs;
		POINT ptInput;


		switch(msg) {
		case WM_TOUCH: {
			cInputs = LOWORD(wParam);
			pInputs = new TOUCHINPUT[cInputs];

			cycleCount++;
			if (pInputs) {
				if (GetTouchInputInfo((HTOUCHINPUT)lParam, cInputs, pInputs, sizeof(TOUCHINPUT))) {
					for (int xi = 0; xi < static_cast<int>(cInputs); xi++) {

						TOUCHINPUT ti = pInputs[xi];

						if (ti.dwID != 0) {
							// Do something with your touch input handle
							ptInput.x = TOUCH_COORD_TO_PIXEL(ti.x);
							ptInput.y = TOUCH_COORD_TO_PIXEL(ti.y);
							ScreenToClient(hWnd, &ptInput);

							//passes coordinates to the handler
							touch.handleJoystick(ptInput.x, ptInput.y);

							if (ti.dwFlags & TOUCHEVENTF_UP) {

								//ReleaseContactIndex(ti.dwID);
								touch.releaseTouch(ti.dwID);

								touchCount++;
							} else {
								//If the touch point already exists - ie. someone has held their finger on the screen or dragged it without lifting it off then GetCircleIndex
								//will return a value by which we can retrieve information pertaining to that touch point from circlesArray. If the touch point doesn't exist then an
								//array location will be allocated to it, a color created and stored along with its position on the screen and that array location is returned.
								index = touch.GetCircleIndex(ti.dwID);

								circlesArray[index].pointX = ptInput.x;
								circlesArray[index].pointY = ptInput.y;
							}
						}

						if (!CloseTouchInputHandle((HTOUCHINPUT)lParam)) {
							/*
							// error handling
							MessageBox(
							NULL,
							(LPCWSTR)L"!CloseTouchInputHandle",
							(LPCWSTR)L"Error",
							MB_ICONWARNING | MB_DEFBUTTON2
							);
							*/
						}
					}
				}
				// If you handled the message and don't want anything else done with it, you can close it
				CloseTouchInputHandle((HTOUCHINPUT)lParam);

				delete[] pInputs;
			} else {
				// Handle the error here
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}

        case WM_KEYDOWN: {
          switch(wParam) {
            case 'W':
              gameControls.up = true;
              break;
            case 'S':
              gameControls.down = true;
              break;
            case 'A':
              gameControls.left = true;
              break;
            case 'D':
              gameControls.right = true;
              break;
            case'~':
              gameControls.tilde = true;
              break;
          }
        }

        case WM_KEYUP:{
          switch(wParam) {
            case 'W':
              gameControls.up = false;
              break;
            case 'S':
              gameControls.down = false;
              break;
            case 'A':
              gameControls.left = false;
              break;
            case 'D':
              gameControls.right = false;
              break;
            case'~':
              gameControls.tilde = false;
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
		  RegisterTouchWindow(windowHandle, 0);
		  
		  for (int i = 0; i < MAXPOINTS; i++) {
			  circlesArray[i].sysID = -1;
			  circlesArray[i].pointX = -1;
			  circlesArray[i].pointY = -1;
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
