#pragma once
#define  BUFF_SIZE 512

typedef struct _NET_RULES {
    UCHAR action;                   // 0x0 - alert, 0x1 - drop
    UCHAR ether_type[2];            // 0x08, 0x00 - ip, 0x08, 0x06 - arp
    UCHAR ip_next_protocol[1];      // 0x2 - IGMP, 0x11 - UDP, 0x6 - TCP 0x0 - ignore
    UCHAR source_ip[4];
    UCHAR destination_ip[4];
    UCHAR source_port[2];
    UCHAR destination_port[2];

    struct _NET_RULES* _next;
    struct _NET_RULES* _prev;
} NET_RULES, * PNET_RULES;

extern PNET_RULES __ndisNetRules;

VOID ndisReadCfg();
VOID ndisParseCfg(CHAR* cfg_buff);
VOID ndisPushRule(NET_RULES newrule);
VOID ndisDumpProtectedFileCfg();
VOID ndisDestroyProtectedFileCfg();
VOID ndisUpdateCfg();
