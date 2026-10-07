/*

MIT License

Copyright © 2026 Samuel Venable

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <system_error>
#include <filesystem>

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

#include <libdlgmod/libdlgmod.h>

#if (defined(_WIN32) || defined(_WIN64))
#include <windows.h>
#include <gdiplus.h>
#include "IDI_APPICON.h"
#elif (defined(__APPLE__) && defined(__MACH__) && !defined(PROCESS_XQUARTZ_IMPL))
#include <AppKit/AppKit.h>
#include "IDI_APPICON_MAC.h"
#elif ((defined(__linux__) && !defined(__ANDROID__)) || (defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__OpenBSD__)) || defined(__sun) || defined(PROCESS_XQUARTZ_IMPL))
#include <X11/Xlib.h>
#include "IDI_APPICON.h"
#endif

int main() {
  int btn = 0;
  int col = -1;
  double dbl = 0;
  std::string str;
  const int c_red = 255;
  const char *filter = "Sprite Images (*.png *.gif *.jpg *.jpeg)|*.png;*.gif;*.jpg;*.jpeg|Background Images (*.png)|*.png|All Files (*.*)|*.*";
  auto remove_trailing_zeros = [](double dbl) {
    std::string strdbl = std::to_string(dbl);
    while (!strdbl.empty() && strdbl.find('.') != std::string::npos && 
      (strdbl.back() == '.' || strdbl.back() == '0')) {
      strdbl.pop_back();
    }
    return strdbl;
  };
  #if (defined(_WIN32) || defined(_WIN64))
  std::error_code ec;
  std::filesystem::path icon = std::filesystem::temp_directory_path(ec) / "IDI_APPICON.png";
  std::ofstream out(icon.string().c_str(), std::ios::binary);
  out.write((const char *)IDI_APPICON_png, IDI_APPICON_png_len);
  out.close();
  WNDCLASSEXW wc = { sizeof(WNDCLASSEXW) };
  wc.lpfnWndProc = DefWindowProc;
  wc.lpszClassName = L"DialogModule";
  wc.hInstance = GetModuleHandleW(nullptr);
  wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  RegisterClassExW(&wc);
  static const wchar_t *title = L"DialogModule;
  HWND window = CreateWindowExW(0, wc.lpszClassName, title, WS_OVERLAPPEDWINDOW,
  0, 0, 640, 480, nullptr, nullptr, nullptr, nullptr);
  HICON hIcon = nullptr;
  ULONG_PTR gdiplusToken;
  Gdiplus::GdiplusStartupInput gdiplusStartupInput;
  Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
  Gdiplus::Bitmap *png = Gdiplus::Bitmap::FromFile(icon.wstring().c_str());
  png->GetHICON(&hIcon);
  PostMessage(window, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
  delete png;
  RECT rc = { 0, 0, 640, 480 };
  DWORD dwStyle = GetWindowLongPtr(window, GWL_STYLE);
  DWORD dwExStyle = GetWindowLongPtr(window, GWL_EXSTYLE);
  bool bMenu = (GetMenu(window) != nullptr);
  AdjustWindowRectEx(&rc, dwStyle, bMenu, dwExStyle);
  int width = rc.right - rc.left, height = rc.bottom - rc.top;
  SetWindowPos(window, nullptr, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
  int cxscreen = GetSystemMetrics(SM_CXSCREEN);
  int cyscreen = GetSystemMetrics(SM_CYSCREEN);
  int xpos = (cxscreen - width) / 2;
  int ypos = (cyscreen - height) / 2;
  SetWindowPos(window, HWND_TOP, xpos, ypos, width, height, SWP_SHOWWINDOW);
  ShowWindow(window, SW_SHOW);
  UpdateWindow(window);
  #elif (defined(__APPLE__) && defined(__MACH__) && !defined(PROCESS_XQUARTZ_IMPL))
  std::error_code ec;
  std::filesystem::path icon = std::filesystem::temp_directory_path(ec) / "IDI_APPICON.png";
  std::ofstream out(icon.string().c_str(), std::ios::binary);
  out.write((const char *)IDI_APPICON_MAC_png, IDI_APPICON_MAC_png_len);
  out.close();
  NSRect frame = NSMakeRect(0, 0, 640, 480);
  NSWindowStyleMask styles = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable;
  NSWindow *window = [[NSWindow alloc] initWithContentRect:frame styleMask:styles backing:NSBackingStoreBuffered defer:false];
  [window setTitle:@"DialogModule"];
  [window setBackgroundColor:[NSColor whiteColor]];
  NSRect screen = [[NSScreen mainScreen] frame];
  CGFloat xpos = NSMidX(screen) - (frame.size.width / 2);
  CGFloat ypos = NSMidY(screen) - (frame.size.height / 2);
  [window setFrameOrigin:NSMakePoint(xpos, ypos)];
  [window makeKeyAndOrderFront:nullptr];
  #elif ((defined(__linux__) && !defined(__ANDROID__)) || (defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__OpenBSD__)) || defined(__sun) || defined(PROCESS_XQUARTZ_IMPL))
  std::error_code ec;
  std::filesystem::path icon = std::filesystem::temp_directory_path(ec) / "IDI_APPICON.png";
  std::ofstream out(icon.string().c_str(), std::ios::binary);
  out.write((const char *)IDI_APPICON_png, IDI_APPICON_png_len);
  out.close();
  Display *display = XOpenDisplay(nullptr);
  int screen = DefaultScreen(display);
  Window window = XCreateSimpleWindow(display, RootWindow(display, screen), 
  0, 0, 550, 32 * 4, 1, BlackPixel(display, screen), WhitePixel(display, screen));
  XStoreName(display, window, "DialogModule");
  XSelectInput(display, window, ExposureMask | KeyPressMask);
  XMapWindow(display, window);
  #endif
  widget_set_owner(std::to_string((unsigned long long)window).c_str());
  widget_set_icon(icon.string().c_str());
  widget_set_caption("DialogModule");
  btn = show_message("Hello World!");
  show_message(std::to_string(btn).c_str());
  btn = show_message_cancelable("Hello World!");
  show_message(std::to_string(btn).c_str());
  btn = show_question("Yes or no?");
  show_message(std::to_string(btn).c_str());
  btn = show_question_cancelable("Yes, no, or cancel?");
  show_message(std::to_string(btn).c_str());
  widget_set_caption("Error");
  btn = show_attempt("Hello World!");
  widget_set_caption("DialogModule");
  show_message(std::to_string(btn).c_str());
  widget_set_caption("Error");
  btn = show_error("Hello World!", false);
  widget_set_caption("DialogModule");
  str = get_string("Enter a string:", "Hello World!");
  if (!str.empty()) { show_message(str.c_str()); }
  str = get_password("Enter a string password:", "Hello World!");
  if (!str.empty()) { show_message(str.c_str()); }
  dbl = get_integer("Enter an integer:", 0);
  if (!widget_get_canceled()) { show_message(remove_trailing_zeros(dbl).c_str()); }
  dbl = get_passcode("Enter an integer passcode:", 0);
  if (!widget_get_canceled()) { show_message(remove_trailing_zeros(dbl).c_str()); }
  str = get_open_filename(filter, "Select a File");
  if (!str.empty()) { show_message(str.c_str()); }
  str = get_open_filename_ext(filter, "Select a File", "", "Open Ext");
  if (!str.empty()) { show_message(str.c_str()); }
  str = get_open_filenames(filter, "Select Files");
  if (!str.empty()) { show_message(str.c_str()); }
  str = get_open_filenames_ext(filter, "Select Files", "", "Open Ext");
  if (!str.empty()) { show_message(str.c_str()); }
  str = get_save_filename(filter, "Untitled.png");
  if (!str.empty()) { show_message(str.c_str()); }
  str = get_save_filename_ext(filter, "Untitled.png", "", "Save As Ext");
  if (!str.empty()) { show_message(str.c_str()); }
  str = get_directory("");
  if (!str.empty()) { show_message(str.c_str()); }
  #if (defined(_WIN32) || defined(_WIN64))
  str = get_directory_alt("Select Folder Alt", "");
  #else
  str = get_directory_alt("Select Directory Alt", "");
  #endif
  if (!str.empty()) { show_message(str.c_str()); }
  col = get_color(c_red);
  show_message(std::to_string(col).c_str());
  #if (defined(__APPLE__) && defined(__MACH__))
  col = get_color_ext(c_red, "Colors Ext");
  #else
  col = get_color_ext(c_red, "Color Ext");
  #endif
  show_message(std::to_string(col).c_str());
  #if (defined(_WIN32) || defined(_WIN64))
  DestroyWindow(window);
  #elif (defined(__APPLE__) && defined(__MACH__) && !defined(PROCESS_XQUARTZ_IMPL))
  [window release];
  #elif ((defined(__linux__) && !defined(__ANDROID__)) || (defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__OpenBSD__)) || defined(__sun) || defined(PROCESS_XQUARTZ_IMPL))
  XDestroyWindow(display, window);
  XCloseDisplay(display);
  #endif
  return 0;
}
