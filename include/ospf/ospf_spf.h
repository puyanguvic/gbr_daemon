#ifndef OSPF_SPF_H
#define OSPF_SPF_H

#include "ospf_lsa.h"

// 调度 SPF 计算任务
void ospf_schedule_spf_calculation(ospf_instance_t *ospf);

// 执行 SPF 计算
void *ospf_spf_calculate(void *arg);

#endif // OSPF_SPF_H
