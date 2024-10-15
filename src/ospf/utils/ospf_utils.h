#ifndef OSPF_UTILS_H
#define OSPF_UTILS_H

#include <stdint.h>
#include <stdbool.h>
// #include "ospf_main.h" // 假设此文件中定义了结构体 ospf_lsa 等

/* 常量定义 */
#define OSPF_MAX_AGE 3600         /* LSA 最大老化时间，单位：秒 */
#define OSPF_LS_REFRESH_TIME 1800 /* LSA 刷新时间，单位：秒 */
#define OSPF_DEFAULT_METRIC 10    /* 默认度量值 */

/* 枚举类型 */
typedef enum
{
    OSPF_SUCCESS = 0,
    OSPF_ERROR = -1
} ospf_status_t;

/* 实用函数声明 */

/* 计算 IP 校验和 */
uint16_t ospf_calculate_checksum(const void *data, int length);

/* 更新 LSA 的老化时间 */
void ospf_update_lsa_age(struct ospf_lsa *lsa);

/* 比较 Router ID，大于返回 1，等于返回 0，小于返回 -1 */
int ospf_compare_router_id(uint32_t id1, uint32_t id2);

/* 转换 IP 地址为字符串 */
const char *ospf_ip_to_string(uint32_t ip_addr);

/* 检查 IP 地址是否在指定前缀内 */
bool ospf_ip_in_prefix(uint32_t ip_addr, uint32_t prefix, uint8_t prefix_length);

/* 获取当前时间戳（秒） */
uint32_t ospf_current_time(void);

/* 打印调试信息 */
void ospf_log_debug(const char *format, ...);

#endif /* OSPF_UTILS_H */
