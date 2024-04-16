#include <QScreen>
#include <QMessageBox>
#include <QJsonDocument>
#include <QClipboard>

#include "png.h"

#include "utils.h"
#include "lib/config.h"

bool Utils::readJsonFile(QIODevice &device, QSettings::SettingsMap &map) {
  QJsonDocument json = QJsonDocument::fromJson(device.readAll());
  map = json.object().toVariantMap();
  return true;
}

bool Utils::writeJsonFile(QIODevice &device, const QSettings::SettingsMap &map) {
  device.write(QJsonDocument(QJsonObject::fromVariantMap(map)).toJson(QJsonDocument::Indented));
  return true;
}

bool Utils::fileExists(const QString &path) {
  QFileInfo check_file(path);
  return check_file.exists() && check_file.isFile();
}

bool Utils::dirExists(const QString &path) {
  QDir pathDir(path);
  return pathDir.exists();
}

QByteArray Utils::fileOpen(const QString &path) {
  QFile file(path);
  if(!file.open(QFile::ReadOnly | QFile::Text)) {
    return QByteArray();
  }

  QByteArray data = file.readAll();
  file.close();
  return data;
}

QByteArray Utils::fileOpenQRC(const QString &path) {
  QFile file(path);
  if(!file.open(QIODevice::ReadOnly)) {
    qDebug() << "error: " << file.errorString();
  }

  QByteArray data = file.readAll();
  file.close();
  return data;
}

bool Utils::fileWrite(const QString &path, const QString &data) {
    QFile file(path);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file); out << data << "\n";
        file.close();
        return true;
    }
    return false;
}

QStringList Utils::fileFind(const QRegularExpression &pattern, const QString &baseDir, int level, int depth, const int maxPerDir) {
    // like `find /foo -name -maxdepth 2 "*.jpg"`
    QStringList rtn;
    QDir dir(baseDir);
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);

    int fileCount = 0;
    for(const auto &fileInfo: dir.entryInfoList({"*"})) {
        fileCount += 1;
        if(fileCount > maxPerDir) return rtn;
        if(!fileInfo.isReadable())
            continue;

        const auto fn = fileInfo.fileName();
        const auto path = fileInfo.filePath();

        if (fileInfo.isDir()) {
            if (level + 1 <= depth)
                rtn << Utils::fileFind(pattern, path, level + 1, depth, maxPerDir);
        }
        else if (pattern.match(fn).hasMatch())
            rtn << path;
    }
    return rtn;
}

bool Utils::isCyrillic(const QString &inp) {
  QRegularExpression re("[А-Яа-яЁё]+");
  QRegularExpressionMatch match = re.match(inp);
  return match.hasMatch();
}

PngInfo Utils::pngInfo(const QFileInfo &path) {
  auto _path = path.absoluteFilePath();
  if(!Utils::fileExists(_path)) {
    qWarning() << "does not exist:" << path;
  }

  FILE *fp = fopen(_path.toStdString().c_str(), "rb");
  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if(!png) {
    qWarning() << "error reading png #1";
    return {};
  }

  png_infop info = png_create_info_struct(png);
  if(!info) {
    qWarning() << "error reading png #2";
    return {};
  }

  if(setjmp(png_jmpbuf(png))) {
    qWarning() << "error reading png #3";
    return {};
  }

  png_init_io(png, fp);
  png_read_info(png, info);

  auto png_info = PngInfo();
  png_info.channels = png_get_channels(png, info);
  png_info.width = png_get_image_width(png, info);
  png_info.height = png_get_image_height(png, info);
  png_info.success = true;
  png_destroy_read_struct(&png, &info, nullptr);
  return png_info;
}
