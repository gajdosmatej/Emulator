#include "classes.h"

Error::Error(){



}

QVector<QString> Error::getVector_string(){ return this->E_VECTOR_STRING; }
int Error::getInt(){  return this->E_INT; }
float Error::getFloat(){  return this->E_FLOAT; }
QString Error::getString(){ return this->E_STRING;  }


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


void Arguments::addArgument(QString arg){

  this->argsVector.append(arg);

}

QString Arguments::getArgument(int position){

  if(position >= this->argsVector.length()){  return (new Error)->getString(); }
  return this->argsVector[position];

}

Code::Code(QString code){

  this->rawCode = code;

}

QVector<QString> Code::parse(){

  QVector<QString> vect;
  QString tempCode = this->rawCode;

  while( tempCode.contains(";") ){

    int position = tempCode.indexOf(";");
    vect.append( tempCode.mid(0, position) );
    tempCode = tempCode.mid(position + 1);

  }

  return vect;

}

QString Code::getCode(){  return this->rawCode; }


Compiler::Compiler(Editor * editor){

    this->window = editor;
    this->window->readOnly();

}

int Code::getPortNumber(QString rawCommand){

  int right = rawCommand.indexOf("]");
  if(right == -1){ return -2; } //chyba v syntaxi

  rawCommand = rawCommand.mid(1, right - 1);

  bool ok;
  int portNum = rawCommand.toInt(&ok);

  if(!ok){  return -1;  } //chyba v datovem typu
  else{ return portNum; }

}

Arguments* Code::getArguments(QString rawCommand){

  int pos1 = rawCommand.indexOf("(");
  int pos2 = rawCommand.indexOf(")");

  Arguments * parsedArgs = new Arguments;
  QString rawArgs = rawCommand.mid(pos1 + 1, pos2 - pos1 - 1);

  while(rawArgs.indexOf(",") != -1){

      parsedArgs->addArgument( rawArgs.left(rawArgs.indexOf(",")) );
      rawArgs = rawArgs.mid(rawArgs.indexOf(",") + 1);

  }

  return parsedArgs;
}


QString Code::getCommand(QString rawCommand){

  int pos = rawCommand.indexOf("]");
  int argPos = rawCommand.indexOf("(");

  if(argPos == -1){ return rawCommand.mid(pos + 1); }
  return rawCommand.mid(pos + 1, argPos - pos - 1);

}
