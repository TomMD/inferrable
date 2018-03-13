all: build/ackermann.o build/open_close.c build/use_after_free.o

build/%.o: c/%.c
	mkdir -p build
	clang -c $^ -o $@

build/%.class: java/%.java
	javac $^ -d build
