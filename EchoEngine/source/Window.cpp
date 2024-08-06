/*
 * MIT License
 *
 * Copyright (c) 2024 Roberto Charreton
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * In addition, any project or software that uses this library or class must include
 * the following acknowledgment in the credits:
 *
 * "This project uses software developed by Roberto Charreton and Attribute Overload."
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/
#include "Window.h"

HRESULT
Window::init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc) {
	m_hInst = hInstance;
	// Register class
	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = wndproc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, (LPCTSTR)IDI_TUTORIAL1);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "TutorialWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_TUTORIAL1));
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(nullptr, "RegisterClassEx failed!", "Error", MB_OK);
		return E_FAIL;
	}

	// Create window
	RECT rc = { 0, 0, 1200 , 1010 };
	m_rect = rc;
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	m_hWnd = CreateWindow("TutorialWindowClass",
												m_windowName.c_str(),
												WS_OVERLAPPEDWINDOW,
												CW_USEDEFAULT,
												CW_USEDEFAULT,
												m_rect.right - m_rect.left,
												m_rect.bottom - m_rect.top,
												nullptr,
												nullptr,
												m_hInst,
												nullptr);
	if (!m_hWnd) {
		MessageBox(nullptr, "CreateWindow failed!", "Error", MB_OK);
		return E_FAIL;
	}

	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	GetClientRect(m_hWnd, &m_rect);
	m_width = m_rect.right - m_rect.left;
	m_height = m_rect.bottom - m_rect.top;
	return S_OK;
}

void
Window::update() {
}

void
Window::render() {
}

void
Window::destroy() {
}
