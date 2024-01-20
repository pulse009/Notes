#include <cstdlib>
#include "libpq-fe.h"

// Data for generation connection request
struct DbConnectParameters {
    const char* username;
    const char* password;
    std::string host;
};

// Data for adding note
struct InfoToInsert {
    std::string task;
    std::string deadline;
};

struct InfoToUpdate {
    int id;
    std::string updatableInfo;
    std::string newValue;
};

// todo: сделать изменение порядкового номера
struct InfoToDelete {
    int id;
};

enum class QueryType {
    INSERT, 
    UPDATE, 
    DELETE, 
    SELECT
};

class DatabaseManager {
private: 
    PGconn* conn;

    // Connection request forming
    std::string getFullRequest (DbConnectParameters& parameters){
        std::string returnableQuery = "dbname=notes user=" + std::string(parameters.username) + " password=" + std::string(parameters.password) + parameters.host;
        return returnableQuery;
    }

    //unificated append function
    void submitQuery (const char* query){
        PGresult *result = PQexec(conn, query);

        if (PQresultStatus(result) == PGRES_COMMAND_OK) {
            std::cout << "Запрос выполнен успешно." << std::endl;

            // Освобождаем ресурсы
            PQclear(result);
        } else {
            std::cerr << "Не удалось выполнить SQL-запрос: " << PQerrorMessage(conn) << std::endl;
        }
    }

    void deadlineDateParser (std::string& date){
        date = date.substr(6,4) + "-" + date.substr(3,2) + "-" + date.substr(0,2);
    }

    //Forming ready-to-append INSERT query
    std::string insertQueryForming (std::string& task, std::string& date){
        std::string queryStr = "INSERT INTO notes (note) VALUES ('" + task + "');";

        if (date != ""){
            deadlineDateParser (date);
            queryStr = "INSERT INTO notes (note, deadline) VALUES ('" + task + "', '" + date + "');";
        }
        return queryStr;
    }

    //Forming ready-to-append UPDATE query
    std::string updateQueryForming (int& id, std::string& updatableInfo, std::string& newValue){
        std::string queryStr = "UPDATE notes SET " + updatableInfo + " = '" + newValue + "' WHERE id = " + std::to_string(id) + ";";
        return queryStr;
    }

    std::string deleteQueryForming (int& id){
        std::string queryStr = "DELETE from notes WHERE id = " + std::to_string(id) + ";";
        return queryStr;
    }

public:
    void connectToServer(DbConnectParameters& requestParameters){
        std::string request = getFullRequest(requestParameters);

        // Connection
        conn = PQconnectdb(request.c_str());
    } 
    

    //Sending additional request
    void add (std::string& task, std::string& date){
        std::string queryStr = insertQueryForming(task, date);
        const char* query = queryStr.c_str();
        submitQuery(query);
    }

    //Updating and appending changed information
    void update (int& id, std::string& columnName, std::string& newValue){
        std::string queryStr = updateQueryForming(id, columnName, newValue);
        const char* query = queryStr.c_str();
        submitQuery(query);

    }

    //Deleting function
    void remove (int& id){
        std::string queryStr = deleteQueryForming(id);
        const char* query = queryStr.c_str();
        submitQuery(query);
    }

    void stopConnection(){
        PQfinish(conn);
    }
};