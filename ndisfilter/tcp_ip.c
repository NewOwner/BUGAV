#include "precomp.h"

void _dump_bytes(PUCHAR buf, size_t buf_len) {
    size_t i = 0;
    for (i = 0; i < buf_len; ++i) {
        DbgPrint("%02X%s", buf[i], (i + 1) % 16 == 0 ? "\r\n" : " ");
    }
    DbgPrint("\n");
}

PETHRENET_HDR get_etherhdr(PUCHAR frame) {
    PETHRENET_HDR hdr = (PETHRENET_HDR)frame;
    return hdr;
}

PARP_HDR get_arphdr(PUCHAR frame) {
    PARP_HDR hdr = (PARP_HDR)frame;
    return hdr;
}

PIPV4_HDR get_ipv4hdr(PUCHAR frame) {
    PIPV4_HDR hdr = (PIPV4_HDR)frame;
    return hdr;
}

PTCP_HDR get_tcphdr(PUCHAR frame) {
    PTCP_HDR hdr = (PTCP_HDR)frame;
    return hdr;
}

FLT_NETWORK_DATA parse_frame(PUCHAR frame) {
    FLT_NETWORK_DATA net_data = { 0 };
    PUCHAR frame_ptr = frame;
    net_data.eth_hdr = get_etherhdr(frame_ptr);
    frame_ptr += sizeof(ETHRENET_HDR);

    UCHAR   __ethertype_ip[2] = {0x08, 0x00};
    UCHAR   __ethertype_arp[2] = { 0x08, 0x06 };
    if (memcmp(net_data.eth_hdr->type, __ethertype_ip, 2)==0) {
        net_data.ipv4_hdr = get_ipv4hdr(frame_ptr);
        frame_ptr += sizeof(IPV4_HDR);
    } else if (memcmp(net_data.eth_hdr->type, __ethertype_arp, 2)==0) {
        net_data.arp_hdr = get_arphdr(frame_ptr);
        frame_ptr += sizeof(ARP_HDR);
        return net_data;
    }

    net_data.tcp_hdr = get_tcphdr(frame_ptr);

    return net_data;
}