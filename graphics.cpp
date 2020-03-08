#include "classes.h"

MainWindow::MainWindow(int l, int t, int w, int h, QWidget *parent)
    : QMainWindow(parent)
{

    this->x = l;
    this->y = t;
    this->width = w;
    this->height = h;

    this->resize( this->width, this->height);

}

MainWindow::~MainWindow()
{}




CompileButton::CompileButton(int left, int top, int w, int h, QWidget * par)
{

    this->x = left;
    this->y = top;
    this->width = w;
    this->height = h;
    this->parent = par;

    this->me = new QPushButton(par);
    this->me->setGeometry(this->x, this->y, this->width, this->height);


    QObject::connect(this->me, &QPushButton::clicked, this, &CompileButton::clicked);

}

void CompileButton::show(){

    this->me->show();

}

void CompileButton::setText(const QString text){

    this->me->setText(text);

}


Editor::Editor(QWidget * par, int l, int t, int w, int h)
{

    this->parent = par;
    this->me = new QTextEdit(this->parent);
    this->x = l;
    this->y = t;
    this->width = w;
    this->height = h;
    this->show();

}

void Editor::show(){

    this->me->show();
    this->me->setGeometry(this->x, this->y, this->width, this->height);

}

void Editor::readOnly(){

    this->me->setReadOnly(true);

}

void Editor::setText(QString text){    this->me->setText(text);    }

QString Editor::getText(){  return this->me->toPlainText(); }

Editor::Editor(){};
