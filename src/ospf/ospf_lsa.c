#include "ospf_lsa.h"
#include "memory.h"
#include <string.h>

// 创建 LSA 数据库
ospf_lsa_db_t *ospf_lsa_db_create()
{
    ospf_lsa_db_t *db = xmalloc(sizeof(ospf_lsa_db_t));
    db->lsa_list = NULL;
    return db;
}

// 向 LSA 数据库添加 LSA
void ospf_lsa_db_add(ospf_lsa_db_t *db, ospf_lsa_t *lsa)
{
    lsa->next = db->lsa_list;
    db->lsa_list = lsa;
}

// 创建新的 LSA
ospf_lsa_t *ospf_lsa_create()
{
    ospf_lsa_t *lsa = xmalloc(sizeof(ospf_lsa_t));
    memset(lsa, 0, sizeof(ospf_lsa_t));
    return lsa;
}

// 释放 LSA
void ospf_lsa_free(ospf_lsa_t *lsa)
{
    if (lsa)
    {
        xfree(lsa->data);
        xfree(lsa);
    }
}
