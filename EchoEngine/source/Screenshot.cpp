#include "Screenshot.h"
#include "Window.h"
#include "SwapChain.h"
#include "Texture.h"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"

void 
Screenshot::captureScreenshot(Window window, SwapChain swapChain, Texture & backBuffer) {
  // Obtener el back buffer
  swapChain.m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&backBuffer.m_texture));

  // Obtener el HWND de la ventana de la aplicación
  HWND hWnd = GetForegroundWindow();

  // Obtener el DC de la ventana de la aplicación
  HDC hDC = GetDC(hWnd);

  // Obtener el tamaño de la ventana de la aplicación
  RECT rect;
  GetClientRect(hWnd, &rect);
  int width = rect.right - rect.left;
  int height = rect.bottom - rect.top;

  // Crear la textura en memoria
  HBITMAP hBitmap = CreateCompatibleBitmap(hDC, width, height);
  HDC hMemoryDC = CreateCompatibleDC(hDC);
  SelectObject(hMemoryDC, hBitmap);

  // Copiar el back buffer al contexto de dispositivo de la textura en memoria
  BitBlt(hMemoryDC, 0, 0, width, height, hDC, 0, 0, SRCCOPY);

  /// Obtener los datos de píxeles del HBITMAP
  BITMAPINFO bmi = { 0 };
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = window.m_width;
  bmi.bmiHeader.biHeight = -window.m_height;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 32;
  bmi.bmiHeader.biCompression = BI_RGB;
  std::vector<uint8_t> pixels(window.m_width * window.m_height * 4);
  GetDIBits(hMemoryDC, hBitmap, 0, window.m_height, pixels.data(), &bmi, DIB_RGB_COLORS);

  // Reordenar los datos de los píxeles de BGR a RGB
  for (size_t i = 0; i < pixels.size(); i += 4) {
    std::swap(pixels[i], pixels[i + 2]);
  }

  // Guardar los datos de píxeles en un archivo de imagen
  //stbi_write_png("screenshot.png", window.m_width, window.m_height, 4, pixels.data(), window.m_width * 4);


  // Liberar los recursos
  DeleteDC(hMemoryDC);
  DeleteObject(hBitmap);
  ReleaseDC(hWnd, hDC);
  backBuffer.m_texture->Release();
}

void 
Screenshot::ui(Window window, SwapChain swapChain, Texture& backBuffer) {
  if (ImGui::Button("Capture Screenshot"))
  {
    ImGui::OpenPopup("popup_mensaje");
  }
  if (ImGui::BeginPopup("popup_mensaje")) {

    if (ImGui::Button("Close")) {
      ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button("Capture Screenshot")) {
      captureScreenshot(window, swapChain, backBuffer);
    }
    ImGui::EndPopup();
  }

}
