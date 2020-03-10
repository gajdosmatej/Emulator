#include "classes.h"

Queue::Queue(QVector<Call*> qu, int pos){

  this->queue = qu;
  this->position = pos;

}

void Queue::callQueue(){

  int len = this->queue.size();

  if(this->position < len){

    this->queue[this->position++]->doCommand(this);
  }
}

Call::Call(){}

SystemCall::SystemCall(SystemLibrary * sysLib, QString com){

  this->systemLibrary = sysLib;
  this->command = com;

}

void SystemCall::doCommand(Queue * queue){

  this->systemLibrary->doCommand(this->command, queue);

}

DriverCall::DriverCall(DriverLibrary * driverLib, QString com, int portNum){

  this->driverLibrary = driverLib;
  this->command = com;
  this->portNumber = portNum;

}

void DriverCall::doCommand(Queue * queue){

  this->driverLibrary->doCommand(this->portNumber, this->command);

  queue->callQueue();

}

ErrorCall::ErrorCall(Compiler * comp, QString message, QString com){

  this->errorMessage = message;
  this->compiler = comp;
  this->command = com;

}

void ErrorCall::doCommand(Queue * queue){

  QString err = this->errorMessage + " (in: \"" + this->command + "\")";
  this->compiler->print(err);

  queue->callQueue();

}


//iniciace portu
Controller::Controller(Editor * editor, Compiler * comp, Editor * driverWindow){

    for(int i = 0; i < this->portsNumber; ++i){ this->PORTS.push_back(new Port);   }

    this->window = editor;
    this->compiler = comp;
	  this->driverLibrary = new DriverLibrary(this, driverWindow);
    this->systemLibrary = new SystemLibrary(this, driverWindow);
}

void Controller::loadText(){

    Code * code = new Code(this->window->getText());
    this->compiler->validate(code);
}

int Controller::getNumberOfPorts(){ return this->portsNumber; }

Port::Port()
{

}

SystemLibrary::SystemLibrary(Controller * IC, Editor * w){

  this->controller = IC;
  this->window = w;

}

bool SystemLibrary::existCommand(QString command){

  int len = this->functions.size();
  for(int i = 0; i < len; ++i){

    if(functions[i] == command){  return true;  }

  }

  return false;
}

void SystemLibrary::doCommand(QString command, Queue * queue){

  QString winText = this->window->getText() + "DO SYSCALL " + command + ";\n";
  this->window->setText(winText);

  if(command == "delay"){ this->delay(queue);  }
  else{ queue->callQueue(); }

}

void SystemLibrary::delay(Queue * queue){


  QTimer::singleShot(1000, queue, SLOT(callQueue()));

}
