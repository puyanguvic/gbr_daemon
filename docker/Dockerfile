# 使用ubuntu 22.04作为基础镜像
FROM ubuntu:22.04

# 更新包列表并安装编译器g++和make
RUN apt update && apt install -y g++ make && apt clean

# 将源代码复制到容器中
COPY . /gbr_daemon

# 设置工作目录
WORKDIR /gbr_daemon

# 编译项目
RUN make

# 运行GBR守护进程
CMD ["./gbr_daemon"]
