#include <QCoreApplication>
#include <QDebug>

#include "config.h"


// Temp Config File
enum class TempConfigEnum
{
    Param1,
    Param2
};

using TempConfig = Config<TempConfigEnum>;
template<>
QSettings TempConfig::settings { "tempConfig.ini", QSettings::IniFormat };

template<>
const QMap<TempConfigEnum, QString> TempConfig::keyToString {
    { TempConfigEnum::Param1, "tempParam1" },
    { TempConfigEnum::Param2, "tempParam2" }
};

// Main Config File

enum class MainConfigEnum
{
    ConfigParam1,
    ConfigParam2
};

using MainConfig = Config<MainConfigEnum>;
template<>
QSettings MainConfig::settings { "mainConfig.ini", QSettings::IniFormat };

template<>
const QMap<MainConfigEnum, QString> MainConfig::keyToString {
    { MainConfigEnum::ConfigParam1, "mainParam/Param1" },
    { MainConfigEnum::ConfigParam2, "mainParam/Param2" }
};

// Usage examples
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const auto i = 2;
    const QString str = "Value";

    // Example for Temp Config File
    if(TempConfig::status() != QSettings::NoError)
    {
        qDebug() << "Config file isn't valid.";
        return 1;
    }
    TempConfig::writeValue(TempConfigEnum::Param1, i);
    TempConfig::writeValue(TempConfigEnum::Param2, str);

    qInfo() << TempConfig::readValue<int>(TempConfigEnum::Param1);      // 1
    qInfo() << TempConfig::readValue<QString>(TempConfigEnum::Param2);  // "Value"

    // Example for Main Config File
    if(MainConfig::status() != QSettings::NoError)
    {
        qDebug() << "Config file isn't valid.";
        return 1;
    }
    MainConfig::writeValue(MainConfigEnum::ConfigParam1, i);
    MainConfig::writeValue(MainConfigEnum::ConfigParam2, str);

    qInfo() << MainConfig::readValue<int>(MainConfigEnum::ConfigParam1);    // 1
    qInfo() << MainConfig::readValue<QString>(MainConfigEnum::ConfigParam2);// "Value"

    return a.exec();
}
