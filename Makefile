CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lpthread

LIB_SRCS = $(wildcard src/lib/*.c)
OSPF_SRCS = $(wildcard src/ospf/*.c)
TEST_SRCS = $(wildcard tests/*.c)

LIB_OBJS = $(LIB_SRCS:.c=.o)
OSPF_OBJS = $(OSPF_SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

INCLUDES = -Iinclude

all: ospf_d

ospf_d: $(LIB_OBJS) $(OSPF_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

tests: $(LIB_OBJS) $(OSPF_OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o test_ospf $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f ospf_d test_ospf $(LIB_OBJS) $(OSPF_OBJS) $(TEST_OBJS)
