#include "domen.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

void
get_domen (const char * domen)
{
	int             status;
	struct addrinfo hints, *p;
	char            ipstr[INET6_ADDRSTRLEN];

	memset(&hints,0,sizeof(hints));
	hints.ai_family   = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((status = getaddrinfo(domen,0,&hints,&p))) {
		fprintf(stderr,"getaddrinfo: %s\n",gai_strerror(status));
		exit(3);
	}

	printf("IP addrs for %s:\n\n",domen);
	for(;;) {
		if (!p) { break; }
		void * addr;
		char * ipver;

		if (p->ai_family == AF_INET) {
			struct sockaddr_in * ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		} else if (p->ai_family == AF_INET6) {
			struct sockaddr_in6 * ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		} else {
			puts("  ERR: unsupported ai_family");
			continue;
		}

		inet_ntop(p->ai_family,addr,ipstr,sizeof(ipstr));
		printf("  %s: %s\n",ipver,ipstr);
		p=p->ai_next;
	}

	freeaddrinfo(p);
}
