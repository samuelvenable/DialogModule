cd "${0%/*}/libdlgmod" && make && cd "..";
if [ "$OS" = "Windows_NT" ]; then
  xxd -i "IDI_APPICON.png" > "IDI_APPICON.h";
  windres "IDI_APPICON.rc" -o "IDI_APPICON.o";
  g++ "DialogModule.cpp" "libdlgmod/libdlgmod-cc.a" "IDI_APPICON.o" -o "DialogModule.exe" -DPROCESS_GUIWINDOW_IMPL -DNULLIFY_STDERR -I"libdlgmod" -std=c++17 -static-libgcc -static-libstdc++ -static -lntdll -lgdi32 -lgdiplus -lcomctl32 -lshlwapi -lcomdlg32 -lole32 -loleaut32 -luuid -mwindows -fPIC;
  rm -fr "IDI_APPICON.o";
elif [ `uname` = "Darwin" ]; then
  xxd -i "IDI_APPICON_MAC.png" > "IDI_APPICON_MAC.h";
  mkdir -p "DialogModule.app/Contents/MacOS";
  clang++ "DialogModule.cpp" "libdlgmod/libdlgmod-cc.a" -o "DialogModule.app/Contents/MacOS/DialogModule" -I"libdlgmod" -std=c++17 -ObjC++ -framework AppKit -framework UniformTypeIdentifiers -mmacos-version-min=11.0 -arch arm64 -arch x86_64 -fPIC;
  ln -s "DialogModule.app/Contents/MacOS/DialogModule" "DialogModule";
elif [ `uname` = "Linux" ]; then
  xxd -i "IDI_APPICON.png" > "IDI_APPICON.h";
  g++ "DialogModule.cpp" "libdlgmod/libdlgmod-cc.a" -o "DialogModule" -DPROCESS_GUIWINDOW_IMPL -DNULLIFY_STDERR -DUSE_XDG_DESKTOP_PORTAL -I"libdlgmod" -std=c++17 -static-libgcc -static-libstdc++ `pkg-config --cflags --libs x11 xrandr xinerama` `pkg-config --cflags --libs dbus-1` -lpthread -fPIC;
elif [ `uname` = "FreeBSD" ]; then
  xxd -i "IDI_APPICON.png" > "IDI_APPICON.h";
  clang++ "DialogModule.cpp" "libdlgmod/libdlgmod-cc.a" -o "DialogModule" -DPROCESS_GUIWINDOW_IMPL -DNULLIFY_STDERR -I"libdlgmod" -std=c++17 `pkg-config --cflags --libs x11 xrandr xinerama` -lkvm -lc -lpthread -fPIC;
elif [ `uname` = "DragonFly" ]; then
  xxd -i "IDI_APPICON.png" > "IDI_APPICON.h";
  g++ "DialogModule.cpp" "libdlgmod/libdlgmod-cc.a" -o "DialogModule" -DPROCESS_GUIWINDOW_IMPL -DNULLIFY_STDERR -I"libdlgmod" -std=c++17 -static-libgcc `pkg-config --cflags --libs x11 xrandr xinerama` -lkvm -lc -lpthread -fPIC;
elif [ `uname` = "NetBSD" ]; then
  xxd -i "IDI_APPICON.png" > "IDI_APPICON.h";
  g++ "DialogModule.cpp" "libdlgmod/libdlgmod-cc.a" -o "DialogModule" -DPROCESS_GUIWINDOW_IMPL -DNULLIFY_STDERR -I"libdlgmod" -std=c++17 -static-libgcc `pkg-config --cflags --libs x11 xrandr xinerama` -I/usr/x11 xrandr xineramaR7/include -Wl,-rpath,/usr/x11 xrandr xineramaR7/lib -L/usr/x11 xrandr xineramaR7/lib -lkvm -lc -lpthread -fPIC;
elif [ `uname` = "OpenBSD" ]; then
  xxd -i "IDI_APPICON.png" > "IDI_APPICON.h";
  clang++ "DialogModule.cpp" "libdlgmod/libdlgmod-cc.a" -o "DialogModule" -DPROCESS_GUIWINDOW_IMPL -DNULLIFY_STDERR -I"libdlgmod" -std=c++17 `pkg-config --cflags --libs x11 xrandr xinerama` -lkvm -lc -lpthread -fPIC;
elif [ `uname` = "SunOS" ]; then
  xxd -i "IDI_APPICON.png" > "IDI_APPICON.h";
  export PKG_CONFIG_PATH=/usr/lib/64/pkgconfig;
  g++ "DialogModule.cpp" "libdlgmod/libdlgmod-cc.a" -o "DialogModule" -DPROCESS_GUIWINDOW_IMPL -DNULLIFY_STDERR -I"libdlgmod" -std=c++17 -static-libgcc `pkg-config --cflags --libs x11 xrandr xinerama` -lkvm -lc -lproc -lpthread -fPIC;
fi;
