cd "${0%/*}";
clang++ DialogModule.cpp libdlgmod.a -framework AppKit -framework UniformTypeIdentifiers -I. -o DialogModule;
