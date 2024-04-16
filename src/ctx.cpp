#include <filesystem>

#include <QObject>
#include <QDir>
#include <QStandardPaths>

#include "ctx.h"
#include "lib/utils.h"
//#include "lib/vmfpp/vmfpp.h"

using namespace std::chrono;


AppContext::AppContext() {
  configRoot = QDir::homePath();
  homeDir = QDir::homePath();
  configDirectory = QString("%1/.config/%2/").arg(configRoot, QCoreApplication::applicationName());
  cacheDirectory = QString("%1/cache").arg(configDirectory);
  config()->set(ConfigKeys::CacheDir, cacheDirectory);

  createConfigDirectory(configDirectory);
  createConfigDirectory(cacheDirectory);
}

void AppContext::createConfigDirectory(const QString &dir) {
  QStringList createDirs({dir});
  for(const auto &d: createDirs) {
    if(!std::filesystem::exists(d.toStdString())) {
      qDebug() << QString("Creating directory: %1").arg(d);
      if (!QDir().mkpath(d))
        throw std::runtime_error("Could not create directory " + d.toStdString());
    }
  }
}

AppContext::~AppContext() {}
