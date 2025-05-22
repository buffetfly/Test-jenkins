#include "UserModel.h"

UserModel::UserModel() {
    // 确保user目录存在
    QDir dir(QCoreApplication::applicationDirPath() + "/user");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
}

UserModel::~UserModel() {
}

bool UserModel::validateUser(const QString& username, const QString& password) {
    QFile file(getUserFilePath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(":");
        if (parts.size() == 2 && parts[0] == username && parts[1] == hashPassword(password)) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool UserModel::registerUser(const QString& username, const QString& password) {
    if (userExists(username)) {
        return false;
    }

    QFile file(getUserFilePath());
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    out << username << ":" << hashPassword(password) << "\n";
    file.close();
    return true;
}

bool UserModel::userExists(const QString& username) {
    QFile file(getUserFilePath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(":");
        if (parts.size() == 2 && parts[0] == username) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

QString UserModel::getUserFilePath() const {
    return QCoreApplication::applicationDirPath() + "/user/userdata.txt";
}

QString UserModel::hashPassword(const QString& password) const {
    QByteArray passwordBytes = password.toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256).toHex();
    return QString(hashedPassword);
} 