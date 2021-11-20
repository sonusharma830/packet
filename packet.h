#ifndef PACKET_H
#define PACKET_H

typedef int UINT32;
typedef short int UINT16;
typedef char UINT8;

#define CONNECT_COMMAND (0xAA01)

#define PACKET_HEADER 0x8765u
#define PACKET_FOOTER 0x431u

#define CMD_PORT 1000

#endif // PACKET_H
