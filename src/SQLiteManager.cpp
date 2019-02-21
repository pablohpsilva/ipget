#include "../include/SQLiteManager.hpp"


using namespace std;

SQLiteManager::SQLiteManager()
{
    int rc = sqlite3_open("ipget.db", &instance);
    if(rc)
    {
        fprintf(stderr,
         "Unable to open database\nError stacktrace: %s", 
         sqlite3_errmsg(instance)
        );
    } else
    {
          fprintf(stdout, "Opened database successfully\n");
    }
}

SQLiteManager::~SQLiteManager()
{
    int rc = sqlite3_close(instance);   // This close the sqlite3.
    if(rc)
    {
        fprintf(stderr,
         "Unable to close database\nError stacktrace: %s", 
         sqlite3_errmsg(instance)
        );
    } 
    else
    {
        fprintf(stdout, "Closed database successfully\n");
    }
}

// Create a datatable.
bool SQLiteManager::CreateTable(std::string Name, std::string Query)
{
    if(Query.length() > 0)
    {
        std::cout << "We cant find a valid lenght for string.";
    }
    else
    {
        /* code */
    }
}

template<typename ArgT>
std::string SQLiteManager::executeCmd(ArgT Query,ECmdSelect SelectCmd, ArgT Args...)
{
    char* sQuery;
    // Get type and convert the generic string to right type.
    if (typeid(Query) == typeid(std::string))
        char* sQuery = Query.c_str();
    else
        char* sQuery = Query;
        
    switch (SelectCmd)
    {
        case ECmdSelect::SELECT:
            sqlite3_exec(this->instance, sQuery, [](void* ctx, int NumberArgc, char** data, char** columName){
                std::cout << "The query was executed" << std::endl;
                return std::string(data);
            }, [](char** errMsg){
                fprintf(stderr, "An error has occured: %s", errMsg);
            });
            break;

        case ECmdSelect::INSERT:
            break;

        case ECmdSelect::UPDATE:
            break;

        case ECmdSelect::DELETE:
            break;
        
        default:
            std::cout << "Not options was selected, skipping cmd execution" << std::endl;
            break;
    }
}

