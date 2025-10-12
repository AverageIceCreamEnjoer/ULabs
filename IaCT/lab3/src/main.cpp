#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "back/GilbertMooreCoder.hpp"

int main(int argc, char *argv[]) {
  // Создаем экземпляр приложения
  QGuiApplication app(argc, argv);

  // Регистрируем наш C++ тип для использования в QML
  // qmlRegisterType<ClassName>("URI", major_ver, minor_ver, "QmlName");
  qmlRegisterType<GilbertMooreCoder>("com.mycompany.coding", 1, 0,
                                     "GilbertMooreCoder");

  // Создаем движок QML
  QQmlApplicationEngine engine;

  // Указываем движку загрузить наш QML файл.
  // Путь "qrc:/" означает, что файл находится внутри ресурсов, скомпилированных
  // в программу.
  const QUrl url(u"qrc:/front/main.qml"_qs);

  // Обрабатываем событие, если объект не был создан, чтобы приложение не падало
  // молча
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);

  // Загружаем QML
  engine.load(url);

  // Запускаем главный цикл обработки событий приложения
  return app.exec();
}