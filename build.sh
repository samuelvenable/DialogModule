cd "${0%/*}";
if [ "$OS" = "Windows_NT" ]; then
  g++ DialogModule.cpp libdlgmod.a -o "DialogModule.exe" -DPROCESS_GUIWINDOW_IMPL -DNULLIFY_STDERR -I. -std=c++17 -static-libgcc -static-libstdc++ -static -lntdll -lgdiplus -lcomctl32 -lshlwapi -lcomdlg32 -lole32 -loleaut32 -luuid -fPIC;
elif [ `uname` = "Darwin" ]; then
  clang++ DialogModule.cpp libdlgmod.a -o "DialogModule" -I. -std=c++17 -ObjC++ -framework AppKit -framework UniformTypeIdentifiers -mmacos-version-min=11.0 -arch arm64 -arch x86_64 -fPIC;
elif [ `uname` = "Linux" ]; then
  g++ DialogModule.cpp libdlgmod.a -o "DialogModule" -DPROCESS_GUIWINDOW_IMPL -DNULLIFY_STDERR -DUSE_XDG_DESKTOP_PORTAL -Ilibdlgmod/xlib/nfd/src/include -I. -std=c++17 -static-libgcc -static-libstdc++ `pkg-config --cflags --libs x11` `pkg-config --cflags --libs dbus-1` -lpthread -fPIC;
elif [ `uname` = "FreeBSD" ]; then
  clang++ DialogModule.cpp libdlgmod.a -o "DialogModule" -DPROCESS_GUIWINDOW_IMPL -DNULLIFY_STDERR -I. -std=c++17 `pkg-config --cflags --libs x11` -lkvm -lc -lpthread -fPIC;
elif [ `uname` = "DragonFly" ]; then
  g++ DialogModule.cpp libdlgmod.a -o "DialogModule" -DPROCESS_GUIWINDOW_IMPL -DNULLIFY_STDERR -I. -std=c++17 -static-libgcc `pkg-config --cflags --libs x11` -lkvm -lc -lpthread -fPIC;
elif [ `uname` = "NetBSD" ]; then
  g++ DialogModule.cpp libdlgmod.a -o "DialogModule" -DPROCESS_GUIWINDOW_IMPL -DNULLIFY_STDERR -I. -std=c++17 -static-libgcc `pkg-config --cflags --libs x11` -I/usr/X11R7/include -Wl,-rpath,/usr/X11R7/lib -L/usr/X11R7/lib -lkvm -lc -lpthread -fPIC;
elif [ `uname` = "OpenBSD" ]; then
  clang++ DialogModule.cpp libdlgmod.a -o "DialogModule" -DPROCESS_GUIWINDOW_IMPL -DNULLIFY_STDERR -I. -std=c++17 `pkg-config --cflags --libs x11` -lkvm -lc -lpthread -fPIC;
elif [ `uname` = "SunOS" ]; then
  export PKG_CONFIG_PATH=/usr/lib/64/pkgconfig;
  g++ DialogModule.cpp libdlgmod.a -o "DialogModule" -DPROCESS_GUIWINDOW_IMPL -DNULLIFY_STDERR -I. -std=c++17 -static-libgcc `pkg-config --cflags --libs x11` -lkvm -lc -lproc -lpthread -fPIC;
fi;
