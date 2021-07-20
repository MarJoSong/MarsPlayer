#include "MainApp.h"

#include <QDebug>
#include <QDir>
#include <QFont>
#include <QIcon>
#include <QList>
#include <QString>
#include <QUrl>

#define APP_NAME "MarsPlayer"
#define APP_DISPLAYNAME "MarsPlayer"
#define APP_ICON_PATH "qrc:/image/AppIcon.ico"
#define UI_MAIN_PATH "qrc:/qml/main.qml"
#define UI_TRANSLATION_PATH ":/translation/MarsPlayer_zh_CN.qm" //不能加qrc,原因不详
#define IMAGEDIR_RELATIVE_PATH "./image"
#define DEFAULT_FONT_NAME "微软雅黑"

MainApp* g_pApp = nullptr;

MainApp* GetMainApp() { return g_pApp; }

QObject* MainApp::GetInstance(QQmlEngine* engine, QJSEngine* scriptEngine) {
  Q_UNUSED(engine);
  Q_UNUSED(scriptEngine);

  QObject* pObj = GetMainApp();
  QQmlEngine::setObjectOwnership(pObj, QQmlEngine::CppOwnership);
  return pObj;
}

MainApp::MainApp(int& argc, char** argv)
    : QApplication(argc, argv), m_AppRootPath(""), m_ImageRootPath("") {}

int MainApp::Main(int argc, char** /*argv*/) {
  Q_UNUSED(argc);

  if (!Initialize()) {
    Uninitialize();
    return EXIT_FAILURE;
  }

  int nRet = exec();

  Uninitialize();
  return nRet;
}

void MainApp::testFunc() {
  qDebug() << "MainApp::testFunc()";
  setDemoNum(demoNum() + 1);
}

int MainApp::demoNum() const { return m_demoNum; }

void MainApp::setDemoNum(int newValue) {
  if (m_demoNum != newValue) {
    m_demoNum = newValue;
    emit demoNumChanged(m_demoNum);
  }
}

// int MainApp::Main(int argc, char **argv) {
//;
//};

bool MainApp::Initialize() {
  setApplicationName(QStringLiteral(APP_NAME));
  setWindowIcon(QIcon(QStringLiteral(APP_ICON_PATH)));

  InitializePath();

  InitializeCfg();

  if (!InitializeTranslator()) {
    return false;
  }

  if (!InitializeQmlEngine()) {
    return false;
  }

  if (!InitializeUI(m_pQmlEngine.data())) {
    return false;
  }

  InitializeOthers();

  return true;
}

bool MainApp::Uninitialize() {
  UninitializeOthers();

  UninitializeUI(m_pQmlEngine.data());

  UninitializeQmlEngine();

  UninitializeTranslator();

  UninitializeCfg();

  UninitializePath();

  return true;
}

bool MainApp::InitializePath() {
  m_AppRootPath = qApp->applicationDirPath();
  QDir dirApp(m_AppRootPath);
  if (!dirApp.exists()) {
    return false;
  }

  m_ImageRootPath = m_AppRootPath;
  m_ImageRootPath.append(QStringLiteral("/"))
      .append(QStringLiteral(IMAGEDIR_RELATIVE_PATH));
  QDir dirImg(m_AppRootPath);
  if (!dirImg.exists()) {
    return false;
  }
  m_ImageRootPath = dirImg.canonicalPath();

  return true;
}

bool MainApp::UninitializePath() {
  m_ImageRootPath.clear();
  m_AppRootPath.clear();

  return true;
}

bool MainApp::InitializeCfg() { return true; }

bool MainApp::UninitializeCfg() { return true; }

bool MainApp::InitializeTranslator() {
  if (nullptr != m_pTranslator) {
    return true;
  }

  m_pTranslator.reset(new QTranslator);
  qDebug() << QStringLiteral(UI_TRANSLATION_PATH) << endl;
  if (!m_pTranslator->load(QStringLiteral(UI_TRANSLATION_PATH))) {
    return false;
  }

  installTranslator(m_pTranslator.data());
  return true;
}

bool MainApp::UninitializeTranslator() {
  if (nullptr == m_pTranslator) {
    return false;
  }

  removeTranslator(m_pTranslator.data());
  m_pTranslator.reset();

  return true;
}

bool MainApp::InitializeQmlEngine() {
  if (nullptr != m_pQmlEngine) {
    return true;
  }

  m_pQmlEngine.reset(new QQmlApplicationEngine);

  return (nullptr != m_pQmlEngine);
}

bool MainApp::UninitializeQmlEngine() {
  if (nullptr == m_pQmlEngine) {
    return true;
  }

  m_pQmlEngine.reset();

  return true;
}

bool MainApp::InitializeUI(QQmlApplicationEngine* pQmlEngine) {
  if (nullptr == pQmlEngine) {
    return false;
  }

  setFont(QFont(DEFAULT_FONT_NAME));

  qmlRegisterSingletonType<MainApp>("com.huahua.marsplayer", 1, 0, "MainApp",
                                    &MainApp::GetInstance);

  pQmlEngine->load(QUrl(QStringLiteral(UI_MAIN_PATH)));
  QList<QObject*> rootObjs(pQmlEngine->rootObjects());
  return !rootObjs.empty();
}

bool MainApp::UninitializeUI(QQmlApplicationEngine* pQmlEngine) {
  if (nullptr == pQmlEngine) {
    return true;
  }

  return true;
}

bool MainApp::InitializeOthers() { return true; }

bool MainApp::UninitializeOthers() { return true; }
