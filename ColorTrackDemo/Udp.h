#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <string>
using std::string;
class Udp
{
private:
    int sock;
    struct sockaddr_in selfAddr;
    struct sockaddr_in dstAddr;

public:
    /**
    **/
    class UdpPackage
    {
    public:
        string IP;
        int port;
        char *pbuffer;
        int len;
    };
    Udp()
    {
        sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
        bzero(&dstAddr,sizeof(sockaddr_in));
        dstAddr.sin_family=AF_INET;
    }
    Udp(int port)
    {
        sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
        bzero(&selfAddr,sizeof(sockaddr_in));
        bzero(&dstAddr,sizeof(sockaddr_in));
        dstAddr.sin_family=AF_INET;
        selfAddr.sin_family=AF_INET;
        selfAddr.sin_addr.s_addr=htonl(INADDR_ANY);
        selfAddr.sin_port=htons(port);
        bind(sock,(struct sockaddr*)&selfAddr,sizeof(selfAddr));
    }

    int Send(const UdpPackage &package)
    {
        socklen_t slen = sizeof(dstAddr);
        dstAddr.sin_port=htons(package.port);
        inet_aton(package.IP.c_str(),&dstAddr.sin_addr);
        sendto(sock,package.pbuffer,package.len,0,(struct sockaddr *)&dstAddr,slen);
    }

    int Receive(char* buf,int buffSize)
    {
        socklen_t slen = sizeof(dstAddr);
        int recv_len = recvfrom(sock, buf, buffSize, 0, (struct sockaddr *) &dstAddr,&slen);
        return recv_len;
    }
};
