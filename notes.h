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
// struct InfoToDelete {
//     std::string 
// }

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

    void appendQuery (const char* query){
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

    std::string insertQueryForming (std::string& task, std::string& date){
        std::string queryStr = "INSERT INTO notes (note) VALUES ('" + task + "');";

        if (date != ""){
            deadlineDateParser (date);
            queryStr = "INSERT INTO notes (note, deadline) VALUES ('" + task + "', '" + date + "');";
        }
        return queryStr;
    }

    std::string updateQueryForming (int& id, std::string& updatableInfo, std::string& newValue){
        std::string queryStr = "UPDATE notes SET " + updatableInfo + " = '" + newValue + "' WHERE id = " + std::to_string(id) + ";";
        return queryStr;
    }

public:
    void connectToServer(DbConnectParameters& requestParameters){
        std::string request = getFullRequest(requestParameters);

        // Connection
        conn = PQconnectdb(request.c_str());
    } 
    

    //Sending additional request to database
    void addTask (std::string& task, std::string& date){
        std::string queryStr = insertQueryForming(task, date);
        const char* query = queryStr.c_str();
        appendQuery(query);
    }

    //todo: сделать разделение на операции по QueryType
    //апдейт таски будет по id, потому что в случае применения в gui тыкаться апдейт будет по id
    void updateTask (int& id, std::string& columnName, std::string& newValue){
        std::string queryStr = updateQueryForming(id, columnName, newValue);
        const char* query = queryStr.c_str();
        appendQuery(query);

    }

    void stopConnection(){
        PQfinish(conn);
    }
};