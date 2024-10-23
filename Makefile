build: makefile
	cmake --build build

makefile:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
	ctags -R .

xcode:
	cmake -S . -B xcode -GXcode

format:
	find src -iname "*.h" -o -iname "*.c" | xargs clang-format -i --style=file

.PHONY: format xcode makefile build
