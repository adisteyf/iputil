#include "domen.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

static char * get_protocol (int);
static char * get_socktype (int);


static char *
get_protocol (int num)
{
	switch (num) {
		case IPPROTO_UDP:
			return "udp";
		case IPPROTO_TCP:
			return "tcp";

		default:
			return "???";
	}
}

static char *
get_socktype (int num)
{
	switch (num) {
		case SOCK_STREAM:
			return "SOCK_STREAM";
		case IPPROTO_TCP:
			return "IPPROTO_TCP";

		default:
			return "???";
	}
}

void
get_domen (const char * domen)
{
	int             status;
	struct addrinfo hints, *p;
	char            ipstr[INET6_ADDRSTRLEN];

	bzero(&hints,sizeof(hints));
	hints.ai_family   = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((status = getaddrinfo(domen,0,&hints,&p))) {
		fprintf(stderr,"get_domen,getaddrinfo: %s\n",gai_strerror(status));
		exit(3);
	}

	printf("IP addrs for %s:\n\n",domen);
	for(;;) {
		if (!p) { break; }
		void * addr;
		char * ipver;

		if (p->ai_family == AF_INET) {
			struct sockaddr_in * ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr       = &(ipv4->sin_addr);
			ipver      = "IPv4";
		} else if (p->ai_family == AF_INET6) {
			struct sockaddr_in6 * ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			addr       = &(ipv6->sin6_addr);
			ipver      = "IPv6";
		} else {
			puts("  ERR: unsupported ai_family");
			continue;
		}

		inet_ntop(p->ai_family,addr,ipstr,sizeof(ipstr));
		printf("  %s: %s (%s) | sock: %s, flags: %d\n",ipver,ipstr,get_protocol(p->ai_protocol),get_socktype(p->ai_socktype),p->ai_flags);
		p=p->ai_next;
	}

	freeaddrinfo(p);
}
