build: makefile
	cmake --build build

makefile:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
	ctags -R .

xcode:
	cmake -S . -B xcode -GXcode

release:
	cmake -S . -B release -DCMAKE_BUILD_TYPE=Release
	cmake --build release --config Release

format:
	find src -iname "*.h" -o -iname "*.c" | xargs clang-format -i --style=file

clean:
	rm -rf build release xcode

.PHONY: format xcode makefile build release clean
.SILENT:
