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
    insertParameters.task = "Smash house";
    insertParameters.deadline = "23.03.2024"; 

    // databaseManager.add(insertParameters.task, insertParameters.deadline);

    //update parameters
    InfoToUpdate updateParameters;
    updateParameters.id = 24;
    updateParameters.updatableInfo = "note";
    updateParameters.newValue = "go home";
    
    // databaseManager.update(updateParameters.id, updateParameters.updatableInfo, updateParameters.newValue);

    InfoToDelete deleteParameters;
    deleteParameters.id = 38;

    databaseManager.remove(deleteParameters.id);

    databaseManager.stopConnection();

    return 0;
}