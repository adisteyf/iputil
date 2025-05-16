#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ifaddrs.h>

void
get_myself(void)
{
	struct ifaddrs *ifa;
	char ip[INET_ADDRSTRLEN];
	getifaddrs(&ifa);

	printf("your ips:\n\n");
	for (;;) {
		if (!ifa) { break; }
		if (ifa->ifa_addr && ifa->ifa_addr->sa_family==AF_INET) {
			inet_ntop(AF_INET, &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr, ip, sizeof(ip));
			printf("%s: %s\n",ifa->ifa_name,ip);
		}

		ifa = ifa->ifa_next;
	}

	freeifaddrs(ifa);
}
