# Makefile
CC = g++
CFLAGS = -std=c++11 -Iinclude -pthread

SRC = src/main.cpp src/gbr_daemon.cpp src/gbr_protocol.cpp src/vty_server.cpp src/config_manager.cpp
OBJ = $(SRC:.cpp=.o)

TARGET = gbr_daemon

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
