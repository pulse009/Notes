#include <string>
#include <cstdlib>
#include "libpq-fe.h"

//Data for generation connection request
struct DbConnectParameters {
    const char* username;
    const char* password;
    std::string host;
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

public:
    //Connection request forming
    std::string GetFullRequest(DbConnectParameters& parameters){
        std::string returnableQuery = "dbname=notes user=" + std::string(parameters.username) + " password=" + std::string(parameters.password) + parameters.host;
        return returnableQuery;
    }

    void ConnectToServer(DbConnectParameters& requestParameters){
        std::string request = GetFullRequest(requestParameters);

        // Connection
        conn = PQconnectdb(request.c_str());
    }

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

    void StopConnection(){
        PQfinish(conn);
    }
};