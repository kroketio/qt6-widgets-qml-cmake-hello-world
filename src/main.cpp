#include <QApplication>
#include <QResource>
#include <QtCore>
#include <QSslSocket>

#if defined(Q_OS_WIN)
#include <windows.h>
#endif

#include <unistd.h>
#include <sys/types.h>
#include "mainwindow.h"
#include "lib/logger.h"
#include "ctx.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick3D/qquick3d.h>

int main(int argc, char *argv[]) {
  qDebug() << "qt" << qVersion();
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication::setApplicationName("hello");
  QApplication::setOrganizationDomain("kroket.io");
  QApplication::setOrganizationName("Kroket Ltd.");
  QApplication app(argc, argv);
  qInstallMessageHandler(customMessageHandler);

  qDebug() << "SSL version: " << QSslSocket::sslLibraryVersionString();
  qDebug() << "SSL build: " << QSslSocket::sslLibraryBuildVersionString();

  auto *ctx = new AppContext();
  ctx->isDebug = false;
  auto *mainWindow = new MainWindow(ctx);

  return QApplication::exec();
}
