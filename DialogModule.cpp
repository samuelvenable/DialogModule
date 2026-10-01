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

#include "IDI_APPICON.h"

int main() {
  std::error_code ec;
  const int c_red = 255;
  const char *filter = "Sprite Images (*.png *.gif *.jpg *.jpeg)|*.png;*.gif;*.jpg;*.jpeg|Background Images (*.png)|*.png|All Files (*.*)|*.*";
  std::filesystem::path icon = std::filesystem::temp_directory_path(ec) / "IDI_APPICON.png";
  std::ofstream out(icon.string().c_str(), std::ios::binary);
  out.write((const char *)IDI_APPICON_png, IDI_APPICON_png_len);
  out.close();
  widget_set_icon(icon.string().c_str());
  widget_set_caption("DialogModule");
  std::cout << show_message("Hello World!") << std::endl;
  std::cout << show_message_cancelable("Hello World!") << std::endl;
  std::cout << show_question("Yes or no?") << std::endl;
  std::cout << show_question_cancelable("Yes, no, or cancel?") << std::endl;
  widget_set_caption("Error");
  std::cout << show_attempt("Hello World!") << std::endl;
  std::cout << show_error("Hello World!", false) << std::endl;
  widget_set_caption("DialogModule");
  std::cout << get_string("Enter a string:", "Hello World!") << std::endl;
  std::cout << get_password("Enter a string password:", "Hello World!") << std::endl;
  std::cout << get_integer("Enter an integer:", 0) << std::endl;
  std::cout << get_passcode("Enter an integer passcode:", 0) << std::endl;
  std::cout << get_open_filename(filter, "Select a File") << std::endl;
  std::cout << get_open_filename_ext(filter, "Select a File", "", "Open Ext") << std::endl;
  std::cout << get_open_filenames(filter, "Select Files") << std::endl;
  std::cout << get_open_filenames_ext(filter, "Select Files", "", "Open Ext") << std::endl;
  std::cout << get_save_filename(filter, "Untitled.png") << std::endl;
  std::cout << get_save_filename_ext(filter, "Untitled.png", "", "Save As Ext") << std::endl;
  std::cout << get_directory("") << std::endl;
  #if (defined(_WIN32) || defined(_WIN64))
  std::cout << get_directory_alt("Select Folder Alt", "") << std::endl;
  #else
  std::cout << get_directory_alt("Select Directory Alt", "") << std::endl;
  #endif
  std::cout << get_color(c_red) << std::endl;
  #if (defined(__APPLE__) && defined(__MACH__))
  std::cout << get_color_ext(c_red, "Colors Ext") << std::endl;
  #else
  std::cout << get_color_ext(c_red, "Color Ext") << std::endl;
  #endif
  return 0;
}
