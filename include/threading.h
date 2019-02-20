#include <pthread.h>
#include <future>
#include <cstdarg>

// TODO - Need refactor the class.
template<class T>
class CThread
{
public:
      CThread();
      ~CThread();
      
      inline void CreateThread(void* in, void* args...)
      {
	      pthread_t thread;
            // Iterate from vargs and get aruments
	      pthread_create (&tread, NULL, &in, NULL);
      }
    
      inline void CreateThreadArgs(void* func, void* args...)
      {
            
      }
      
      inline void RunThread(void* m)
      {
	      this->CreateThread(m, NULL);
      }
      template<typename T>
      inline static std::future<T>MakeSharedFuture()
      {

      }
      
      T RunAsAsync();

private:
      std::mutex _mutex;
      
};
