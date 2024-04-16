#pragma once

#include <iostream>

#include <QMainWindow>
#include <QCompleter>
#include <QQmlEngine>
#include <QCheckBox>
#include <QPushButton>
#include <QClipboard>
#include <QStringListModel>
#include <QTimer>
#include <QQuickWidget>
#include <QQuickView>
#include <QQmlContext>
#include <QDebug>
#include <QQueue>
#include <QThread>
#include <QMutex>
#include <QFileDialog>

#include "ctx.h"
#include "lib/utils.h"

namespace Ui {
  class MainWindow;
}

class AppContext;
class MainWindow : public QMainWindow
{
Q_OBJECT
Q_PROPERTY(int example_property MEMBER m_example_property NOTIFY example_propertyChanged);

public:
  explicit MainWindow(AppContext *ctx, QWidget *parent = nullptr);
  ~MainWindow() override;

  qreal screenDpiRef;
  QRect screenGeo;
  QRect screenRect;
  qreal screenDpi;
  qreal screenDpiPhysical;
  qreal screenRatio;

signals:
  void example_propertyChanged();

public slots:
  void onWindowTitle(const QString &title);
  void onExample(int status);

protected:
  void closeEvent(QCloseEvent *event) override;

private:
  Ui::MainWindow *ui;
  AppContext *m_ctx = nullptr;
  QQuickWidget *m_quickWidget = nullptr;

  unsigned int m_example_property = 320;

  void createQml();
  void destroyQml();
};
