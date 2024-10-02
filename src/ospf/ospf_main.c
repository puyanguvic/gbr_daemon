#include "ospf.h"
#include "log.h"
#include "memory.h"
#include <stdlib.h>

// 初始化 OSPF 实例
void ospf_init(ospf_instance_t *ospf)
{
    ospf->interfaces = NULL;                      // 初始化接口列表为空
    ospf->neighbors = NULL;                       // 初始化邻居列表为空
    ospf->lsa_db = ospf_lsa_db_create();          // 创建 LSA 数据库
    ospf->thread_master = thread_master_create(); // 创建线程管理器
}

// 启动 OSPF 协议处理
void ospf_start(ospf_instance_t *ospf)
{
    log_info("Starting OSPF instance with Router ID: %u", ospf->router_id);

    // 初始化所有接口
    ospf_interface_init_all(ospf);

    // 调度定时任务，如发送 Hello 包、执行 SPF 计算
    ospf_schedule_hello(ospf);
    ospf_schedule_spf_calculation(ospf);
}

int main(int argc, char **argv)
{
    // 分配并初始化 OSPF 实例
    ospf_instance_t *ospf = xmalloc(sizeof(ospf_instance_t));
    ospf->router_id = 1; // 设置路由器 ID，可以从配置文件读取

    // 初始化日志系统
    log_init(LOG_DEBUG);

    // 初始化并启动 OSPF
    ospf_init(ospf);
    ospf_start(ospf);

    // 主循环，处理线程事件
    while (1)
    {
        thread_process_events(ospf->thread_master);
    }

    return 0;
}
