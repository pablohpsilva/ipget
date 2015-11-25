#include <string.h> /* for strncpy */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <ifaddrs.h>

using namespace std;

class GetIP
{
   public:
	GetIP();
	~GetIP();
	//Get an Internal IP and return it with provide type;
	char* GetInternalIP(char*);
	//Get an External IP and return it with provide type;
	void GetExternalIP();     
	//variables
	int fd;
	struct ifaddrs * ifAddrStruct = NULL;
	struct ifaddrs * ifa = NULL;
	void * pAddrTmp;


};
