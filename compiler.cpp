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

int Compiler::getErrorID(Code * code, QString rawCommand){

  //-1 -> systemovy prikaz
  //0 -> v poradku
  //1 -> chybna syntaxe
  //2 -> prikaz neexistuje
  //3 -> chybny datovy typ
  //4 -> port neexistuje

  //systemovy prikaz
  if(this->controller->systemLibrary->existCommand(rawCommand)) return -1;

  if( rawCommand.left(1) != "[" ){  return 1; }

  int portNumber = code->getPortNumber(rawCommand);
  if( portNumber == -1 ){  return 3; }
  if( portNumber == -2){  return 1; }
  if(portNumber > (this->controller->getNumberOfPorts() - 1)){ return 4; }
  if(portNumber < 0){ return 4; }

  QString command = code->getCommand(rawCommand);
  if( !this->controller->driverLibrary->existCommand(portNumber, command) ){  return 2; }

  return 0;

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

  QVector<QVector<QString>> query;

  int len = codeList.length();
  this->window->setText("");

  bool ok = true;

  for(int i = 0; i < len; ++i){

    codeList[i] = this->deleteSpaces(codeList[i]);
    QString command = codeList.at(i);

    QString message = this->window->getText() + "Command " + QString::number(i) + ": ";
    int errorID = this->getErrorID(code, command);

    //drivery
    if(errorID != -1){

      message += this->Errors[errorID] + "\n";
      this->window->setText(message);

      if(errorID != 0){ ok = false; }

      QVector<QString> queryFunc = {command, "Driver"};
      query.append(queryFunc);

    }
    //system
    else{

      this->window->setText(message + this->Errors[0] + "\n");
      QVector<QString> queryFunc = {command, "System"};
      query.append(queryFunc);

    }
  }

  if(ok){

    for(int i = 0; i < len; ++i){

      QString command = query[i][0];
      QString call = query[i][1];

      if(call == "Driver"){
        this->controller->driverLibrary->doCommand(code->getPortNumber(command), code->getCommand(command));
      }
      else{
        this->controller->systemLibrary->doCommand(command);
      }
    }
  }
}
