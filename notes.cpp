#include <iostream>
#include <string>
#include "notes.h"
#include <cstdlib>

DatabaseManager databaseManager;

int main() {
    DbConnectParameters requestParameters;
    requestParameters.username = "tester";
    requestParameters.password = "123";
    requestParameters.host     = "localhost";

    databaseManager.ConnectToServer(requestParameters);

    InfoToInsert insertParameters;
    insertParameters.task = "Clean house";

    databaseManager.AddTask(insertParameters.task);

    databaseManager.StopConnection();

    return 0;
}