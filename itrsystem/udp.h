#ifndef __UDP__
#define __UDP__

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <string>

using std::string;

namespace itr_system
{
    class Udp
    {
        private:
            int sock;
            struct sockaddr_in selfAddr;
            struct sockaddr_in dstAddr;
            int recmsg;
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
            Udp(int port,bool wait)
            {
                sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
                bzero(&selfAddr,sizeof(sockaddr_in));
                bzero(&dstAddr,sizeof(sockaddr_in));
                dstAddr.sin_family=AF_INET;
                selfAddr.sin_family=AF_INET;
                selfAddr.sin_addr.s_addr=htonl(INADDR_ANY);
                selfAddr.sin_port=htons(port);
                bind(sock,(struct sockaddr *)&selfAddr,sizeof(selfAddr));
                recmsg=wait?0:MSG_DONTWAIT;
            }
            ~Udp()
            {
                close(sock);
            }
            int Send(const UdpPackage &package)
            {
                socklen_t slen = sizeof(dstAddr);
                dstAddr.sin_port=htons(package.port);
                inet_aton(package.IP.c_str(),&dstAddr.sin_addr);
                return sendto(sock,package.pbuffer,package.len,0,(struct sockaddr *)&dstAddr,slen);
            }

            int Receive(char *buf,int buffSize)
            {
                socklen_t slen = sizeof(dstAddr);
                int recv_len = recvfrom(sock, buf, buffSize, recmsg, (struct sockaddr *) &dstAddr,&slen);
                return recv_len;
            }
    };
}
#endif
