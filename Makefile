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
	@echo "Build successful"

default: build

clean:
	rm -f $(TARGET)
