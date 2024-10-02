# 编译器和编译选项
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lpthread

# 源文件目录
OSPF_DIR = src/ospf
LIB_DIR = src/lib
TEST_DIR = tests

# 头文件目录
INCLUDES = -Iinclude

# 源文件列表
LIB_SRCS = $(wildcard $(LIB_DIR)/*.c)
OSPF_SRCS = $(wildcard $(OSPF_DIR)/*.c)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)

# 对应的目标文件列表
LIB_OBJS = $(LIB_SRCS:.c=.o)
OSPF_OBJS = $(OSPF_SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

# 最终生成的可执行文件
TARGET = ospf_d
TEST_TARGET = test_ospf

# 默认目标
all: $(TARGET)

# 生成 ospf_d
$(TARGET): $(LIB_OBJS) $(OSPF_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# 生成测试程序
$(TEST_TARGET): $(LIB_OBJS) $(OSPF_OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# 生成目标文件
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 清理
clean:
	rm -f $(TARGET) $(TEST_TARGET) $(LIB_OBJS) $(OSPF_OBJS) $(TEST_OBJS)

# 安装
install:
	mkdir -p /usr/local/bin
	cp $(TARGET) /usr/local/bin/

# 卸载
uninstall:
	rm -f /usr/local/bin/$(TARGET)
