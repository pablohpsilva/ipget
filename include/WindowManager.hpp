#include <iostream>
#include <memory>
#include <vector>

/**
 * 
 * Get GTK headers */
#if _GUI_ | _GTK_
#include <gtk-3.0/gtk/gtk.h>
#define GTKAPP GtkApplication 
#define GTKPTR gpointer
#endif

/**
 * @brief Windows Method from Windows.
 * @describe Get all libs from windows SO screens;
 */
#if _WIN_
#include <Windows.h>
#define _WINAPP WHANDLE
#define _WINPTR WPTR
#endif

#if !NOGUI
    #define _WINAPP int
    #define _WINPTR int
#endif

/**
 * @brief Class GUI
 * Class to make all graphic interface to program.
 */
class WindowManager
{
    private:
        std::string title;
        int flag_api;
        float screenX;
        float screenY;
  public:
    /* Constructor with no Args, defaul is size/2 */
    WindowManager(std::vector<float>ScreenSize, std::string Title, int FLAG_API);
    ~WindowManager();

    /**
	* @brief Create Single Window Frame
    * Create Window frame with no options
	*/
    void createFrame();

    /**
     * @brief Activate main window context
     * 
     * @param app Application Pointer
     * @param user_data Pointer for objects in application
     */
    static void activate(_WINAPP *app, _WINPTR user_data);
};