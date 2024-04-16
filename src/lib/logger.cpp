#include <QObject>
#include <QDir>
#include <QJsonArray>
#include <QJsonObject>
#include <QQmlContext>
#include <QCommandLineParser>
#include <QStandardPaths>

void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    QString logMessage;
    switch (type) {
    case QtDebugMsg:
        logMessage = "[D] ";
        break;
    case QtInfoMsg:
        logMessage = "[I] ";
        break;
    case QtWarningMsg:
        logMessage = "[W] ";
        break;
    case QtCriticalMsg:
        logMessage = "[C] ";
        break;
    default:
        logMessage = "[U] ";
        break;
    }

    auto fn = QString(context.file);
    auto fnspl = fn.split("/");
    logMessage += QString("[%1:%2] %3").arg(fnspl.last()).arg(context.line).arg(msg);

    // Output the log message to the console or a file
    QTextStream stream(stdout);
    stream << logMessage << "\n";

    // You can also write the log to a file
    // QFile outFile("log.txt");
    // if (outFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
    //     QTextStream fileStream(&outFile);
    //     fileStream << logMessage << endl;
    // }
}