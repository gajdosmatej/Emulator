#include <QObject>
#include <QPushButton>
#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QWidget>
#include <QTextEdit>
#include <QTextStream>
#include <QTimer>

#ifndef CLASSES_H
#define CLASSES_H

class DriverLibrary;
class Controller;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int x, y, width, height;

    MainWindow(int left, int top, int w, int h, QWidget *parent = nullptr);
    ~MainWindow();
};



class Editor : public QWidget
{
    Q_OBJECT
public:
    int x, y, width, height;

    Editor(QWidget * par, int left, int top, int w, int h);
    Editor();
    void readOnly();
    void setText(QString &text);
    QString getText();

protected:
    QTextEdit * me;
    QWidget * parent;

private:
    void show();
};




class CompileButton : public QObject
{
Q_OBJECT
public:
    int x, y, width, height;

    CompileButton(int left, int top, int w, int h, QWidget * par);
    void show();
    void setText(const QString &text);

signals:
    void clicked(); //kliknuto na *me

private:
    QPushButton * me;
    QWidget * parent;
};


class Device : public QObject
{
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



class Head : public Device
{
  Q_OBJECT
public:
  Head();

protected slots:
  void readState();
};



class Port
{
public:
    Device * device = nullptr;
    Port();
};




class Compiler
{
public:
    Compiler(Editor * editor);
    void validate(QString &code);
    Controller * controller;

private:
	Editor * window;
};



class Controller : public QObject
{
Q_OBJECT
public:

	DriverLibrary * driverLibrary;
    QVector<Port *> PORTS;
    Controller(Editor * editor, Compiler * comp);

public slots:
    void loadText();   //zapocni nacteni kodu, validaci etc.

private:
    int portsNumber = 8;
    Editor * window;
    Compiler * compiler;

};




class DeviceManager
{
public:
    DeviceManager(Controller * IC);
    int numberOfDevices();
    void connectDevice(Device * device, int port);
    void disconnectDevice(int port);

private:
    Controller * controller;
    QVector<int> ports = {0, 0, 0, 0, 0, 0, 0, 0};
};



class Driver
{
public:
    virtual void execute(Device * device, QString &command) = 0;
    int ID;
    QVector<QString> functions;
    int portNumber;

};



class HeadDriver : public Driver
{
public:

    HeadDriver();
    void execute(Device * device, QString &command);
    void blink(Device * device);
    void light_on(Device * device);
    void light_off(Device * device);
};


class DriverLibrary{

public:
	bool existCommand(int pinNumber, QString &command);
	void doCommand(int pinNumber, QString &command);
	DriverLibrary(Controller* par);

private:
	QVector<Driver *> drivers = {new HeadDriver};
	Controller * controller;
};


#endif // CLASSES_H