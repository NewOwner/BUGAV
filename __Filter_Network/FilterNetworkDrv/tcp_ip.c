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

BOOLEAN inspect_list(PNET_BUFFER_LIST nbl_ptr) {
   
    PNET_BUFFER nb_ptr = NET_BUFFER_LIST_FIRST_NB(nbl_ptr);
    
    while (nb_ptr != NULL) {
    
        PMDL nb_curmdl = NET_BUFFER_CURRENT_MDL(nb_ptr);
        PVOID net_dataptr = MmGetMdlVirtualAddress(nb_curmdl);
        FLT_NETWORK_DATA frame_data = parse_frame((PUCHAR)net_dataptr);

        DbgPrint("NDIS: \tinspect_packet\n");
        
        BOOLEAN drop = inspect_packet(&frame_data);
        if (drop == TRUE) {
            DbgPrint("### MATCH!!! --> Drop it!++++++++++++++\n");
            ULONG nb_data_length = NET_BUFFER_DATA_LENGTH(nb_ptr);
            _dump_bytes((PUCHAR)net_dataptr, nb_data_length);
            dump_packet(&frame_data);
            DbgPrint("### MATCH!!! --> Drop it!--------------\n");
            return TRUE;
        } else {
        }
        nb_ptr = NET_BUFFER_NEXT_NB(nb_ptr);
    }
    return FALSE;
}

BOOLEAN inspect_packet(PFLT_NETWORK_DATA packet_data) {
    BOOLEAN match = FALSE;  // TRUE - drop, FALSE - forward
    PNET_RULES rule_ptr = __ndisNetRules;
    while (rule_ptr != NULL) {
        match = TRUE;

        //UCHAR ether_type[2];
        if (*((UINT16*)rule_ptr->ether_type) == 0) { DbgPrint("ignore ethertype\n"); /*ignore*/ }
        else if (memcmp(packet_data->eth_hdr->type, rule_ptr->ether_type, 2) != 0) { 
            match = FALSE; 
            rule_ptr = rule_ptr->_next;
            continue; 
        }
        
        //UCHAR ip_next_protocol[1];
        if (packet_data->ipv4_hdr != NULL) {

            if (*((UCHAR*)rule_ptr->ip_next_protocol) == 0) { DbgPrint("ignore ipnext\n"); /*ignore*/ }
            else if (memcmp(packet_data->ipv4_hdr->protocol, rule_ptr->ip_next_protocol, 1) != 0) {
                match = FALSE;
                rule_ptr = rule_ptr->_next;
                continue;
            }
        
            //UCHAR source_ip[4];
            if (*((UINT32*)rule_ptr->source_ip) == 0) { DbgPrint("ignore srcip\n"); /*ignore*/ }
            else if (memcmp(packet_data->ipv4_hdr->source_ip, rule_ptr->source_ip, 4) != 0) {
                match = FALSE;
                rule_ptr = rule_ptr->_next;
                continue;
            }
        
            //UCHAR destination_ip[4];
            if (*((UINT32*)rule_ptr->destination_ip) == 0) { DbgPrint("ignore dstip\n"); /*ignore*/ }
            else if (memcmp(packet_data->ipv4_hdr->destination_ip, rule_ptr->destination_ip, 4) != 0) {
                match = FALSE;
                rule_ptr = rule_ptr->_next;
                continue;
            }
        }
        
        if (packet_data->tcp_hdr != NULL) {

            //UCHAR source_port[2];
            if (*((UINT16*)rule_ptr->source_port) == 0) { DbgPrint("ignore srcport\n"); /*ignore*/ }
            else if (memcmp(packet_data->tcp_hdr->source_port, rule_ptr->source_port, 2) != 0) {
                match = FALSE;
                rule_ptr = rule_ptr->_next;
                continue;
            }
        
            //UCHAR destination_port[2];
            if (*((UINT16*)rule_ptr->destination_port) == 0) { DbgPrint("ignore dstport\n"); /*ignore*/ }
            else if (memcmp(packet_data->tcp_hdr->destination_port, rule_ptr->destination_port, 2) != 0) {
                match = FALSE;
                rule_ptr = rule_ptr->_next;
                continue;
            }
        }
        break;
    }
        
    return match;
}

VOID dump_packet(PFLT_NETWORK_DATA packet_data) {
    ETHER_HDR_DUMP(packet_data->eth_hdr);
    if (packet_data->arp_hdr != NULL) { ARP_HDR_DUMP(packet_data->arp_hdr); }
    if (packet_data->ipv4_hdr != NULL) { IPV4_HDR_DUMP(packet_data->ipv4_hdr); }
    if (packet_data->tcp_hdr != NULL) { TCP_HDR_DUMP(packet_data->tcp_hdr); }
}