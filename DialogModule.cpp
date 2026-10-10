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
#include <libdlgmod/general/lodepng.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xrandr.h>
#include <X11/extensions/Xinerama.h>
#include "IDI_APPICON.h"
static int displayX            = -1;
static int displayY            = -1;
static int displayWidth        = -1;
static int displayHeight       = -1;
static int displayXGetter      = -1;
static int displayYGetter      = -1;
static int displayWidthGetter  = -1;
static int displayHeightGetter = -1;
static void display_get_position(bool i, int *result) {
  Display *display = XOpenDisplay(NULL);
  *result = 0; Rotation original_rotation; 
  Window root = XDefaultRootWindow(display);
  XRRScreenConfiguration *conf = XRRGetScreenInfo(display, root);
  SizeID original_size_id = XRRConfigCurrentConfiguration(conf, &original_rotation);
  if (XineramaIsActive(display)) {
    int m = 0; XineramaScreenInfo *xrrp = XineramaQueryScreens(display, &m);
    if (!i) *result = xrrp[original_size_id].x_org;
    else if (i) *result = xrrp[original_size_id].y_org;
    XFree(xrrp);
  }
  XCloseDisplay(display);
}
static void display_get_size(bool i, int *result) {
  Display *display = XOpenDisplay(NULL);
  *result = 0; int num_sizes; Rotation original_rotation; 
  Window root = XDefaultRootWindow(display);
  int screen = XDefaultScreen(display);
  XRRScreenConfiguration *conf = XRRGetScreenInfo(display, root);
  SizeID original_size_id = XRRConfigCurrentConfiguration(conf, &original_rotation);
  if (XineramaIsActive(display)) {
    XRRScreenSize *xrrs = XRRSizes(display, screen, &num_sizes);
    if (!i) *result = xrrs[original_size_id].width;
    else if (i) *result = xrrs[original_size_id].height;
  } else if (!i) *result = XDisplayWidth(display, screen);
  else if (i) *result = XDisplayHeight(display, screen);
  XCloseDisplay(display);
}
static int display_get_x() {
  if (displayXGetter == displayX && displayX != -1)
    return displayXGetter;
  display_get_position(false, &displayXGetter);
  int result = displayXGetter;
  displayX = result;
  return result;
}
static int display_get_y() { 
  if (displayYGetter == displayY && displayY != -1)
    return displayYGetter;
  display_get_position(true, &displayYGetter);
  int result = displayYGetter;
  displayY = result;
  return result;
}
static int display_get_width() {
  if (displayWidthGetter == displayWidth && displayWidth != -1) 
    return displayWidthGetter;
  display_get_size(false, &displayWidthGetter);
  int result = displayWidthGetter;
  displayWidth = result;
  return result;
}
static int display_get_height() {
  if (displayHeightGetter == displayHeight && displayHeight != -1)
    return displayHeightGetter;
  display_get_size(true, &displayHeightGetter);
  int result = displayHeightGetter;
  displayHeight = result;
  return result;
}
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
  std::ofstream out(icon, std::ios::binary);
  out.write((const char *)IDI_APPICON_png, IDI_APPICON_png_len);
  out.close();
  WNDCLASSEXA wc = { sizeof(WNDCLASSEXA) };
  wc.lpfnWndProc = DefWindowProc;
  wc.lpszClassName = "DialogModule";
  wc.hInstance = GetModuleHandleA(nullptr);
  wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  RegisterClassExA(&wc);
  HWND window = CreateWindowExA(0, wc.lpszClassName, wc.lpszClassName, WS_OVERLAPPEDWINDOW,
  0, 0, 640, 480, nullptr, nullptr, nullptr, nullptr);
  HICON hIcon = nullptr;
  ULONG_PTR gdiplusToken;
  Gdiplus::GdiplusStartupInput gdiplusStartupInput;
  Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
  Gdiplus::Bitmap *png = Gdiplus::Bitmap::FromFile(icon.wstring().c_str());
  png->GetHICON(&hIcon);
  PostMessageW(window, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
  delete png;
  EnableMenuItem(GetSystemMenu(window, false), SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
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
  std::ofstream out(icon, std::ios::binary);
  out.write((const char *)IDI_APPICON_MAC_png, IDI_APPICON_MAC_png_len);
  out.close();
  NSRect frame = NSMakeRect(0, 0, 640, 480);
  NSWindowStyleMask styles = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable;
  NSWindow *window = [[NSWindow alloc] initWithContentRect:frame styleMask:styles backing:NSBackingStoreBuffered defer:false];
  [window setTitle:@"DialogModule"];
  [window setBackgroundColor:[NSColor whiteColor]];
  NSImage *image = [[NSImage alloc] initWithContentsOfFile:[NSString stringWithUTF8String:icon.u8string().c_str()]];
  [NSApp setApplicationIconImage:image];
  [[window standardWindowButton:NSWindowCloseButton] setEnabled:NO];
  NSRect screen = [[NSScreen mainScreen] frame];
  CGFloat xpos = NSMidX(screen) - (frame.size.width / 2);
  CGFloat ypos = NSMidY(screen) - (frame.size.height / 2);
  [window setFrameOrigin:NSMakePoint(xpos, ypos)];
  [window makeKeyAndOrderFront:nullptr];
  #elif ((defined(__linux__) && !defined(__ANDROID__)) || (defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__OpenBSD__)) || defined(__sun) || defined(PROCESS_XQUARTZ_IMPL))
  std::error_code ec;
  std::filesystem::path icon = std::filesystem::temp_directory_path(ec) / "IDI_APPICON.png";
  std::ofstream out(icon, std::ios::binary);
  out.write((const char *)IDI_APPICON_png, IDI_APPICON_png_len);
  out.close();
  auto XSetIcon = [](Display *display, Window window, const char *icon) {
    auto nlpo2dc = [](unsigned x) {
      x--;
      x |= x >> 1;
      x |= x >> 2;
      x |= x >> 4;
      x |= x >> 8;
      return (unsigned)(x | (x >> 16));
    };
    XSynchronize(display, true);
    Atom property = XInternAtom(display, "_NET_WM_ICON", true);
    unsigned char *data = nullptr;
    unsigned pngwidth, pngheight;
    unsigned error = lodepng_decode32_file(&data, &pngwidth, &pngheight, icon);
    unsigned widfull = nlpo2dc(pngwidth) + 1,
    hgtfull = nlpo2dc(pngheight) + 1, ih, iw;
    const int bitmap_size = widfull * hgtfull * 4;
    unsigned char *bitmap = new unsigned char[bitmap_size]();
    unsigned i = 0;
    unsigned elem_numb = 2 + pngwidth * pngheight;
    unsigned long *result = new unsigned long[elem_numb]();
    result[i++] = pngwidth;
    result[i++] = pngheight;
    for (ih = 0; ih < pngheight; ih++) {
      unsigned tmp = ih * widfull * 4;
      for (iw = 0; iw < pngwidth; iw++) {
        bitmap[tmp + 0] = data[4 * pngwidth * ih + iw * 4 + 2];
        bitmap[tmp + 1] = data[4 * pngwidth * ih + iw * 4 + 1];
        bitmap[tmp + 2] = data[4 * pngwidth * ih + iw * 4 + 0];
        bitmap[tmp + 3] = data[4 * pngwidth * ih + iw * 4 + 3];
        result[i++] = bitmap[tmp + 0] | (bitmap[tmp + 1] << 8) | (bitmap[tmp + 2] << 16) | (bitmap[tmp + 3] << 24);
        tmp += 4;
      }
    }
    XChangeProperty(display, window, property, XA_CARDINAL, 32, PropModeReplace, (unsigned char *)result, elem_numb);
    XFlush(display);
    delete[] result;
    delete[] bitmap;
    delete[] data;
  };
  Display *display = XOpenDisplay(nullptr);
  int screen = DefaultScreen(display);
  int xpos = display_get_x() + ((display_get_width() - 640) / 2);
  int ypos = display_get_y() + ((display_get_height() - 480) / 2);
  Window window = XCreateSimpleWindow(display, RootWindow(display, screen), 
  xpos, ypos, 640, 480, 1, BlackPixel(display, screen), WhitePixel(display, screen));
  XSizeHints *size_hints = XAllocSizeHints();
  size_hints->flags &= ~PPosition;
  size_hints->flags |= USPosition;
  size_hints->x = xpos;
  size_hints->y = ypos;
  XSetWMNormalHints(display, window, size_hints);
  XFree(size_hints);
  XStoreName(display, window, "DialogModule");
  XSetIcon(display, window, icon.u8string().c_str());
  XSelectInput(display, window, ExposureMask | KeyPressMask);
  XMapWindow(display, window);
  XEvent event;
  while (true) {
  XNextEvent(display, &event);
  #endif
  widget_set_owner(std::to_string((unsigned long long)window).c_str());
  widget_set_icon(icon.u8string().c_str());
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
  show_message(std::to_string(btn).c_str());
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
  [image release];
  [window release];
  #elif ((defined(__linux__) && !defined(__ANDROID__)) || (defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__OpenBSD__)) || defined(__sun) || defined(PROCESS_XQUARTZ_IMPL))
  break;
  }
  XDestroyWindow(display, window);
  XCloseDisplay(display);
  #endif
  return 0;
}
