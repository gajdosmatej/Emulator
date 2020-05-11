#include "classes.h"




void Compiler::print(QString message){

  this->window->setText(this->window->getText() + message + "\n");

}


Call* Compiler::createCall(Code * code, QString rawCommand){

  QString command = code->getCommand(rawCommand);
  QString arg0 = code->getArguments(rawCommand)->getArgument(0);
/*QTextStream out(stdout);
out<<arg0;*/

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

  QVector<QString> commandList = code->parse();
  int len = commandList.length();

  Queue * queue = new Queue;

  for(int i = 0; i < len; ++i){

    commandList[i] = this->deleteSpaces(commandList[i]);
    queue->appendCommand( createCall(code, commandList[i]) );

  }

  this->window->setText("");

  queue->callQueue();

}
