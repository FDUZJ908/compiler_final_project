
main: build/bin build/main.cc build/tokenizer.cc src/syntax.h
	@g++ -g build/main.cc build/tokenizer.cc -lfl -o build/bin/main -I "src"

build/bin:
	mkdir -p build/bin

build/main.cc: src/main.y 
	@bison src/main.y -o build/main.cc --defines=build/main.tab.h

build/tokenizer.cc: build/main.cc src/tokenizer.l 
	@flex -o build/tokenizer.cc src/tokenizer.l



clean:
				@-rm -rf build
.PHONY: clean
