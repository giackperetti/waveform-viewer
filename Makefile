CC = g++
CFLAGS = -Wall -O2
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = src/wave.cxx
TARGET = bin/wave

.PHONY: run build clean

run: build
	./$(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

build: $(TARGET)
	@echo -e "\033[1mBuild ended succesfully!\033[0m"

default: build

clean:
	rm -f $(TARGET)
