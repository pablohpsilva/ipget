#include <pthread.h>

template<class T>
class CThread
{
public:
      CThread();
      ~CThread();
      
      inline void CreateThread(void* in, void* args...)
      {
	pthread_t tread;
	pthread_create (&tread, NULL, &in, NULL);
      }
    
      inline void CreateThreadArgs(void* func, void* args...)
      {
	
      }
      
      inline void RunThread(void* m)
      {
	this->CreateThread(m, NULL);
      }
      
      T RunAsAsync();

private:
      std::mutex _mutex;
      
};
