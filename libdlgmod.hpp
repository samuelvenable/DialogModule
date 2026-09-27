/*

 MIT License

 Copyright © 2021-2026 Samuel Venable

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

#if !defined(DIALOG_MODULE_GAME_MAKER_BUILD)
#if defined(_WIN32) /* Windows */
#define EXPORTED_FUNCTION extern "C" __declspec(dllexport)
#else /* macOS, Linux, FreeBSD, DragonFly BSD, NetBSD, OpenBSD, Solaris, illumos */
#define EXPORTED_FUNCTION extern "C" __attribute__((visibility("default")))
#endif
EXPORTED_FUNCTION int show_message(const char *str);
EXPORTED_FUNCTION int show_message_cancelable(const char *str);
EXPORTED_FUNCTION int show_question(const char *str);
EXPORTED_FUNCTION int show_question_cancelable(const char *str);
EXPORTED_FUNCTION int show_attempt(const char *str);
EXPORTED_FUNCTION int show_error(const char *str, bool abort);
EXPORTED_FUNCTION const char *get_string(const char *str, const char *def);
EXPORTED_FUNCTION const char *get_password(const char *str, const char *def);
EXPORTED_FUNCTION double get_integer(const char *str, double def);
EXPORTED_FUNCTION double get_passcode(const char *str, double def);
EXPORTED_FUNCTION const char *get_open_filename(const char *filter, const char *fname);
EXPORTED_FUNCTION const char *get_open_filename_ext(const char *filter, const char *fname, const char *dir, const char *title);
EXPORTED_FUNCTION const char *get_open_filenames(const char *filter, const char *fname);
EXPORTED_FUNCTION const char *get_open_filenames_ext(const char *filter, const char *fname, const char *dir, const char *title);
EXPORTED_FUNCTION const char *get_save_filename(const char *filter, const char *fname);
EXPORTED_FUNCTION const char *get_save_filename_ext(const char *filter, const char *fname, const char *dir, const char *title);
EXPORTED_FUNCTION const char *get_directory(const char *dname);
EXPORTED_FUNCTION const char *get_directory_alt(const char *capt, const char *root);
EXPORTED_FUNCTION int get_color(int defcol);
EXPORTED_FUNCTION int get_color_ext(int defcol, const char *title);
EXPORTED_FUNCTION const char *widget_get_caption();
EXPORTED_FUNCTION void widget_set_caption(const char *str);
EXPORTED_FUNCTION const char *widget_get_owner();
EXPORTED_FUNCTION void widget_set_owner(const char *hwnd);
EXPORTED_FUNCTION const char *widget_get_icon();
EXPORTED_FUNCTION void widget_set_icon(const char *icon);
EXPORTED_FUNCTION const char *widget_get_system();
EXPORTED_FUNCTION void widget_set_system(const char *sys);
EXPORTED_FUNCTION void widget_set_button_name(int type, const char *name);
EXPORTED_FUNCTION const char *widget_get_button_name(int type);
EXPORTED_FUNCTION bool widget_get_canceled();
#endif

namespace dialog_module {

  int show_message(const char *str);
  int show_message_cancelable(const char *str);
  int show_question(const char *str);
  int show_question_cancelable(const char *str);
  int show_attempt(const char *str);
  int show_error(const char *str, bool abort);
  const char *get_string(const char *str, const char *def);
  const char *get_password(const char *str, const char *def);
  double get_integer(const char *str, double def);
  double get_passcode(const char *str, double def);
  const char *get_open_filename(const char *filter, const char *fname);
  const char *get_open_filename_ext(const char *filter, const char *fname, const char *dir, const char *title);
  const char *get_open_filenames(const char *filter, const char *fname);
  const char *get_open_filenames_ext(const char *filter, const char *fname, const char *dir, const char *title);
  const char *get_save_filename(const char *filter, const char *fname);
  const char *get_save_filename_ext(const char *filter, const char *fname, const char *dir, const char *title);
  const char *get_directory(const char *dname);
  const char *get_directory_alt(const char *capt, const char *root);
  int get_color(int defcol);
  int get_color_ext(int defcol, const char *title);
  const char *widget_get_caption();
  void widget_set_caption(const char *str);
  const char *widget_get_owner();
  void widget_set_owner(const char *hwnd);
  const char *widget_get_icon();
  void widget_set_icon(const char *icon);
  const char *widget_get_system();
  void widget_set_system(const char *sys);
  void widget_set_button_name(int type, const char *name);
  const char *widget_get_button_name(int type);
  bool widget_get_canceled();
  
} // namespace dialog_module

#if !defined(DIALOG_MODULE_GAME_MAKER_BUILD)
inline int show_message(const char *str) {
  return dialog_module::show_message(str);
}

inline int show_message_cancelable(const char *str) {
  return dialog_module::show_message_cancelable(str);
}

inline int show_question(const char *str) {
  return dialog_module::show_question(str);
}

inline int show_question_cancelable(const char *str) {
  return dialog_module::show_question_cancelable(str);
}

inline int show_attempt(const char *str) {
  return dialog_module::show_attempt(str);
}

inline int show_error(const char *str, bool abort) {
  return dialog_module::show_error(str, abort);
}

inline const char *get_string(const char *str, const char *def) {
  return dialog_module::get_string(str, def);
}

inline const char *get_password(const char *str, const char *def) {
  return dialog_module::get_password(str, def);
}

inline double get_integer(const char *str, double def) {
  return dialog_module::get_integer(str, def);
}

inline double get_passcode(const char *str, double def) {
  return dialog_module::get_passcode(str, def);
}

inline const char *get_open_filename(const char *filter, const char *fname) {
  return dialog_module::get_open_filename(filter, fname);
}

inline const char *get_open_filename_ext(const char *filter, const char *fname, const char *dir, const char *title) {
  return dialog_module::get_open_filename_ext(filter, fname, dir, title);
}

inline const char *get_open_filenames(const char *filter, const char *fname) {
  return dialog_module::get_open_filenames(filter, fname);
}

inline const char *get_open_filenames_ext(const char *filter, const char *fname, const char *dir, const char *title) {
  return dialog_module::get_open_filenames_ext(filter, fname, dir, title);
}

inline const char *get_save_filename(const char *filter, const char *fname) {
  return dialog_module::get_save_filename(filter, fname);
}

inline const char *get_save_filename_ext(const char *filter, const char *fname, const char *dir, const char *title) {
  return dialog_module::get_save_filename_ext(filter, fname, dir, title);
}

inline const char *get_directory(const char *dname) {
  return dialog_module::get_directory(dname);
}

inline const char *get_directory_alt(const char *capt, const char *root) {
  return dialog_module::get_directory_alt(capt, root);
}

inline int get_color(int defcol) {
  return dialog_module::get_color(defcol);
}

inline int get_color_ext(int defcol, const char *title) {
  return dialog_module::get_color_ext(defcol, title);
}

inline const char *widget_get_caption() {
  return dialog_module::widget_get_caption();
}

inline void widget_set_caption(const char *str) {
  dialog_module::widget_set_caption(str);
}

inline const char *widget_get_icon() {
  return dialog_module::widget_get_icon();
}

inline void widget_set_icon(const char *icon) {
  dialog_module::widget_set_icon(icon);
}

inline const char *widget_get_owner() {
  return dialog_module::widget_get_owner();
}

inline void widget_set_owner(const char *hwnd) {
  dialog_module::widget_set_owner(hwnd);
}

inline const char *widget_get_system() {
  return dialog_module::widget_get_system();
}

inline void widget_set_system(const char *sys) {
  dialog_module::widget_set_system(sys);
}

inline const char *widget_get_button_name(int type) {
  return dialog_module::widget_get_button_name(type);
}

inline void widget_set_button_name(int type, const char *name) {
  dialog_module::widget_set_button_name(type, name);
}

inline bool widget_get_canceled() {
  return dialog_module::widget_get_canceled();
}
#endif
