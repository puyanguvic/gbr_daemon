// #ifndef OSPF_H
// #define OSPF_H

// #include "thread.h"
// #include "ospf_interface.h"
// #include "ospf_neighbor.h"
// #include "ospf_lsa.h"
// #include "ospf_spf.h"

// // 定义 OSPF 实例结构体，包含路由器 ID、接口列表等
// typedef struct
// {
//     uint32_t router_id;             // 本地路由器 ID
//     ospf_interface_t *interfaces;   // 接口列表
//     ospf_neighbor_t *neighbors;     // 邻居列表
//     ospf_lsa_db_t *lsa_db;          // LSA 数据库
//     thread_master_t *thread_master; // 线程管理器
// } ospf_instance_t;

// // 初始化 OSPF 实例
// void ospf_init(ospf_instance_t *ospf);

// // 启动 OSPF 实例
// void ospf_start(ospf_instance_t *ospf);

// #endif // OSPF_H
