#include <uxr/client/profile/transport/ip/ip.h>
#include <uxr/client/config.h>

#if defined(UCLIENT_PLATFORM_RTTHREAD)
#include <arpa/inet.h>
#include <sys/socket.h>
#endif /* if defined(UCLIENT_PLATFORM_RTTHREAD) */

bool uxr_ip_to_locator(
        char const* ip,
        uint16_t port,
        uxrIpProtocol ip_protocol,
        TransportLocator* locator)
{
    bool result = false;
    switch (ip_protocol)
    {
        case UXR_IPv4:
            locator->format = ADDRESS_FORMAT_MEDIUM;
            locator->_.medium_locator.locator_port = port;
            result = (1 == inet_pton(AF_INET, ip, locator->_.medium_locator.address));
            break;
        case UXR_IPv6:
            locator->format = ADDRESS_FORMAT_LARGE;
            locator->_.large_locator.locator_port = port;
            result = (1 == inet_pton(AF_INET6, ip, locator->_.large_locator.address));
            break;
        default:
            break;
    }
    return result;
}

bool uxr_locator_to_ip(
        TransportLocator const* locator,
        char* ip,
        size_t size,
        uint16_t* port,
        uxrIpProtocol* ip_protocol)
{
    bool result = false;
    switch (locator->format)
    {
        case ADDRESS_FORMAT_MEDIUM:
            *port = locator->_.medium_locator.locator_port;
            *ip_protocol = UXR_IPv4;
            result = (NULL != inet_ntop(AF_INET, locator->_.medium_locator.address, ip, (socklen_t)size));
            break;
        case ADDRESS_FORMAT_LARGE:
            *port = (uint16_t)locator->_.large_locator.locator_port;
            *ip_protocol = UXR_IPv6;
            result = (NULL != inet_ntop(AF_INET6, locator->_.large_locator.address, ip, (socklen_t)size));
            break;
        default:
            break;
    }
    return result;
}
