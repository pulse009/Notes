#include <iostream>
#include <string>
#include "notes.h"
#include <cstdlib>

DatabaseManager databaseManager;

int main() {
    DbConnectParameters requestParameters;
    requestParameters.username = "tester";
    requestParameters.password = "123";
    requestParameters.host = "localhost";

    databaseManager.ConnectToServer(requestParameters);

    //тестовый запрос
    const char* query = "INSERT INTO notes(note) VALUES ('Clean house');";

    databaseManager.SendQueryToServer(QueryType::INSERT, query);

    databaseManager.StopConnection();

    return 0;
}