#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>

class Database
{
public:
    static Database& getInstance();
    
    void initializeDatabase();
    bool saveProject(const QString &projectName, const QString &projectData);
    QString loadProject(const QString &projectName);
    bool deleteProject(const QString &projectName);
    
private:
    Database();
    ~Database();
    
    QSqlDatabase db;
    
    void createTables();
};

#endif // DATABASE_H
