#include <iostream>
#include <string>
#include "notes.h"
#include <cstdlib>
#include "libpq-fe.h"

int main() {
    const char* username = "tester";
    const char* password = "123";
    std::string request = "dbname=notes user=" + std::string(username) + " password=" + std::string(password) + " host=localhost";

    // Устанавливаем соединение
    PGconn *conn = PQconnectdb(request.c_str());

    //тестовый запрос
    const char* query = "INSERT INTO notes(note) VALUES ('kill yourself');";

    PGresult *result = PQexec(conn, query);

    if (PQresultStatus(result) == PGRES_COMMAND_OK) {
        std::cout << "Запрос выполнен успешно." << std::endl;

        // Здесь вы можете обрабатывать успешный результат запроса

        // Освобождаем ресурсы
        PQclear(result);
    } else {
        std::cerr << "Не удалось выполнить SQL-запрос: " << PQerrorMessage(conn) << std::endl;
    }

    // Закрываем соединение
    PQfinish(conn);

    return 0;
}