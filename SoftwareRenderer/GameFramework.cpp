#include "pch.h"
#include "GameFramework.h"

void GameFramework::OnCreate(HINSTANCE hInst, HWND hWnd) {
	m_hInstance = hInst;
	m_hWnd = hWnd;

	CreateFrameBuffers();
}

void GameFramework::OnDesroy() {
	// Release Objects
}

void GameFramework::ProcessInput() {

}

void GameFramework::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {
	switch (nMessageID) {
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		break;

	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		break;

	case WM_MOUSEMOVE:
		break;

	default:
		break;
	}
}

void GameFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {
	switch (nMessageID) {
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			::PostQuitMessage(0);
			break;

		case VK_RETURN:
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
}

LRESULT CALLBACK GameFramework::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {
	switch (nMessageID) {
	case WM_SIZE:
		break;

	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
		break;

	case WM_KEYDOWN:
	case WM_KEYUP:
		OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
		break;
	}

	return(0);
}

void GameFramework::CreateFrameBuffers() {
	::GetClientRect(m_hWnd, &m_rcClient);

	HDC hDC{ ::GetDC(m_hWnd) };

	m_hDCFrameBuffer = ::CreateCompatibleDC(hDC);
	m_hBmpFrameBuffer = ::CreateCompatibleBitmap(hDC, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top);
	::SelectObject(m_hDCFrameBuffer, m_hBmpFrameBuffer);

	::ReleaseDC(m_hWnd, hDC);
	::SetBkMode(m_hDCFrameBuffer, TRANSPARENT);
}

void GameFramework::ClearFrameBuffer(DWORD dwColor) {
	HPEN hPen = ::CreatePen(PS_SOLID, 0, dwColor);
	HPEN hOldPen = (HPEN)::SelectObject(m_hDCFrameBuffer, hPen);

	HBRUSH hBrush = ::CreateSolidBrush(dwColor);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_hDCFrameBuffer, hBrush);

	::Rectangle(m_hDCFrameBuffer, m_rcClient.left, m_rcClient.top, m_rcClient.right, m_rcClient.bottom);

	::SelectObject(m_hDCFrameBuffer, hOldBrush);
	::SelectObject(m_hDCFrameBuffer, hOldPen);

	::DeleteObject(hPen);
	::DeleteObject(hBrush);
}

void GameFramework::PresentFrameBuffer() {
	HDC hDC = ::GetDC(m_hWnd);
	::BitBlt(hDC, m_rcClient.left, m_rcClient.top, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top, m_hDCFrameBuffer, m_rcClient.left, m_rcClient.top, SRCCOPY);
	::ReleaseDC(m_hWnd, hDC);
}

void GameFramework::FrameAdvance() {
	ProcessInput();

	ClearFrameBuffer(RGB(90, 103, 224));

	HPEN hPen = ::CreatePen(PS_SOLID, 0, RGB(0x00, 0xff, 0x00));
	HPEN hOldPen = (HPEN)::SelectObject(m_hDCFrameBuffer, hPen);

	::MoveToEx(m_hDCFrameBuffer, 100, 100, NULL);
	::LineTo(m_hDCFrameBuffer, 400, 400);

	::SelectObject(m_hDCFrameBuffer, hOldPen);
	::DeleteObject(hPen);

	PresentFrameBuffer();
}
