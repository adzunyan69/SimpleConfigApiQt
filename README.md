# Simple Config API

It's short class for interaction with config files using QSettings. 

User of the class have to implement own enum-type `EnumType` and `QMap<EnumType, QString>` with own list of config application parameters.

In the `main.cpp` shown usage example.

`Config` has three static member-functions for now:

- ```
  static T readValue(const EnumType &key, const T &defaultValue = T { })
  ```

where `T` - returned value type, `EnumType` - custom user-defined enum-type, `key` - value from enum-type, defaultValue - default value for type `T`.

- ```
  static void writeValue(const EnumType &key, const T &value)
  ```

where params are the same as above except `value`.

- ```
  static QSettings::Status status()
  ```

that returns status of QSettings object.