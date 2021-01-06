#define  SOCK_STREAM             1 /*virtual circuit*/ //tcp
#define  SOCK_DGRAM              2 /*datagram*/// udp
#define  SOCK_RAW                3 /*raw socket*/
#define  SOCK_RDM                4 /*reliably-delivered message*/
#define  SOCK_CONN_DGRAM         5 /*connection datagram*/
#define SOCK_PACKET	10         /* linux specific way of	*/


#define AF_UNSPEC	0
#define AF_UNIX		1	/* Unix domain sockets 		*/
#define AF_INET		2	/* Internet IP Protocol 	*/
#define AF_AX25		3	/* Amateur Radio AX.25 		*/
#define AF_IPX		4	/* Novell IPX 			*/
#define AF_APPLETALK	5	/* Appletalk DDP 		*/
#define	AF_NETROM	6	/* Amateur radio NetROM 	*/
#define AF_BRIDGE	7	/* Multiprotocol bridge 	*/
#define AF_AAL5		8	/* Reserved for Werner's ATM 	*/
#define AF_X25		9	/* Reserved for X.25 project 	*/
#define AF_INET6	10	/* IP version 6			*/
#define AF_MAX		12	/* For now.. */


#define SOCKET_ERROR     -1
