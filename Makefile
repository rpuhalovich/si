build: makefile
	cmake --build build

makefile:
	cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug
	cp build/compile_commands.json compile_commands.json
	ctags -R src

xcode:
	cmake -S . -B xcode -GXcode

release:
	cmake -S . -B release -DCMAKE_BUILD_TYPE=Release
	cmake --build release --config Release

format:
	find src -iname "*.h" -o -iname "*.c" | xargs clang-format -i --style=file

tidy:
	find src -iname "*.h" -o -iname "*.c" | xargs clang-tidy

clean:
	rm -rf build release xcode

.PHONY: format tidy xcode makefile build release clean
.SILENT:
