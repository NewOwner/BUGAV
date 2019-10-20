#pragma once
void _dump_bytes(PUCHAR buf, size_t buf_len);

typedef struct _ETHRENET_HDR {
    UCHAR   dst[6];
    UCHAR   src[6];
    UCHAR   type[2];
}ETHRENET_HDR, *PETHRENET_HDR;
#define ETHER_HDR_DUMP(eth)         DbgPrint("\nEthernet: ");    \
                                    DbgPrint("\tdst: ");    _dump_bytes(eth->dst, 6);   \
                                    DbgPrint("\tsrc: ");    _dump_bytes(eth->src, 6);    \
                                    DbgPrint("\ttype: ");   _dump_bytes(eth->type, 2);

PETHRENET_HDR get_etherhdr(PUCHAR frame);

typedef struct _ARP_HDR {
    UCHAR   hardware_type[2];
    UCHAR   protocol_type[2];
    UCHAR   hardware_size[1];
    UCHAR   protocol_size[1];
    UCHAR   opcode_request[2];
    UCHAR   sender_mac[6];
    UCHAR   sender_ip[4];
    UCHAR   target_mac[6];
    UCHAR   target_ip[4];
}ARP_HDR, * PARP_HDR;
#define ARP_HDR_DUMP(arp)   DbgPrint("\nARP: ");    \
                            DbgPrint("\thardware_type: ");    _dump_bytes(arp->hardware_type,2);\
                            DbgPrint("\tprotocol_type: ");    _dump_bytes(arp->protocol_type,2 );\
                            DbgPrint("\thardware_size: ");    _dump_bytes(arp->hardware_size,1 );\
                            DbgPrint("\tprotocol_size: ");    _dump_bytes(arp->protocol_size,1 );\
                            DbgPrint("\topcode_request: ");   _dump_bytes(arp->opcode_request,2);\
                            DbgPrint("\tsender_mac: ");       _dump_bytes(arp->sender_mac,6    );\
                            DbgPrint("\tsender_ip: ");        _dump_bytes(arp->sender_ip,4     );\
                            DbgPrint("\ttarget_mac: ");       _dump_bytes(arp->target_mac,6    );\
                            DbgPrint("\ttarget_ip: ");        _dump_bytes(arp->target_ip,4     );

PARP_HDR get_arphdr(PUCHAR frame);

typedef struct _IPV4_HDR {
    UCHAR   version[1];
    UCHAR   type_of_service[1];
    UCHAR   total_len[2];
    UCHAR   id[2];
    UCHAR   flags[2];
    UCHAR   ttl[1];
    UCHAR   protocol[1];
    UCHAR   hdr_checksum[2];
    UCHAR   source_ip[4];
    UCHAR   destination_ip[4];
}IPV4_HDR, * PIPV4_HDR;
#define IPV4_HDR_DUMP(ip)    DbgPrint("\nIPV4: ");    \
                            DbgPrint("\tversion: ");              _dump_bytes(ip->version,1         );\
                            DbgPrint("\ttype_of_service: ");      _dump_bytes(ip->type_of_service,1 );\
                            DbgPrint("\ttotal_len: ");            _dump_bytes(ip->total_len,2       );\
                            DbgPrint("\tid: ");                   _dump_bytes(ip->id,2              );\
                            DbgPrint("\tflags: ");                _dump_bytes(ip->flags,2           );\
                            DbgPrint("\tttl: ");                  _dump_bytes(ip->ttl,1             );\
                            DbgPrint("\tprotocol: ");             _dump_bytes(ip->protocol,1        );\
                            DbgPrint("\thdr_checksum: ");         _dump_bytes(ip->hdr_checksum,2    );\
                            DbgPrint("\tsource_ip: ");            _dump_bytes(ip->source_ip,4       );\
                            DbgPrint("\tdestination_ip: ");       _dump_bytes(ip->destination_ip,4  );

PIPV4_HDR get_ipv4hdr(PUCHAR frame);

typedef struct _TCP_HDR {
    UCHAR   source_port[2];
    UCHAR   destination_port[2];
    UCHAR   sequence_num[4];
    UCHAR   acknowledge_num[4];
    UCHAR   header_len_flags[2];    // XXX
    UCHAR   windows_sz[2];
    UCHAR   checksum[2];
    UCHAR   urgent_ptr[2];
}TCP_HDR, * PTCP_HDR;
#define TCP_HDR_DUMP(tcp)    DbgPrint("\nTCP: ");    \
                            DbgPrint("\tsource_port: ");_dump_bytes(tcp->source_port,2      );\
                            DbgPrint("\tdestination_port: ");_dump_bytes(tcp->destination_port,2 );\
                            DbgPrint("\tsequence_num: ");_dump_bytes(tcp->sequence_num,4     );\
                            DbgPrint("\tacknowledge_num: ");_dump_bytes(tcp->acknowledge_num,4  );\
                            DbgPrint("\theader_len_flags: ");_dump_bytes(tcp->header_len_flags,2 );\
                            DbgPrint("\twindows_sz: ");_dump_bytes(tcp->windows_sz,2       );\
                            DbgPrint("\tchecksum: ");_dump_bytes(tcp->checksum,2         );\
                            DbgPrint("\turgent_ptr: ");_dump_bytes(tcp->urgent_ptr,2       );

PTCP_HDR get_tcphdr(PUCHAR frame);

typedef struct _FLT_NETWORK_DATA {
    PETHRENET_HDR eth_hdr;
    PARP_HDR arp_hdr;
    PIPV4_HDR ipv4_hdr;
    PTCP_HDR tcp_hdr;
}FLT_NETWORK_DATA, * PFLT_NETWORK_DATA;

FLT_NETWORK_DATA parse_frame(PUCHAR frame);