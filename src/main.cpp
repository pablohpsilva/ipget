#include "../include/printer.h"


int main (int argc, char** argv)
{
	GetIP* ip = new GetIP();
	
	char* addr = ip->GetInternalIP("enp2s0");
	
//	std::cout << "DE" << addr << std::endl;
	
	if(ip != NULL)
	{
		delete ip;
	}		

	return 0;
}
