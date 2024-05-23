#include "BaseApp.h"

HRESULT
BaseApp::init() {
  return E_NOTIMPL;
}

void 
BaseApp::update() {
}

void 
BaseApp::render() {
}

void 
BaseApp::destroy() {
}

int
BaseApp::run(HINSTANCE hInstance, 
						 HINSTANCE hPrevInstance, 
						 LPWSTR lpCmdLine, 
						 int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // Inicializa la ventana
  if (FAILED(m_window.init(hInstance, nCmdShow, nullptr)))
    return 0;

  // Inicializa los recursos de la aplicacion
  if (FAILED(init()))
  {
    destroy();
    return 0;
  }

  // Main message loop
  MSG msg = { 0 };
  while (WM_QUIT != msg.message)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
      update();
      render();
    }
  }

  destroy();

  return (int)msg.wParam;
}

LRESULT CALLBACK
BaseApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PAINTSTRUCT ps;
  HDC hdc;

  switch (message)
  {
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
}