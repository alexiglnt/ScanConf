#include "SystemInfo.h"

// Implementation of executeCommand
QString SystemInfo::executeCommand(const QString &command) {
    QProcess process;
    process.start("powershell.exe", QStringList() << "-NoProfile" << "-Command" << command);
    process.waitForFinished(-1); // Wait indefinitely until the process finishes
    QString output = process.readAllStandardOutput().trimmed();
    return output;
}


// Implementation of getCpuNameWindows
QString SystemInfo::getCpuNameWindows() {
    QString result = executeCommand("wmic cpu get name");
    auto lines = result.split("\r\n", Qt::SkipEmptyParts); // Adjusting for Windows line endings
    for (const QString& line : lines) {
        if (!line.trimmed().isEmpty() && !line.contains("Name")) {
            return line.trimmed();
        }
    }
    return "Unknown CPU";
}

// Implementation of extractCpuModel
QString SystemInfo::extractCpuModel(const QString& fullCpuName) {
    // Regular expression to find the CPU model pattern
    QRegularExpression cpuModelRegex(
        "(i[3579]-\\d{4,5}[A-Z]?)|(Ryzen \\d+ \\d{4}X?)|(Xeon(R)?( Gold)? [\\w-]+\\s?(v\\d+)?)|"
        "(Pentium(R)? CPU [\\w-]+)|(Celeron(R)? CPU [\\w-]+)|(Athlon [\\w-]+)|(EPYC \\d{4}[A-Z]?)",
        QRegularExpression::CaseInsensitiveOption // Case-insensitive matching
        );

    QRegularExpressionMatch match = cpuModelRegex.match(fullCpuName);
    if (match.hasMatch()) {
        // Return the first match which should be the CPU model
        return match.captured(0);
    }

    return "Unknown Model"; // Return a default value if no match is found
}

// Implementation of getCpuName
QString SystemInfo::getCpuName() {
    #ifdef Q_OS_WIN
        return extractCpuModel(getCpuNameWindows());
    #elif defined(Q_OS_LINUX)
        return getCpuNameLinux();
    #elif defined(Q_OS_MAC)
        return getCpuNameMac();
    #else
        return "Unknown OS";
    #endif
}


QString SystemInfo::getRamInfo() {
    #ifdef Q_OS_WIN
            return getRamInfoWindows();
    #elif defined(Q_OS_LINUX)
            return getRamInfoLinux(); // Implement this method for Linux
    #elif defined(Q_OS_MAC)
            return getRamInfoMac(); // Implement this method for macOS
    #else
            return "Unknown OS";
    #endif
}

QString SystemInfo::getDiskInfo() {
#ifdef Q_OS_WIN
            return getDiskInfoWindows();
#elif defined(Q_OS_LINUX)
            return getDiskInfoLinux(); // Implement this method for Linux
#elif defined(Q_OS_MAC)
            return getDiskInfoMac(); // Implement this method for macOS
#else
            return "Unknown OS";
#endif
}


QString SystemInfo::getRamInfoWindows() {
        QString ramInfo;
        qint64 totalCapacityBytes = 0;

        // Use PowerShell to get detailed physical memory information
        QString command = "powershell \"Get-CimInstance Win32_PhysicalMemory | Select-Object -Property Capacity, Manufacturer | Format-List\"";
        QString output = executeCommand(command);
        qDebug() << "RAM Command Output:" << output;

        // Split the output by the property names
        QStringList memoryModules = output.split("\r\n\r\n", Qt::SkipEmptyParts);
        for (const QString &moduleData : memoryModules) {
    QStringList lines = moduleData.split("\r\n", Qt::SkipEmptyParts);
    QMap<QString, QString> properties;
    for (const QString &line : lines) {
        QStringList keyValue = line.split(":", Qt::SkipEmptyParts);
        if (keyValue.size() == 2) {
            properties[keyValue[0].trimmed()] = keyValue[1].trimmed();
        }
    }

    // Convert Capacity from bytes to GB
    bool ok;
    qint64 capacityBytes = properties["Capacity"].toLongLong(&ok);
    if (ok) {
        totalCapacityBytes += capacityBytes;
        double capacityGB = capacityBytes / (1024.0 * 1024.0 * 1024.0);
        ramInfo.append(QString("RAM Stick: %1 GB, Manufacturer: %2\n")
                           .arg(QString::number(capacityGB, 'f', 2))
                           .arg(properties["Manufacturer"]));
    }
        }

        // Calculate and append the total RAM in GB
        if (totalCapacityBytes > 0) {
    double totalCapacityGB = totalCapacityBytes / (1024.0 * 1024.0 * 1024.0);
    ramInfo.prepend(QString("Total RAM: %1 GB\n").arg(totalCapacityGB, 0, 'f', 2));
        } else {
    ramInfo.prepend(QString("Total RAM: Unavailable\n"));
        }

        return ramInfo;
}



QString SystemInfo::getDiskInfoWindows() {
    QString diskInfo;

    // Use PowerShell to get the physical disk information
    QString command = "powershell \"Get-PhysicalDisk | Select-Object -Property DeviceId, MediaType, Size | Format-Table -AutoSize | Out-String -Width 4096\"";
    QString output = executeCommand(command);
    QStringList lines = output.split("\n", Qt::SkipEmptyParts);

    // Define regular expressions for parsing
    QRegularExpression headerRegex("^DeviceId\\s+MediaType\\s+Size", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression lineRegex("^(\\d+)\\s+(HDD|SSD)\\s+(\\d+)", QRegularExpression::CaseInsensitiveOption);

    bool headerFound = false;
    for (const QString &line : lines) {
        if (headerRegex.match(line).hasMatch()) {
            headerFound = true;
            continue; // Skip the header line
        }
        if (!headerFound || line.trimmed().isEmpty()) {
            continue; // Skip lines until header is found and ignore empty lines
        }

        QRegularExpressionMatch match = lineRegex.match(line);
        if (match.hasMatch()) {
            QString deviceId = match.captured(1);
            QString mediaType = match.captured(2);
            qint64 sizeBytes = match.captured(3).toLongLong();
            double sizeGB = sizeBytes / (1024.0 * 1024.0 * 1024.0);

            diskInfo += QString("Disk %1: Type: %2, Size: %3 GB\n")
                            .arg(deviceId)
                            .arg(mediaType)
                            .arg(QString::number(sizeGB, 'f', 2));
        }
    }

    return diskInfo;
}

QJsonObject SystemInfo::createSystemInfoJson(SystemInfo& sysInfo) {
    QJsonObject systemInfo;

    // Model information
    QJsonObject model;
    model["type"] = "rack"; // Assume a rack type for this example
    systemInfo["model"] = model;

    // Configuration information
    QJsonObject configuration;

    // CPU information
    QJsonObject cpu;
    QString cpuName = sysInfo.getCpuName();
    cpu["units"] = 1; // Assuming 1 CPU unit for simplicity
    cpu["name"] = cpuName;
    configuration["cpu"] = cpu;

    // RAM information
    QString ramInfo = sysInfo.getRamInfo();
    // You need to parse diskInfo string and fill this array
    QJsonArray ramArray = parseRamInfo(ramInfo);
    configuration["ram"] = ramArray;

    // Disk information
    QString diskInfo = sysInfo.getDiskInfo();
    // You need to parse diskInfo string and fill this array
    QJsonArray diskArray = parseDiskInfo(diskInfo);
    configuration["disk"] = diskArray;

    systemInfo["configuration"] = configuration;

    // Usage information - assuming dummy data for the example
    QJsonObject usage;
    usage["avg_power"] = 300; // Assume average power usage
    usage["usage_location"] = "FRA"; // Assume location is Frankfurt
    systemInfo["usage"] = usage;

    return systemInfo;
}

QJsonArray SystemInfo::parseRamInfo(const QString& ramInfo) {
    QJsonArray ramArray;
    QStringList ramLines = ramInfo.split("\n", Qt::SkipEmptyParts);
    for (const QString& line : ramLines) {
        QJsonObject ramDetail;
        QRegularExpression regex("RAM Stick: (\\d+\\.\\d+) GB, Manufacturer: (.+)");
        QRegularExpressionMatch match = regex.match(line);
        if (match.hasMatch()) {
            double capacityGB = match.captured(1).toDouble();
            QString manufacturer = match.captured(2);
            ramDetail["units"] = 1; // Each line represents one RAM stick
            ramDetail["capacity"] = capacityGB;
            ramDetail["manufacturer"] = manufacturer;
            ramArray.append(ramDetail);
        }
    }
    return ramArray;
}


QJsonArray SystemInfo::parseDiskInfo(const QString& diskInfo) {
    QJsonArray diskArray;
    QStringList lines = diskInfo.split("\n", Qt::SkipEmptyParts);
    QRegularExpression regex("Disk (\\d+): Type: (SSD|HDD), Size: (\\d+\\.\\d+) GB");
    for (const QString& line : lines) {
        QRegularExpressionMatch match = regex.match(line);
        if (match.hasMatch()) {
            int diskNumber = match.captured(1).toInt();
            QString diskType = match.captured(2);
            double diskSize = match.captured(3).toDouble();

            QJsonObject diskObject;
            diskObject["units"] = 1; // Assuming 1 unit per disk
            diskObject["type"] = diskType;
            diskObject["capacity"] = diskSize;
            // Disk number can be used if needed, but it's not included in the JSON object
            // as it's not present in the example structure you've provided.

            diskArray.append(diskObject);
        }
    }

    return diskArray;
}
