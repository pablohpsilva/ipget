#include "../include/WindowManager.hpp"


WindowManager::WindowManager
(
    std::vector<float>ScreenSize, 
    std::string Title,
    int FLAG_API
) : title("An exemple of a Ipget."), flag_api(0)
{
    // check if we vect has desired size.
    try
    {
        if(ScreenSize.size() > 2)
        {
            std::cout << "The size of vect must be 2.";
            throw("The size of vect must be 2");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }    
}

// TODO - Create windows manager delete safer thread
WindowManager::~WindowManager()
{

}
