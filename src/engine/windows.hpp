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
    static LRESULT __stdcall WindowHandleInput(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		
		// For double buffering
		static HDC memDC = 0;
		static HBITMAP hMemBmp = 0;
		HBITMAP hOldBmp = 0;

		// For tracking dwId to points
		int index;

		// For dealing with WM_TOUCH
		int i, x, y;
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
					for (int i = 0; i < static_cast<int>(cInputs); i++) {

						TOUCHINPUT ti = pInputs[i];

						if (ti.dwID != 0) {
							// Do something with your touch input handle
							ptInput.x = TOUCH_COORD_TO_PIXEL(ti.x);
							ptInput.y = TOUCH_COORD_TO_PIXEL(ti.y);
							ScreenToClient(hWnd, &ptInput);

							if (ti.dwFlags & TOUCHEVENTF_UP) {

								//ReleaseContactIndex(ti.dwID);
								touch.ReleaseCircleIndex(ti.dwID);

								touchCount++;
							}
							else {
								//If the touch point already exists - ie. someone has held their finger
								//on the screen or dragged it without lifting it off then GetCircleIndex
								//will return a value by which we can retrieve information pertaining to
								//that touch point from circlesArray. If the touch point doesn't exist then an
								//array location will be allocated to it, a color created and stored along
								//with its position on the screen and that array location is returned.
								index = touch.GetCircleIndex(ti.dwID);

								circlesArray[index].pointX = ptInput.x;
								circlesArray[index].pointY = ptInput.y;
							}
						}

						if (!CloseTouchInputHandle((HTOUCHINPUT)lParam))
						{
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
			}
			else {
				// Handle the error here
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}

		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...

			RECT client;
			GetClientRect(hWnd, &client);

			// start double buffering
			if (!memDC) {
				memDC = CreateCompatibleDC(hdc);
			}
			hMemBmp = CreateCompatibleBitmap(hdc, client.right, client.bottom);
			hOldBmp = (HBITMAP)SelectObject(memDC, hMemBmp);

			//This conditional provides a convenient block
			//within which backgroundBrush can be created and destroyed
			if (memDC) {

				//A brush to create background is generated once
				//and destroyed once every time this function is called
				HBRUSH backgroundBrush = CreateSolidBrush(RGB(0, 0, 0));

				FillRect(memDC, &client, backgroundBrush);

				//Draw Touched Points
				for (i = 0; i < MAXPOINTS; i++) {


					//I added this block to monitor the touch point IDs on screen
					TCHAR buffer[180];
					_stprintf_s(buffer, 180, _T(
						"cc %d tc %d idl: %d %d %d %d %d %d %d %d %d %d                                                                       "),
						cycleCount, touchCount,
						circlesArray[0].sysID,
						circlesArray[1].sysID,
						circlesArray[2].sysID,
						circlesArray[3].sysID,
						circlesArray[4].sysID,
						circlesArray[5].sysID,
						circlesArray[6].sysID,
						circlesArray[7].sysID,
						circlesArray[8].sysID,
						circlesArray[9].sysID
					);
					RECT rect = { 0,0,800,20 };
					DrawText(memDC, buffer, 100, (LPRECT)&rect, DT_TOP);

					HBRUSH circleBrush = CreateSolidBrush(circlesArray[i].color);
					SelectObject(memDC, circleBrush);

					x = circlesArray[i].pointX;
					y = circlesArray[i].pointY;

					if (x >0 && y>0) {
						Ellipse(memDC, x - radius, y - radius, x + radius, y + radius);
					}
					ReleaseDC(hWnd, memDC);
					DeleteObject(circleBrush);
				}

				BitBlt(hdc, 0, 0, client.right, client.bottom, memDC, 0, 0, SRCCOPY);
				DeleteObject(backgroundBrush);
			}

			EndPaint(hWnd, &ps);

			ReleaseDC(hWnd, hdc);
			DeleteObject(hMemBmp);
			DeleteObject(hOldBmp);
			break;
		}

		case WM_DESTROY: {
			DeleteDC(memDC);
			PostQuitMessage(0);
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
			  circlesArray[i].color = RGB(0, 0, 0);
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
