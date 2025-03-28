#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(AppContext *ctx, QWidget *parent) :
    QMainWindow(parent),
    m_ctx(ctx),
    ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  this->screenDpiRef = 128;
  this->screenGeo = QApplication::primaryScreen()->availableGeometry();
  this->screenRect = QGuiApplication::primaryScreen()->geometry();
  this->screenDpi = QGuiApplication::primaryScreen()->logicalDotsPerInch();
  this->screenDpiPhysical = QGuiApplication::primaryScreen()->physicalDotsPerInch();
  this->screenRatio = this->screenDpiPhysical / this->screenDpiRef;
  qDebug() << QString("%1x%2 (%3 DPI)").arg(
      this->screenRect.width()).arg(this->screenRect.height()).arg(this->screenDpi);

  this->createQml();
  this->show();

  // example get config value:
  auto test = config()->get(ConfigKeys::Test).toString();
  qDebug() << "config value: " << test;

  // example set config value
  // config()->set(ConfigKeys::Test, "test2");

  // example QWidget button handler
  connect(ui->pushButton, &QPushButton::clicked, [=] {
    qDebug() << "pushButton clicked";
  });
}

void MainWindow::closeEvent(QCloseEvent *event) {
  //event->ignore();
  QApplication::quit();
}

void MainWindow::createQml() {
  if(m_quickWidget != nullptr) return;
  m_quickWidget = new QQuickWidget(this);

  auto *qctx = m_quickWidget->rootContext();
  qctx->setContextProperty("cfg", config());
  qctx->setContextProperty("ctx", m_ctx);

  qctx->setContextProperty("mainwindow", this);

  m_quickWidget->setSource(QUrl(QStringLiteral("qrc:/qml/main.qml")));
  m_quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

  ui->qml->layout()->addWidget(m_quickWidget);
}

void MainWindow::onExample(int status) {
  qDebug() << "example() called from QML";
}

void MainWindow::onWindowTitle(const QString &title) {
  this->setWindowTitle(title);
}

void MainWindow::destroyQml() {
  if(m_quickWidget == nullptr) return;
  m_quickWidget->disconnect();
  m_quickWidget->deleteLater();
  m_quickWidget = nullptr;
}

MainWindow::~MainWindow() {
  delete ui;
}

