#include <pthread.h>

class CThread
{
public:
      CThread();
      ~CThread();
      
      inline void CreateThread(void* in)
      {
	pthread_t tread;
	
	pthread_create (&tread, NULL, &in, NULL);
	pthread_join(tread, NULL);
      }
      
      inline void RunThread(void* m)
      {
	this->CreateThread(m, NULL);
	
      }
private:
      
};