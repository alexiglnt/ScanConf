#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QString>
#include <QProcess>
#include <QRegularExpression>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class SystemInfo {
public:
    QString getCpuName();
    QString getRamInfo();
    QString getDiskInfo();
    QJsonObject createSystemInfoJson(SystemInfo& sysInfo);

private:
    QString getCpuNameWindows();
    QString extractCpuModel(const QString& fullCpuName);
    // QString getCpuNameLinux();
    // QString getCpuNameMac();

    QString getRamInfoWindows(); // Implementations for Windows
    // QString getRamInfoLinux(); // Future implementation for Linux
    // QString getRamInfoMac(); // Future implementation for macOS

    QString getDiskInfoWindows(); // Implementations for Windows
    // QString getDiskInfoLinux(); // Future implementation for Linux
    // QString getDiskInfoMac(); // Future implementation for macOS


    QJsonArray parseDiskInfo(const QString& diskInfo);
    QJsonArray parseRamInfo(const QString& diskInfo);

    QString executeCommand(const QString &command);

};

#endif // SYSTEMINFO_H
