build:
	cmake --build build

ninja:
	cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug -G Ninja
	cp build/compile_commands.json compile_commands.json
	ctags -R .

xcode:
	cmake -S . -B xcode -GXcode

release:
	cmake -S . -B release -DCMAKE_BUILD_TYPE=Release -G Ninja
	cmake --build release --config Release

test: ninja
	cmake --build build
	ctest --test-dir build --output-on-failure

format:
	find src -iname "*.h" -o -iname "*.c" | xargs clang-format -i --style=file

tidy:
	find src -iname "*.h" -o -iname "*.c" | xargs clang-tidy

clean:
	rm -rf build release xcode

.PHONY: format tidy xcode makefile build release clean ninja test
.SILENT:
