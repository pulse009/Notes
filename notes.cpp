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

    databaseManager.connectToServer(requestParameters);

    //insert parameters
    InfoToInsert insertParameters;
    insertParameters.task = "Clean house";
    insertParameters.deadline = ""; 

    //update parameters
    InfoToUpdate updateParameters;
    updateParameters.id = 24;
    updateParameters.updatableInfo = "note";
    updateParameters.newValue = "go home";

    //the only way to input date
    //todo: может добавить еще вариации формата даты
    insertParameters.deadline = "23.03.2024"; 

    // databaseManager.addTask(insertParameters.id, insertParameters.deadline);
    databaseManager.updateTask(updateParameters.id, updateParameters.updatableInfo, updateParameters.newValue);

    databaseManager.stopConnection();

    return 0;
}