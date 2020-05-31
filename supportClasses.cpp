#include "classes.h"

Error::Error(){



}

QVector<QString> Error::getVector_string(){ return this->E_VECTOR_STRING; }
int Error::getInt(){  return this->E_INT; }
float Error::getFloat(){  return this->E_FLOAT; }
QString Error::getString(){ return this->E_STRING;  }


Queue::Queue(){

}

void Queue::appendCommand(Call * commandCall){

  this->queueVector.append(commandCall);

}

Queue::~Queue(){

  int len = this->getLength();
  for(int i = 0; i < len; ++i){

    delete this->queueVector[i];

  }

}

void Queue::callQueue(){

  int len = this->queueVector.size();

  if(this->position < len){

    this->queueVector[this->position++]->doCommand();
  }
}


Call * Queue::getCommand(int position){

  return this->queueVector[position];

}

int Queue::getLength(){

  return this->queueVector.size();

}

void Queue::call(int position){

  this->queueVector[position]->doCommand();

}

Call::Call(){}

SystemCall::SystemCall(SystemLibrary * sysLib, QString com){

  this->systemLibrary = sysLib;
  this->command = com;

}

void SystemCall::doCommand(){

  this->systemLibrary->doCommand(this->command);

}

DriverCall::DriverCall(DriverLibrary * driverLib, QString com, int portNum){

  this->driverLibrary = driverLib;
  this->command = com;
  this->portNumber = portNum;

}

void DriverCall::doCommand(){

  this->driverLibrary->doCommand(this->portNumber, this->command);

}

ErrorCall::ErrorCall(Compiler * comp, QString message, QString com){

  this->errorMessage = message;
  this->compiler = comp;
  this->command = com;

}

void ErrorCall::doCommand(){

  QString err = this->errorMessage + " (in: \"" + this->command + "\")";
  this->compiler->print(err);


}


void Arguments::addArgument(QString arg){

  this->argsVector.append(arg);

}

QString Arguments::getArgument(int position){

  if(position >= this->argsVector.length()){  return (new Error)->getString(); }
  return this->argsVector[position];

}

Parser::Parser(QString parser){

  this->rawParser = parser;

}


QVector<QString> Parser::parse(){

  QVector<QString> vect;
  QString tempParser = this->rawParser;

  while( tempParser.contains(";") ){

    int position = tempParser.indexOf(";");
    vect.append( tempParser.left(position) );
    tempParser = tempParser.mid(position + 1);

  }

  return vect;

}


QString Parser::getParser(){  return this->rawParser; }


int Parser::getPortNumber(QString rawCommand){

  int right = rawCommand.indexOf("]");
  if(right == -1){ return -2; } //chyba v syntaxi

  rawCommand = rawCommand.mid(1, right - 1);

  bool ok;
  int portNum = rawCommand.toInt(&ok);

  if(!ok){  return -1;  } //chyba v datovem typu
  else{ return portNum; }

}

Arguments* Parser::getArguments(QString rawCommand){

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


QString Parser::getCommand(QString rawCommand){

  int pos = rawCommand.indexOf("]");
  int argPos = rawCommand.indexOf("(");

  if(argPos == -1){ return rawCommand.mid(pos + 1); }
  return rawCommand.mid(pos + 1, argPos - pos - 1);

}

ProcessLoop::ProcessLoop()
{

  this->timer = new QTimer(this);
  QObject::connect(this->timer, &QTimer::timeout, this, &ProcessLoop::cycle);

}

void ProcessLoop::cycle()
{

  int len = this->queue->getLength();

  for(int i = 0; i < len; ++i){

    this->queue->call(i);

  }
}

void ProcessLoop::start(Queue * q, QVector<int> periods){

  this->queue = q;

  this->tickDelay = this->calculateCommonPeriod(periods);
  timer->start(this->tickDelay);

}

void ProcessLoop::stop(){

  delete this->queue;
  timer->stop();

}


int ProcessLoop::greatestCommonDivisor(int a, int b){

    int t;

    while(b != 0){

        t = b;
        b = a % b;
        a = t;

    }
    return a;

}

int ProcessLoop::calculateCommonPeriod(QVector<int> periods)
{

    if(periods.size() == 2){

        return this->greatestCommonDivisor(periods[0], periods[1]);

    }
    else if(periods.size() == 1){

        return periods[0];

    }
    else{

            periods.removeLast();
            return this->greatestCommonDivisor( periods[0], this->calculateCommonPeriod( periods ) );

    }
}
