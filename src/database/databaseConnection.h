#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <libpq-fe.h>
#include <string>

class DatabaseConnection {
    public:
        DatabaseConnection();
        ~DatabaseConnection();
        PGconn* getConnection();

        void insertPatientData(PGconn* conn, const std::string& name, const std::string& gender, const std::string& ageGroup,
            const std::string& exactAge, int heartRate, int bloodPressure1, int bloodPressure2, double temperature);

        void retrievePatientId(PGconn* conn, int& id, std::string name);

        void retrievePatientData(PGconn* conn, int id, std::string& name, std::string& gender, std::string& ageGroup,
            std::string& exactAge, int& heartRate, int& bloodPressure1, int& bloodPressure2, double& temperature);

    private:
        PGconn* conn;
        std::string connectionInfo;
        std::string getConnectionInfo();
};

#endif // DATABASE_CONNECTION_H
