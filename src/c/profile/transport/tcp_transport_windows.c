#include <micrortps/client/profile/transport/tcp_transport_windows.h>

/*******************************************************************************
 * Private function declarations.
 *******************************************************************************/
static bool send_tcp_msg(void* instance, const uint8_t* buf, size_t len);
static bool recv_tcp_msg(void* instance, uint8_t** buf, size_t* len, int timeout);
static int get_tcp_error();

/*******************************************************************************
 * Private function definitions.
 *******************************************************************************/
static bool send_tcp_msg(void* instance, const uint8_t* buf, size_t len)
{
    bool rv = true;
    TCPTransport* transport = (TCPTransport*)instance;
    size_t bytes_sent = 0;
    int send_rv = 0;

    while (bytes_sent < len && rv)
    {
        send_rv = send(transport->socket_fd, (char*)buf, (int)len, 0);
        if (SOCKET_ERROR != bytes_sent)
        {
            bytes_sent += (size_t)send_rv;
        }
        else
        {
            rv = false;
        }
    }

    return rv;
}

static bool recv_tcp_msg(void* instance, uint8_t** buf, size_t* len, int timeout)
{
    bool rv = true;
    TCPTransport* transport = (TCPTransport*)instance;

    int poll_rv = WSAPoll(&transport->poll_fd, 1, timeout);
    if (0 < poll_rv)
    {
        int bytes_received = recv(transport->socket_fd, (void*)transport->buffer, sizeof(transport->buffer), 0);
        if (SOCKET_ERROR != bytes_received)
        {
            *len = (size_t)bytes_received;
            *buf = transport->buffer;
        }
        else if (0 == poll_rv)
        {
           rv = false;
           WSASetLastError(WAIT_TIMEOUT);
        }
        else
        {
            rv = false;
        }
    }

    return rv;
}

static int get_tcp_error()
{
    return WSAGetLastError();
}

/*******************************************************************************
 * Public function definitions.
 *******************************************************************************/
int init_udp_transport(TCPTransport* transport, const char* ip, uint16_t port)
{
    int rv = 0;

    /* Socket initialization. */
    transport->socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == transport->socket_fd)
    {
        rv = WSAGetLastError();
    }

    if (0 < rv)
    {
        /* Remote IP setup. */
        struct sockaddr_in temp_addr;
        temp_addr.sin_family = AF_INET;
        temp_addr.sin_port = port;
        temp_addr.sin_addr.s_addr = inet_addr(ip);
        memset(temp_addr.sin_zero, '\0', sizeof(temp_addr.sin_zero));
        transport->remote_addr = *((struct sockaddr *)&temp_addr);

        /* Poll setup. */
        transport->poll_fd.fd = transport->socket_fd;
        transport->buffer.events = POLLIN;

        /* Server connection. */
        int connected = connect(transport->socket_fd,
                                &transport->remote_addr,
                                sizeof(transport->remote_addr));
        if (SOCKET_ERROR == connected)
        {
            rv = WSAGetLastError();
        }
        else
        {
            /* Interface setup. */
            transport->comm.instance = (void*)transport;
            transport->comm.send_msg = send_tcp_msg;
            transport->comm.recv_msg = recv_tcp_msg;
            transport->comm.comm_error = get_tcp_error;
        }
    }

    return rv;
}