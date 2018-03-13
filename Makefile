all: build/ackermann.o build/open_close.o build/use_after_free.o

build/%.o: c/%.c
	mkdir -p build
	clang -c $^ -o $@

build/%.class: java/%.java
	javac $^ -d build

.PHONY: clean

clean:
	rm -rf build
