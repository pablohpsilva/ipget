/**
 * @file SQLiteManager.hpp
 * @author Jefferson Puchalski (puchiruzuki@gmail.com)
 * @brief The SQLite manager for Ipget.
 * @version 0.1
 * @date 2019-02-18
 * 
 * @copyright Copyright (c) 2019 Jefferson Puchalski
 * 
 */
#pragma once

#include <iostream>
#include <memory>
#include <sqlite3.h>

/**
 * @brief Enum for Cmd select
 * The selector for cmd
 */
enum class ECmdSelect : uint8_t
{
    SELECT,
    UPDATE,
    DELETE,
    INSERT
};

/**
 * @brief Class for SQLiteManager
 * The manager for SQLite Db.
 */
class SQLiteManager
{
private:
    // Instance SQLITE
    sqlite3 *instance;
    
    // Default string
    std::string dbName;

public:

    SQLiteManager();
    ~SQLiteManager();
    
    /**
     * @brief Create a Table object
     * Create a table with a given name.
     * @param Name The full qualified name for datatable.
     * @param Query If is provied, the datatable can add some default values after creation.
     * @return true If datatable was created and a default select is executed.
     * @return false If datatable cant be created. if is the case. a exception is throwed;
     */
    bool CreateTable(std::string Name, std::string Query = "" /* Default argument */);
    
    /*-------------------------------------------------------------
    *                   CRUD operations                           -
    *-------------------------------------------------------------*/
    
    /**
     * @brief Execute a db command in Given database
     * 
     * @param Query The query for select
     * @param Args VAargs to be parsed.
     * @param ECmdCommand The enum for type of comand.
     */
    template<typename ArgT>
    std::string executeCmd(ArgT Query, ECmdSelect SelectCmd, ArgT Args...);

};