#include "database.h"
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

Database::Database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("filmora_editor.db");
}

Database::~Database()
{
    if (db.isOpen()) {
        db.close();
    }
}

Database& Database::getInstance()
{
    static Database instance;
    return instance;
}

void Database::initializeDatabase()
{
    if (!db.open()) {
        qDebug() << "Error al abrir la base de datos:" << db.lastError().text();
        return;
    }
    
    createTables();
    qDebug() << "Base de datos inicializada";
}

void Database::createTables()
{
    QSqlQuery query;
    
    // Tabla de proyectos
    query.exec("CREATE TABLE IF NOT EXISTS projects ("
               "id INTEGER PRIMARY KEY,"
               "name TEXT UNIQUE,"
               "data TEXT,"
               "created_date DATETIME,"
               "modified_date DATETIME"
               ")");
    
    // Tabla de clips
    query.exec("CREATE TABLE IF NOT EXISTS clips ("
               "id INTEGER PRIMARY KEY,"
               "project_id INTEGER,"
               "filename TEXT,"
               "duration INTEGER,"
               "start_time INTEGER,"
               "FOREIGN KEY(project_id) REFERENCES projects(id)"
               ")");
    
    // Tabla de efectos
    query.exec("CREATE TABLE IF NOT EXISTS effects ("
               "id INTEGER PRIMARY KEY,"
               "project_id INTEGER,"
               "effect_name TEXT,"
               "intensity REAL,"
               "FOREIGN KEY(project_id) REFERENCES projects(id)"
               ")");
    
    // Tabla de suscripciones
    query.exec("CREATE TABLE IF NOT EXISTS subscriptions ("
               "id INTEGER PRIMARY KEY,"
               "user_id TEXT UNIQUE,"
               "active BOOLEAN,"
               "expiry_date DATE"
               ")");
    
    qDebug() << "Tablas creadas exitosamente";
}

bool Database::saveProject(const QString &projectName, const QString &projectData)
{
    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO projects (name, data, modified_date) "
                  "VALUES (:name, :data, :date)");
    query.addBindValue(projectName);
    query.addBindValue(projectData);
    query.addBindValue(QDateTime::currentDateTime());
    
    if (!query.exec()) {
        qDebug() << "Error al guardar proyecto:" << query.lastError().text();
        return false;
    }
    
    return true;
}

QString Database::loadProject(const QString &projectName)
{
    QSqlQuery query;
    query.prepare("SELECT data FROM projects WHERE name = :name");
    query.addBindValue(projectName);
    
    if (!query.exec()) {
        qDebug() << "Error al cargar proyecto:" << query.lastError().text();
        return "";
    }
    
    if (query.next()) {
        return query.value(0).toString();
    }
    
    return "";
}

bool Database::deleteProject(const QString &projectName)
{
    QSqlQuery query;
    query.prepare("DELETE FROM projects WHERE name = :name");
    query.addBindValue(projectName);
    
    if (!query.exec()) {
        qDebug() << "Error al eliminar proyecto:" << query.lastError().text();
        return false;
    }
    
    return true;
}
