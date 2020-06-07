#if SQLITE_ENABLE
#include "../include/SQLiteManager.hpp"

using namespace std;

SQLiteManager::SQLiteManager()
{
    // Try open db file
    if(sqlite3_open("ipget.db", &instance))
    {
        fprintf(stderr,
         "Unable to open database\nError stacktrace: %s", 
         sqlite3_errmsg(instance)
        );
    }
    fprintf(stdout, "Opened database successfully\n");
}

SQLiteManager::~SQLiteManager()
{
    // This close the sqlite3.
    if(sqlite3_close(instance))
    {
        fprintf(stderr,
         "Unable to close database\nError stacktrace: %s", 
         sqlite3_errmsg(instance)
        );
    } 
    fprintf(stdout, "Closed database successfully\n");
    
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
void SQLiteManager::executeCmd(ArgT Query,ECmdSelect SelectCmd, int(* finishCb),ArgT Args...)
{
    char* sQuery;
    // Get type and convert the generic string to right type.
    if (typeid(Query) == typeid(std::string))
        char* sQuery = Query.c_str();
    else
        char* sQuery = Query;
    
    char** errMsg;
        
    switch (SelectCmd)
    {
        case ECmdSelect::SELECT:
            sqlite3_exec(this->instance, sQuery, finishCb, errMsg); 

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
#endif