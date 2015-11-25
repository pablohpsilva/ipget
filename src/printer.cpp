#include <iostream>
#include "../include/printer.h"

using namespace std;

GetIP::GetIP()
{

}
GetIP::~GetIP()
{

}


char* GetIP::GetInternalIP(char* InterfaceName)
{
	//std::cout << "DEBUG InterfaceName = " << InterfaceName << endl;
	//getIfaddr struct info
	if ( getifaddrs(&ifAddrStruct) == -1)
	{
	   cout<<"Error initilize ifaddrs pointer"<<endl;
	   return "Error";
	}

	for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
	{
		if (ifa->ifa_addr->sa_family == AF_INET)
		{
		
			//Revice Memory adress from addr
			pAddrTmp = &((struct sockaddr_in *) ifa->ifa_addr)->sin_addr;
			//Buffer to Recive ip addr
			char addressBuffer[INET_ADDRSTRLEN];
		//	std::cout << "DEBUG IFNAME = " << ifa->ifa_name <<endl;
			char* ifname =  ifa->ifa_name;
			//Formate result and pass buffer
	         	inet_ntop(AF_INET, pAddrTmp, addressBuffer, INET_ADDRSTRLEN);
			std::cout << "INTERFACE " << ifname <<" = " <<   addressBuffer << endl;
			if(ifname == InterfaceName)
				return addressBuffer;
			
			
		}
	}

	freeifaddrs(ifAddrStruct);
}

