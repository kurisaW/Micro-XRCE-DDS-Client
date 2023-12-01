#ifndef UXR_CLIENT_PROFILE_TRANSPORT_IP_UDP_RTTHREAD_H_
#define UXR_CLIENT_PROFILE_TRANSPORT_IP_UDP_RTTHREAD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef RTT_UCLIENT_PLATFORM_RTTHREAD
#include <sys/types.h>
#include <sys/socket.h>
#include "netdb.h"
#include <rtthread.h>
#endif // RTT_UCLIENT_PLATFORM_RTTHREAD

typedef struct uxrUDPPlatform
{
    int sock;
} uxrUDPPlatform;

#ifdef __cplusplus
}
#endif

#endif // UXR_CLIENT_PROFILE_TRANSPORT_IP_UDP_RTTHREAD_H_