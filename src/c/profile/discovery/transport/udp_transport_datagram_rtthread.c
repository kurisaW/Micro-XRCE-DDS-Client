/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-12-04     Wangyuqiang  the first version
 */


#include "udp_transport_datagram_internal.h"

#include <stdio.h>
#include <string.h>


bool uxr_init_udp_transport_datagram(
        uxrUDPTransportDatagram* transport)
{
    bool rv = false;
    struct hostent *host = RT_NULL;

    if (ip_protocol != UXR_IPv4) {
        printf("Unsupported ip protocol\n");
        goto __exit;
    }

    host = (struct hostent *)gethostbyname(ip);
    if (host == RT_NULL)
    {
        printf("Get host by name failed!");
        goto __exit;
    }

    if((transport->sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        printf("Create socket error\n");
        goto __exit;
    }

    transport->server_addr.sin_family = AF_INET;
    transport->server_addr.sin_port = htons(atoi(port));
    transport->server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    rt_memset(&(server_addr.sin_zero), 0, sizeof(transport->server_addr.sin_zero));

    if (connect(transport->fd, (struct sockaddr *)&(transport->server_addr), sizeof(struct sockaddr)) == -1)
    {
        printf("Connect fail!\n");
        if (transport->sock >= 0)
        {
            closesocket(transport->sock);
            transport->sock = -1;
        }
        goto __exit;
    }

    rv = true;
__exit:
    return rv;
}

bool uxr_close_udp_transport_datagram(
        uxrUDPTransportDatagram* transport)
{
    if (transport->sock >= 0)
    {
        closesocket(transport->sock);
        transport->sock = -1;
    }
    return true;
}

bool uxr_udp_send_datagram_to(
        uxrUDPTransportDatagram* transport,
        const uint8_t* buf,
        size_t len,
        const TransportLocator* locator)
{
    bool rv = true;
    switch (locator->format)
    {
        case ADDRESS_FORMAT_MEDIUM:
        {
            transport->server_addr.sin_family = AF_INET;
            transport->server_addr.sin_port = htons(atoi(port));
            transport->server_addr.sin_addr = *((struct in_addr *)host->h_addr);
            rt_memset(&(transport->server_addr.sin_zero), 0, sizeof(transport->server_addr.sin_zero));

            memcpy(&transport->server_addr.sin_addr, locator->_.medium_locator.address, sizeof(transport->server_addr.sin_addr));
            transport->server_addr.sin_family = AF_INET;
            transport->server_addr.sin_port = htons(locator->_.medium_locator.locator_port);

            ssize_t bytes_sent = sendto(transport->fd, (const void*)buf, len, 0,
                            (struct sockaddr*)&transport->server_addr, sizeof(transport->server_addr));
            if (0 > bytes_sent)
            {
                rv = false;
            }
            break;
        }
        default:
            rv = false;
            break;
    }
    return rv;
}

bool uxr_udp_recv_datagram(
        uxrUDPTransportDatagram* transport,
        uint8_t** buf,
        size_t* len,
        int timeout)
{
    bool rv = false;

    timeout = (timeout <= 0) ? 1 : timeout;

    struct timeval tv;
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = (timeout % 1000) * 1000;

    if (0 != setsockopt(transport->fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)))
    {
        return false;
    }

    ssize_t bytes_received = recv(transport->fd, (void*)transport->buffer, sizeof(transport->buffer), 0);
    if (-1 != bytes_received)
    {
        *len = (size_t)bytes_received;
        *buf = transport->buffer;
        rv = true;
    }

    return rv;

}

void uxr_bytes_to_ip(
        const uint8_t* bytes,
        char* ip)
{
    struct in_addr addr;
    addr.s_addr = (in_addr_t)(*bytes + (*(bytes + 1) << 8) + (*(bytes + 2) << 16) + (*(bytes + 3) << 24));
    char* internal_ip = inet_ntoa(addr);
    strcpy(ip, internal_ip);
}