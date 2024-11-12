#include "databaseConnection.h"
#include <libpq-fe.h>
#include <cstdlib>
#include <iostream>

DatabaseConnection::DatabaseConnection()
    : conn(nullptr) {
    connectionInfo = getConnectionInfo();
}

// Method to get or establish a connection to the database
PGconn* DatabaseConnection::getConnection() {
    if (!conn) {
        conn = PQconnectdb(connectionInfo.c_str());
        if (PQstatus(conn) != CONNECTION_OK) {
            std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
            PQfinish(conn);
            conn = nullptr;
        }
    }
    return conn;
}

// Destructor to close the connection
DatabaseConnection::~DatabaseConnection() {
    if (conn) {
        PQfinish(conn);
    }
}

// Helper function to get connection info from environment variables
std::string DatabaseConnection::getConnectionInfo() {
    char* user = nullptr;
    char* password = nullptr;
    char* host = nullptr;
    char* port = nullptr;
    size_t len;

    _dupenv_s(&user, &len, "postgre_user");
    _dupenv_s(&password, &len, "postgre_password");
    _dupenv_s(&host, &len, "postgre_host");
    _dupenv_s(&port, &len, "postgre_port");

    if (!user || !password || !host || !port) {
        throw std::runtime_error("Error: One or more environment variables are missing.");
    }

    std::string connectionInfo = "dbname=patient user=" + std::string(user) +
        " password=" + std::string(password) +
        " hostaddr=" + std::string(host) +
        " port=" + std::string(port);

    free(user);
    free(password);
    free(host);
    free(port);

    return connectionInfo;
}

void DatabaseConnection::insertPatientData(PGconn* conn, const std::string& name, const std::string& gender, const std::string& ageGroup,
    const std::string& exactAge, int heartRate, int bloodPressure1, int bloodPressure2, double temperature)
{
    // Construct SQL query with parameter placeholders
    std::string sql = "INSERT INTO patient_health_data (name, gender, ageGroup, exactAge, heartRate, bloodPressure1, bloodPressure2, temperature) "
        "VALUES ($1, $2, $3, $4, $5, $6, $7, $8);";

    // Prepare strings for the numerical values
    std::string heartRateStr = std::to_string(heartRate);
    std::string bloodPressure1Str = std::to_string(bloodPressure1);
    std::string bloodPressure2Str = std::to_string(bloodPressure2);
    std::string temperatureStr = std::to_string(temperature);

    const char* paramValues[8];
    paramValues[0] = name.c_str();
    paramValues[1] = gender.c_str();
    paramValues[2] = ageGroup.c_str();
    paramValues[3] = exactAge.c_str();
    paramValues[4] = heartRateStr.c_str();
    paramValues[5] = bloodPressure1Str.c_str();
    paramValues[6] = bloodPressure2Str.c_str();
    paramValues[7] = temperatureStr.c_str();

    PGresult* res = PQexecParams(conn, sql.c_str(), 8, nullptr, paramValues, nullptr, nullptr, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Insert failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        return;
    }

    PQclear(res);
    std::cout << "Data inserted successfully!" << std::endl;
}

void DatabaseConnection::retrievePatientId(PGconn* conn, int& id, std::string name)
{
    // Prepare the SQL query with the given name
    std::string query = "SELECT id FROM patient_health_data WHERE name = '" + name + "';";

    // Execute the query
    PGresult* res = PQexec(conn, query.c_str());

    // Check if the query executed successfully
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Query failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        return;
    }

    // Check if we got any results
    int numRows = PQntuples(res);
    if (numRows == 0) {
        std::cerr << "No patient found with ID " << id << std::endl;
        PQclear(res);
        return;
    }

    // Retrieve the data and assign it to the function's parameters
    id = std::stoi(PQgetvalue(res, 0, 0));

    // Clear the result to free memory
    PQclear(res);
}

void DatabaseConnection::retrievePatientData(PGconn* conn, int id, std::string& name, std::string& gender, std::string& ageGroup,
    std::string& exactAge, int& heartRate, int& bloodPressure1, int& bloodPressure2, double& temperature)
{
    // Use parameter binding instead of string concatenation
    std::string query = "SELECT name, gender, ageGroup, exactAge, heartRate, bloodPressure1, bloodPressure2, temperature "
        "FROM patient_health_data WHERE id = $1;";

    // Convert id to string for parameter
    std::string idStr = std::to_string(id);
    const char* paramValues[1] = { idStr.c_str() };

    // Execute the query with parameter
    PGresult* res = PQexecParams(conn, query.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);

    // Check if the query executed successfully
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Query failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        return;
    }

    // Check if we got any results
    int numRows = PQntuples(res);
    if (numRows == 0) {
        std::cerr << "No patient found with ID " << id << std::endl;
        PQclear(res);
        return;
    }

    // Fix the column indices (they start from 0)
    name = std::string(PQgetvalue(res, 0, 0));         // Changed from 1 to 0
    gender = std::string(PQgetvalue(res, 0, 1));       // Changed from 2 to 1
    ageGroup = std::string(PQgetvalue(res, 0, 2));     // Changed from 3 to 2
    exactAge = std::string(PQgetvalue(res, 0, 3));     // Changed from 4 to 3
    heartRate = std::stoi(PQgetvalue(res, 0, 4));      // Changed from 5 to 4
    bloodPressure1 = std::stoi(PQgetvalue(res, 0, 5)); // Changed from 6 to 5
    bloodPressure2 = std::stoi(PQgetvalue(res, 0, 6)); // Changed from 7 to 6
    temperature = round(std::stof(PQgetvalue(res, 0, 7)) * 10) / 10; // Changed from 8 to 7

    PQclear(res);
}