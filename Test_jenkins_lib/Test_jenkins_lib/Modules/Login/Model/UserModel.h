#pragma once

#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QCryptographicHash>
#include <QDebug>
#include <QCoreApplication>

class UserModel {
public:
    UserModel();
    ~UserModel();

    bool validateUser(const QString& username, const QString& password);
    bool registerUser(const QString& username, const QString& password);
    bool userExists(const QString& username);

private:
    QString getUserFilePath() const;
    QString hashPassword(const QString& password) const;
}; 