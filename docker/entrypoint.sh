#!/bin/bash

# 初始化操作，例如复制默认配置文件
if [ ! -f /etc/ospf_d/ospf_d.conf ]; then
    mkdir -p /etc/ospf_d
    cp ospf_d.conf /etc/ospf_d/ospf_d.conf
fi

# 启动 OSPF 守护进程
exec "$@"
