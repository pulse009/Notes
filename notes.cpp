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
    insertParameters.deadline = ""; 

    //the only way to input date
    insertParameters.deadline = "23.03.2024"; 

    databaseManager.AddTask(insertParameters.task, insertParameters.deadline);

    databaseManager.StopConnection();

    return 0;
}