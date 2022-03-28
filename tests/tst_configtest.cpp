#include <QtTest>

#include "../config.h"
using adzunyan69::Config;

// Init static members

// Temp Config File
enum class TempConfigEnum
{
    Param1,
    Param2
};

using TempConfig = Config<TempConfigEnum>;

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

using TempConfig = Config<TempConfigEnum>;
template<>
QSettings TempConfig::settings { "tempConfig.ini", QSettings::IniFormat };


class ConfigTest : public QObject
{
    Q_OBJECT

public:
    ConfigTest();
    ~ConfigTest();

private slots:
    void testTempInitConfig();
    void testMainInitEmptyConfig();
    void testSetGetLvalue();
    void testSetGetRvalue();
    void testClearConfigFile();

};

ConfigTest::ConfigTest()
{
    qSetMessagePattern("[%{time hh:mm:ss.zzz}] [%{file} %{function} line %{line}] [%{type}]: %{message}");

}

ConfigTest::~ConfigTest()
{

}

void ConfigTest::testTempInitConfig()
{
    TempConfig::initConfig(
    {
                    {TempConfigEnum::Param1, 5},
                    {TempConfigEnum::Param2, "Value5"}
                });

    QCOMPARE(TempConfig::status(), QSettings::NoError);
    QCOMPARE(TempConfig::value<int>(TempConfigEnum::Param1), 5);
    QCOMPARE(TempConfig::value<QString>(TempConfigEnum::Param2), "Value5");
}

void ConfigTest::testMainInitEmptyConfig()
{
    MainConfig::initEmptyValuesConfig(); // empty config

    QCOMPARE(MainConfig::status(), QSettings::NoError);
    QCOMPARE(MainConfig::value<int>(MainConfigEnum::ConfigParam1),
             int{});
    QCOMPARE(MainConfig::value<QString>(MainConfigEnum::ConfigParam2),
             QString{});
}

void ConfigTest::testSetGetLvalue()
{
    const auto i { 1 };
    const QString str { "Value" };

    TempConfig::setValue(TempConfigEnum::Param1, i); // int const&
    TempConfig::setValue(TempConfigEnum::Param2, str); // QString &

    QCOMPARE(TempConfig::status(), QSettings::NoError);
    QCOMPARE(TempConfig::value<std::remove_cv_t<decltype (i)>>(TempConfigEnum::Param1), i);      // 1
    QCOMPARE(TempConfig::value<std::remove_cv_t<decltype (str)>>(TempConfigEnum::Param2), str);
}

void ConfigTest::testSetGetRvalue()
{
#define INT_VAL 2
    QString str { "RValue" };
    QString copyStr { str };
    MainConfig::setValue(MainConfigEnum::ConfigParam1, INT_VAL); // int&&
    MainConfig::setValue(MainConfigEnum::ConfigParam2, std::move(str)); // QString&&

    QCOMPARE(MainConfig::status(), QSettings::NoError);
    QCOMPARE(MainConfig::value<decltype (INT_VAL)>(MainConfigEnum::ConfigParam1),
             INT_VAL);      // 1
    QCOMPARE(MainConfig::value<decltype (str)>(MainConfigEnum::ConfigParam2),
             copyStr);

#undef i
}

void ConfigTest::testClearConfigFile()
{
    MainConfig::clear();

    QCOMPARE(MainConfig::status(), QSettings::NoError);
    QCOMPARE(MainConfig::value<decltype (std::numeric_limits<int>::min())>(MainConfigEnum::ConfigParam1,
                                                                           std::numeric_limits<int>::min()),
             std::numeric_limits<int>::min());
}

QTEST_APPLESS_MAIN(ConfigTest)

#include "tst_configtest.moc"
