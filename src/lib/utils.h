#pragma once

#include <QObject>
#include <QProcess>
#include <QFileInfo>
#include <QSettings>
#include <QRegularExpression>
#include <QStandardItemModel>
#include <QTextCharFormat>

struct PngInfo
{
    unsigned short channels;
    unsigned short height;
    unsigned short width;
    bool success;
};

class Utils
{

public:
  static bool readJsonFile(QIODevice &device, QSettings::SettingsMap &map);
  static bool writeJsonFile(QIODevice &device, const QSettings::SettingsMap &map);
  static bool fileExists(const QString &path);
  static QByteArray fileOpen(const QString &path);
  static QByteArray fileOpenQRC(const QString &path);
  static bool fileWrite(const QString &path, const QString &data);
  static QStringList fileFind(const QRegularExpression &pattern, const QString &baseDir, int level, int depth, int maxPerDir);
  static bool isCyrillic(const QString &inp);
  static bool dirExists(const QString &path);
  static PngInfo pngInfo(const QFileInfo &path);
};
