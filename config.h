#ifndef CONFIG_H
#define CONFIG_H

#include <QMap>
#include <QSettings>

#ifdef CONFIG_DEBUG_PRINT
#include <QDebug>
#endif

template<typename EnumType>
class Config
{
public:
    Config() = delete;

    template<typename T>
    static T readValue(const EnumType &key, const T &defaultValue = T { })
    {
#ifdef CONFIG_DEBUG_PRINT
        qDebug() << QString("readValue(%1, %2) to file { %3 } with format { %4 }, status { %5 }")
                    .arg(static_cast<int>(key))
                    .arg(defaultValue)
                    .arg(settings.fileName())
                    .arg(settings.format())
                    .arg(settings.status());
#endif
        return qvariant_cast<T>(settings.value(keyToString[key], defaultValue));
    }

    template<typename T>
    static void writeValue(const EnumType &key, const T &value)
    {
#ifdef CONFIG_DEBUG_PRINT
        qDebug() << QString("writeValue(%1, %2) to file { %3 } with format { %4 }, status { %5 }")
                    .arg(static_cast<int>(key))
                    .arg(value)
                    .arg(settings.fileName())
                    .arg(settings.format())
                    .arg(settings.status());
#endif
        settings.setValue(keyToString[key], QVariant::fromValue(value));
        settings.sync();
    }

    static QSettings::Status status()
    {
        return settings.status();
    }

private:
    static QSettings settings;
    static const QMap<EnumType, QString> keyToString;

};


#endif // CONFIG_H
