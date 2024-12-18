build:
	cmake --build build

ctemplate:
	./extern/ctemplate/ctemplate ./src/array.ctypes ./src/array.ht
	./extern/ctemplate/ctemplate ./src/array.ctypes ./src/array.ct

ninja: ctemplate
	cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug -G Ninja
	cp build/compile_commands.json compile_commands.json
	ctags -R .

xcode:
	cmake -S . -B xcode -GXcode

release:
	cmake -S . -B release -DCMAKE_BUILD_TYPE=Release -G Ninja
	cmake --build release --config Release

# test: ninja
# 	cmake --build build
# 	ctest --test-dir build --output-on-failure

check: ninja
	find src -iname "*.h" -o -iname "*.c" | xargs clang-format -i --style=file
	find src -iname "*.h" -o -iname "*.c" | xargs clang-tidy

clean:
	rm -rf build release xcode gen

.PHONY: check xcode makefile build release clean ninja test ctemplate
.SILENT:
