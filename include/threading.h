#include <pthread.h>
#include <iostream>
#include <future>
#include <cstdarg>

/**
 * @brief The main Thread Class
 * Thread class for all asyncrinous operations.
 */
class CThread
{
public:

      CThread();
      ~CThread();
      
      inline void CreateThread(void* in, void* args...)
      {
	      pthread_t thread;
            // Iterate from vargs and get aruments
	      //TODO: Add more C++ threads.
            //pthread_create(&thread, NULL, &in, NULL);
      }

      /**
       * @brief Run Async
       * Run all function in asyncrinous mode.
       * @tparam K Type of given function
       * @tparam Args Type for variadic functions.
       * @param function Function pointer for async
       * @param inArgs Variadica function;
       * @return K The result from function.
       */
      template<typename K, typename... Args>
      inline static K RunAsync(K(* function)(void*),Args... inArgs)
      {
            //TODO: Need implement.
      
             // Get args by va parse
            std::future<K> fut = std::launch::async(function, inArgs...);
            while(fut.wait())
            {
                  std::cout << "Waiting to process ..." << std::endl;
            }
            return fut.get();    
            
      }
      template<typename T>
      inline static std::future<T>MakeSharedFuture()
      {
            // TODO Create future;    
      }
      
private:
      std::mutex _mutex;
      
};
