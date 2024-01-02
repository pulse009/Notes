#include <string>
#include <cstdlib>
#include "libpq-fe.h"

// Data for generation connection request
struct DbConnectParameters {
    const char* username;
    const char* password;
    std::string host;
};

// Data for adding note
// todo: еще добавить столбцов
struct InfoToInsert {
    std::string task;
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
    std::string GetFullRequest(DbConnectParameters& parameters){
        std::string returnableQuery = "dbname=notes user=" + std::string(parameters.username) + " password=" + std::string(parameters.password) + parameters.host;
        return returnableQuery;
    }

    //todo: сделать разделение на операции по QueryType
    void SendQueryToServer(QueryType type, const char* query){
        PGresult *result = PQexec(conn, query);

        if (PQresultStatus(result) == PGRES_COMMAND_OK) {
            std::cout << "Запрос выполнен успешно." << std::endl;

            // Освобождаем ресурсы
            PQclear(result);
        } else {
            std::cerr << "Не удалось выполнить SQL-запрос: " << PQerrorMessage(conn) << std::endl;
        }
    }

public:
    void ConnectToServer(DbConnectParameters& requestParameters){
        std::string request = GetFullRequest(requestParameters);

        // Connection
        conn = PQconnectdb(request.c_str());
    }

    void AddTask(std::string& task){
        std::string queryStr = "INSERT INTO notes(note) VALUES ('" + task + "');";
        const char* query = queryStr.c_str();
        SendQueryToServer(QueryType::INSERT, query);
    }

    void StopConnection(){
        PQfinish(conn);
    }
};