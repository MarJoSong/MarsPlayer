#ifndef MAINAPP_H
#define MAINAPP_H

#include <QApplication>
#include <QJSEngine>
#include <QPointer>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QTranslator>

class MainApp : public QApplication {
  Q_OBJECT
  Q_PROPERTY(int demoNum READ demoNum WRITE setDemoNum NOTIFY demoNumChanged)

 public:
  static QObject* GetInstance(QQmlEngine* engine, QJSEngine* scriptEngine);

 public:
  MainApp(int& argc, char** argv);
  ~MainApp() = default;

  int Main(int argc, char* argv[]);

 public:
  // For QML invokable function(s)
  Q_INVOKABLE void testFunc();

  int demoNum() const;
  void setDemoNum(int newValue);

 signals:
  void demoNumChanged(int newValue);

 public slots:

 private slots:

 private:
  bool Initialize();
  bool Uninitialize();

  bool InitializePath();
  bool UninitializePath();

  bool InitializeCfg();
  bool UninitializeCfg();

  bool InitializeTranslator();
  bool UninitializeTranslator();

  bool InitializeQmlEngine();
  bool UninitializeQmlEngine();

  bool InitializeUI(QQmlApplicationEngine* pQmlEngine);
  bool UninitializeUI(QQmlApplicationEngine* pQmlEngine);

  bool InitializeOthers();
  bool UninitializeOthers();

 private:
  QString m_AppRootPath;
  QString m_ImageRootPath;

  QScopedPointer<QTranslator> m_pTranslator;
  QScopedPointer<QQmlApplicationEngine> m_pQmlEngine;

  int m_demoNum{0};
};

MainApp* GetMainApp();

#endif  // MAINAPP_H
