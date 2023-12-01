#include "udp_transport_datagram_internal.h"

#include <stdio.h>
#include <string.h>

#ifdef RTT_UCLIENT_PLATFORM_RTTHREAD
#include <rtthread.h>
#include <sys/socket.h>
#include <netdb.h>
#endif

bool uxr_init_udp_transport_datagram(
        uxrUDPTransportDatagram* transport)
{
    printf("\n\nuxr_init_udp_transport_datagram.\n\n");
//     bool rv = false;

//     if(transport->poll_fd.fd = socket(AF_INET, SOCKET_DGRAM, IPPROTO_UDP) == -1)
//     {
//         rt_kprintf("Create socket error\n");
//         goto __exit;
//     }
//     transport->poll_fd.fd = rv;
//     transport->poll_fd.events = POLLIN;

//     rv = true;
// __exit:
//     return rv;
}

bool uxr_close_udp_transport_datagram(
        uxrUDPTransportDatagram* transport)
{
    printf("\n\nuxr_close_udp_transport_datagram.\n\n");
    // if (transport->sock >= 0)
    // {
    //     closesocket(transport->sock);
    //     transport->sock = -1;
    // }
    // return true;
}

bool uxr_udp_send_datagram_to(
        uxrUDPTransportDatagram* transport,
        const uint8_t* buf,
        size_t len,
        const TransportLocator* locator)
{
    printf("\n\nuxr_udp_send_datagram_to.\n\n");
    // bool rv = true;
    // switch (locator->format)
    // {
    //     case ADDRESS_FORMAT_MEDIUM:
    //     {
    //         struct sockaddr_in remote_addr;
            
    //         remote_addr.sin_family = AF_INET;
    //         remote_addr.sin_port = htons(atoi(port));
    //         remote_addr.sin_addr = *((struct in_addr *)host->h_addr);
    //         rt_memset(&(remote_addr.sin_zero), 0, sizeof(remote_addr.sin_zero));

    //         memcpy(&remote_addr.sin_addr, locator->_.medium_locator.address, sizeof(remote_addr.sin_addr));
    //         remote_addr.sin_family = AF_INET;
    //         remote_addr.sin_port = htons(locator->_.medium_locator.locator_port);

    //         ssize_t bytes_sent = sendto(transport->poll_fd.fd, (const void*)buf, len, 0,
    //                         (struct sockaddr*)&remote_addr, sizeof(remote_addr));
    //         if (0 > bytes_sent)
    //         {
    //             rv = false;
    //         }
    //         break;
    //     }
    //     default:
    //         rv = false;
    //         break;
    // }
    // return rv;
}

bool uxr_udp_recv_datagram(
        uxrUDPTransportDatagram* transport,
        uint8_t** buf,
        size_t* len,
        int timeout)
{
    printf("\n\nuxr_udp_recv_datagram.\n\n");
    // bool rv = false;

    // int poll_rv = poll(&transport->poll_fd, 1, timeout);
    // if (0 < poll_rv)
    // {
    //     ssize_t bytes_received = recv(transport->poll_fd.fd, (void*)transport->buffer, sizeof(transport->buffer), 0);
    //     if (0 < bytes_received)
    //     {
    //         *len = (size_t)bytes_received;
    //         *buf = transport->buffer;
    //         rv = true;
    //     }
    // }
    // else if (0 == poll_rv)
    // {
    //     errno = ETIME;
    // }

    // return rv;
}

void uxr_bytes_to_ip(
        const uint8_t* bytes,
        char* ip)
{
    printf("\n\nuxr_bytes_to_ip.\n\n");
    // struct in_addr addr;
    // addr.s_addr = (in_addr_t)(*bytes + (*(bytes + 1) << 8) + (*(bytes + 2) << 16) + (*(bytes + 3) << 24));
    // char* internal_ip = inet_ntoa(addr);
    // strcpy(ip, internal_ip);
}
