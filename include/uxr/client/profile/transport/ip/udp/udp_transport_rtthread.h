#ifndef UXR_CLIENT_PROFILE_TRANSPORT_IP_UDP_RTTHREAD_H_
#define UXR_CLIENT_PROFILE_TRANSPORT_IP_UDP_RTTHREAD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <rtthread.h>

typedef struct uxrUDPPlatform
{
    int sock;
    struct sockaddr_in server_addr;
} uxrUDPPlatform;

#ifdef __cplusplus
}
#endif

#endif // UXR_CLIENT_PROFILE_TRANSPORT_IP_UDP_RTTHREAD_H_