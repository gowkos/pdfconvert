#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>//结构体addrinfo, in_addr
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char **argv){
	char *hostname;
	struct addrinfo hints,*result, *rp;
	int err;
	in6_addr addr6;
	in_addr addr;
	char dst[INET6_ADDRSTRLEN+1];
  
	//没有输入域名时，博客园的网址，返回实际IP地址
	hostname = argc < 2 ? (char *)"www.cnblogs.com" : argv[1];

	memset(&hints, 0, sizeof(addrinfo));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_UNSPEC;


	if((err = getaddrinfo(hostname, NULL, &hints, &result)) != 0){
		printf("error %d : %s\n", err, gai_strerror(err));
		return 1;
	}
  
	for (rp = result; rp != NULL; rp = rp->ai_next) {

		if(rp->ai_family == AF_INET)
			{
				addr.s_addr = ((sockaddr_in*)(rp->ai_addr))->sin_addr.s_addr;
				inet_ntop(AF_INET, &addr, dst,  INET_ADDRSTRLEN);
				fprintf(stdout, "ip addresss: %s\n", dst);
			}
		else if(rp->ai_family == AF_INET6)
			{
				addr6 = ((sockaddr_in6*)(rp->ai_addr))->sin6_addr;
				inet_ntop(AF_INET6, &addr6, dst,  INET6_ADDRSTRLEN);
				fprintf(stdout, "ip6 addresss: %s\n", dst);
			}
		else
			{
				fprintf(stderr,"Internal Error!\n");
				freeaddrinfo(result);
				return 1;
			}

	}

	freeaddrinfo(result);

	return 0;
}
