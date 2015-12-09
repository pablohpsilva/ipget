#include "../include/printer.h"

#define __PROGRAM__VERSION "This program was made by Mainstream IT and Software enginier.\nAnd is under GNU license.\nVersion = 1.0.0\n"

int main (int argc, char* argv[])
{
	//Intanciate classes
	GetIP* ip = new GetIP();
	PortCheck *p_check = new PortCheck();
	
	
//Args Opts
	for (int i = 0; i < argc; i++)
	{
	//	std::cout<< std::string(argv[i])<< std::endl;
		
		if( std::string(argv[i]) == "-x")
	        {
	
			 ip->GetExternalIP();
		         return 0;
	        }

		if ( std::string(argv[i]) == "-X")
		{
			ip->GetExternalIpByDns();
			return 0;
		}
		
		if( std::string(argv[i]) == "-V" )
		{
		        std::cout << __PROGRAM__VERSION << std::endl;
			return 0;

		}
		
		if( std::string(argv[i]) == "-h") 
		{
		  char* host = argv[i+1];
		  int port = std::stoi( argv[i+2]);
		  p_check->CheckPort(host, port);
		  return 0;
		}
		    
	
	}
	ip->GetInternalIP("eth0");

	if(ip != NULL)
	{
		delete ip;	
		delete p_check;
	}		

	return 0;
}
