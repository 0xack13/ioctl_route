#include<errno.h>
#include<stdio.h>
#include<string.h>
#include <net/route.h>
#include <sys/types.h>
#include <sys/ioctl.h>

int main()
{
    int sockfd;
    struct rtentry route;
    struct sockaddr_in *addr;
    int err = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == -1)
    {
        perror("Socket failed..");
        return -1;
    }

    memset(&route, 0, sizeof(route));
    addr = (struct sockaddr_in*) &route.rt_gateway;
    addr->sin_family = AF_INET;
    // this gateway should be up
    addr->sin_addr.s_addr = inet_addr("172.16.78.2");
    
    addr = (struct sockaddr_in*) &route.rt_dst;
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = inet_addr("10.10.10.0");

    addr = (struct sockaddr_in*) &route.rt_genmask;
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = inet_addr("255.255.255.0");

    route.rt_flags = RTF_UP | RTF_GATEWAY;

    if((err = ioctl(sockfd, SIOCADDRT, &route)) != 0 )
    {
        perror("SIOCADDRT failed");
        return -1;
    }

}
