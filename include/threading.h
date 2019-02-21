#include <pthread.h>
#include <future>
<<<<<<< Updated upstream
#include <cstdarg>

// TODO - Need refactor the class.
template<class T>
=======

/**
 * @brief The main Thread Class
 * Thread class for all asyncrinous operations.
 */
>>>>>>> Stashed changes
class CThread
{
public:

      CThread();
      ~CThread();
      
<<<<<<< Updated upstream
      inline void CreateThread(void* in, void* args...)
      {
	      pthread_t thread;
            // Iterate from vargs and get aruments
	      pthread_create (&tread, NULL, &in, NULL);
      }
    
      inline void CreateThreadArgs(void* func, void* args...)
      {
            
=======
      template<typename T>
      inline static std::shared_future<T>MakeSharedFuture()
      {

>>>>>>> Stashed changes
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
      inline static K RunAsync(void(*function)(),Args... inArgs)
      {
<<<<<<< Updated upstream
	      this->CreateThread(m, NULL);
      }
      template<typename T>
      inline static std::future<T>MakeSharedFuture()
      {

=======
            // Get args by va parse
            std::future<K> fut = std::async(function, inArgs...);
            while(fut.wait())
            {
                  std::cout << "Waiting to process ..." << std::endl;
            }
            return fut.get();    
>>>>>>> Stashed changes
      }
      
private:
      std::mutex _mutex;
      
};
