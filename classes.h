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

class Code{

public:
  Code(QString code);
  QVector<QString> parse();
  QString getCode();
  int getPortNumber(QString rawCommand);
  QString getCommand(QString rawCommand);

private:
  QString rawCode;

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
    Device();

protected slots:
    virtual void readState() = 0;

protected:
    QTimer * timer;

};

class Head : public Device{
  Q_OBJECT
public:
  Head();

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
  void delay();
  SystemLibrary(Controller * IC, Editor * w);

private:
  QVector<QString> functions = {"delay"};
  Controller * controller;
  Editor * window;

};

class Compiler{
public:
    Compiler(Editor * editor);
    void validate(Code *code);
    Controller * controller;
    void print(QString message);

private:
	Editor * window;
  QVector<QString> Errors = {"OK", "Syntax error", "Command does not exist", "Invalid data type", "Port does not exist"};

  Call * createCall(Code * code, QString rawCommand);
  QString deleteSpaces(QString command);
  void callQueue(QVector<Call*> queue, int position);
};

class Controller : public QObject{
Q_OBJECT
public:

	  DriverLibrary * driverLibrary;
    SystemLibrary * systemLibrary;
    QVector<Port *> PORTS;
    Controller(Editor * editor, Compiler * comp, Editor * driverWindow);

public slots:
    void loadText();   //zapocni nacteni kodu, validaci etc.
    int getNumberOfPorts();

private:
    int portsNumber = 8;
    Editor * window;
    Compiler * compiler;

};

class DeviceManager{
public:
    DeviceManager(Controller * IC);
    int numberOfDevices();
    void connectDevice(Device * device, int port);
    void disconnectDevice(int port);

private:
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


#endif // CLASSES_H
