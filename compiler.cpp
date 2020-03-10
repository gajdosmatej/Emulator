#include "classes.h"

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

QString Code::getCommand(QString rawCommand){

  int pos = rawCommand.indexOf("]");
  return rawCommand.mid(pos + 1);

}


void Compiler::print(QString message){

  this->window->setText(this->window->getText() + message + "\n");

}


Call* Compiler::createCall(Code * code, QString rawCommand){

  QString command = code->getCommand(rawCommand);

  if(command == 0){ return new ErrorCall(this, this->Errors[1], rawCommand);  }
  if(this->controller->systemLibrary->existCommand(rawCommand)){  return new SystemCall(this->controller->systemLibrary, command); }

  if( rawCommand.left(1) != "[" ){  return new ErrorCall(this, this->Errors[1], rawCommand); }

  int portNumber = code->getPortNumber(rawCommand);
  if( portNumber == -1 ){  return new ErrorCall(this, this->Errors[3], rawCommand); }
  if( portNumber == -2){  return new ErrorCall(this, this->Errors[1], rawCommand); }
  if(portNumber > (this->controller->getNumberOfPorts() - 1)){ return new ErrorCall(this, this->Errors[4], rawCommand); }
  if(portNumber < 0){ return new ErrorCall(this, this->Errors[4], rawCommand); }

  if( !this->controller->driverLibrary->existCommand(portNumber, command) ){  return new ErrorCall(this, this->Errors[2], rawCommand); }

  return new DriverCall(this->controller->driverLibrary, command, portNumber);


}


QString Compiler::deleteSpaces(QString command){

  while(command.contains(" ")){

      QString l = command.left(command.indexOf(" "));
      QString r = command.mid(command.indexOf(" ") + 1);
      command = l + r;
  }

  while(command.contains("\n")){

    QString l = command.left(command.indexOf("\n"));
    QString r = command.mid(command.indexOf("\n") + 1);
    command = l + r;

  }

  return command;

}



void Compiler::validate(Code * code){

  QVector<QString> codeList = code->parse();
  int len = codeList.length();

  QVector<Call*> queueVector;

  for(int i = 0; i < len; ++i){

    codeList[i] = this->deleteSpaces(codeList[i]);
    queueVector.append( createCall(code, codeList[i]) );

  }

  this->window->setText("");

  Queue * queue = new Queue(queueVector, 0);
  queue->callQueue();

}
