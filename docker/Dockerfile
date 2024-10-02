FROM ubuntu:20.04

# 设置非交互式安装
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    libpthread-stubs0-dev \
    net-tools \
    iproute2

# 复制项目文件
COPY . /ospf_d
WORKDIR /ospf_d

# 编译项目
RUN make

# 暴露必要的端口（如果需要）
EXPOSE 2604

# 设置入口点
ENTRYPOINT ["./ospf_d", "-c", "config/ospf_d.conf"]
