#include <QObject>
#include <QPushButton>
#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QList>
#include <QWidget>
#include <QTextEdit>
#include <QTextStream>
#include <QTimer>

#ifndef CLASSES_H
#define CLASSES_H

class DriverLibrary;
class Controller;
class SystemLibrary;
class Compiler;
class Queue;
class ProcessLoop;


class Error{

public:
  QVector<QString> getVector_string();
  int getInt();
  float getFloat();
  QString getString();
  Error();

private:
  QVector<QString> E_VECTOR_STRING = {"E", "R", "R", "O", "R"};
  int E_INT = -1000000;
  float E_FLOAT = 74.236;
  QString E_STRING = "dwavvxwčš§ů";

};

class Call{

public:
  Call();
  virtual void doCommand() = 0;

protected:
  QString command;
};

class DriverCall : public Call{

public:
  DriverCall(DriverLibrary * driverLib, QString com, int portNum);
  void doCommand();

private:
  DriverLibrary * driverLibrary;
  int portNumber;

};

class SystemCall : public Call{

public:
  SystemCall(SystemLibrary * sysLib, QString com);
  void doCommand();

private:
  SystemLibrary * systemLibrary;

};

class ErrorCall : public Call{

public:
  ErrorCall(Compiler * comp, QString message, QString com);
  void doCommand();

private:
  Compiler * compiler;
  QString errorMessage;

};

class Arguments{

public:
  void addArgument(QString arg);
  QString getArgument(int position);

private:
  QVector<QString> argsVector;

};

class Parser{

public:
  Parser(QString parser);
  QVector<QString> parse();
  QString getParser();
  int getPortNumber(QString rawCommand);
  QString getCommand(QString rawCommand);
  Arguments * getArguments(QString rawCommand);

private:
  QString rawParser;

};

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    int x, y, width, height;

    MainWindow(int left, int top, int w, int h, QWidget *parent = nullptr);
    ~MainWindow();
};

class Editor : public QWidget{
    Q_OBJECT
public:
    int x, y, width, height;

    Editor(QWidget * par, int left, int top, int w, int h);
    Editor();
    void readOnly();
    void setText(QString text);
    QString getText();

public slots:
  void clear();

protected:
    QTextEdit * me;
    QWidget * parent;

private:
    void show();
};

class CompileButton : public QObject{
Q_OBJECT
public:
    int x, y, width, height;

    CompileButton(int left, int top, int w, int h, QWidget * par);
    void show();
    void setText(const QString text);

signals:
    void clicked(); //kliknuto na *me

private:
    QPushButton * me;
    QWidget * parent;
};

class Device : public QObject{
  Q_OBJECT
public:
    int ID;
    int state = 0;
    Device(Editor * w);

protected slots:
    virtual void readState() = 0;

protected:
    QTimer * timer;
    Editor * window;

};

class Head : public Device{
  Q_OBJECT
public:
  Head(Editor * w);

protected slots:
  void readState();
};

class Port{
public:
    Device * device = nullptr;
    Port();
};

class SystemLibrary{

public:
  bool existCommand(QString command);
  void doCommand(QString command);
  void delay(Queue * queue);
  SystemLibrary(Controller * IC, Editor * w);

private:
  QVector<QString> functions = {"delay"};
  Controller * controller;
  Editor * window;

};


class CompilerErrorHandler{

  bool checkSyntax(Parser * parser, QString rawCommand);

};


class Compiler{
public:
    Compiler(Editor * editor);
    void validate(Parser *parser, ProcessLoop * processLoop, Controller * controller);
    void print(QString message);
    Queue * createQueue(QVector<QString> commandList, Parser * parser, Controller * controller);

private:
	Editor * window;
  QVector<QString> Errors = {"OK", "Syntax error", "Command does not exist", "Invalid data type", "Port does not exist"};
  CompilerErrorHandler * errorHandler;

  Call * createCall(Parser * parser, QString rawCommand, Controller * controller);
  QString deleteSpaces(QString command);
  void callQueue(QVector<Call*> queue, int position);
};

class Controller : public QObject{
Q_OBJECT
public:

	  DriverLibrary * driverLibrary;
    SystemLibrary * systemLibrary;
    QVector<Port *> PORTS;
    Controller(Editor * editor, Editor * driverWindow);

public slots:
    void loadText(Compiler * compiler, ProcessLoop * processLoop);   //zapocni nacteni kodu, validaci etc.
    int getNumberOfPorts();

private:
    int portsNumber = 8;
    Editor * window;

};

class DeviceManager : public QObject{

Q_OBJECT
public:
    DeviceManager(Editor * w, Controller * IC);
    int numberOfDevices();
    void connectDevice(Device * device, int port);
    void disconnectDevice(int port);

public slots:
  void proceed(Editor * deviceEditor);

private:
    Editor * window;
    Controller * controller;
    QVector<int> ports = {0, 0, 0, 0, 0, 0, 0, 0};
};

class Driver{
public:
    virtual void execute(Device * device, QString command) = 0;
    int ID;
    QVector<QString> functions;
    int portNumber;

};

class HeadDriver : public Driver{
public:

    HeadDriver();
    void execute(Device * device, QString command);
    void blink(Device * device);
    void light_on(Device * device);
    void light_off(Device * device);
};

class DriverLibrary{

public:
	bool existCommand(int pinNumber, QString command);
	void doCommand(int pinNumber, QString command);
	DriverLibrary(Controller* par, Editor * w);

private:
	QVector<Driver *> drivers = {new HeadDriver};
	Controller * controller;
  Editor * window;
};

class Queue : public QObject{
Q_OBJECT
public:
  Queue();
  ~Queue();
  void appendCommand(Call * commandCall);
  int getLength();
  Call * getCommand(int position);
  void call(int position);


public slots:
  void callQueue();

private:
  QVector<Call*> queueVector;
  int position = 0;

};

class ProcessLoop : public QObject{

Q_OBJECT
public:
  ProcessLoop();
  void start(Queue * q);

public slots:
  void stop();

private slots:
  void cycle();

private:
  int tickDelay = 500;
  QTimer * timer;
  Queue * queue;

};


#endif // CLASSES_H
