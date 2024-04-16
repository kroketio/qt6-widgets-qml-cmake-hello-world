#pragma once

#include <QObject>
#include <QMainWindow>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include <QQueue>
#include <QThread>
#include <QMutex>
#include <QDir>

#include "lib/config.h"


class AppContext : public QObject {
Q_OBJECT

public:
  explicit AppContext();
  ~AppContext() override;

  bool isDebug;
  QString preloadModel;
  QString configDirectory;
  QString cacheDirectory;

  QString configRoot;
  QString homeDir;

signals:
  void windowTitle(QString title);

private:
  static void createConfigDirectory(const QString &dir);
};
