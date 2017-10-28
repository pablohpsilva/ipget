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
			std::cout << "usage: ipget <option> <paramter>\n" 
				     "				      \n"	
				     "options:			      \n"
				     "									\n"
				     "-x				Retrive external IP from web.\n"
				     "-X				Retrive Internal IP from web DNS.\n"
				     "-V				Show program version.\n"
				     "-h				Show this help.\n"
				     "-p	[ip] [port]		Check the status of given port from given machine.\n\n";
			return 0;
		}

		try
		{	
			if( std::string(argv[i]) == "-p") 
			{
			  char* host = argv[i+1];
			  int port = std::stoi( argv[i+2]);
			  p_check->CheckPort(host, port);
			  return 0;
			}
		}
		catch(std::exception& e)
		{
			std::cout<<"An error has occured.\nSee description: "<<e.what()<<std::endl;
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
