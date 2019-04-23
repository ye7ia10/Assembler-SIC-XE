#include "InstrucionParser.h"

InstrucionParser::InstrucionParser(std::string l, std::string op, std::string oper)
{
    label = l;
    operation = op;
    operand = oper;
}
int InstrucionParser:: getAddress(){
    return address;
}
void InstrucionParser:: setAddress(int add){
    address = add;
}
bool InstrucionParser::isWrong(){
    return errorFlag;
}
void InstrucionParser::setErrorFlag(bool f){
    errorFlag = f;
}
std::string InstrucionParser::getErrorMsg(){
    return errorMsg;
}
void InstrucionParser::setErrorMsg(std::string error){
    errorMsg = error;
}
std::string InstrucionParser::getLabel(){
    return label;
}
std::string InstrucionParser::getOperaion(){
    return operation;
}
std::string InstrucionParser::getOperand(){
    return operand;
}
int InstrucionParser::getFormat(){
    return format;
}
void InstrucionParser::setFormat(int f){
    format = f;
}
std::string InstrucionParser::getComment(){
    return comment;
}
bool InstrucionParser::isComment(){
    return commetFlag;
}
void InstrucionParser::setCommentflag(bool f){
    commetFlag = f;
}
void InstrucionParser::setCommentMsg(std::string str){
    comment = str;
}
InstrucionParser::~InstrucionParser()
{
    //dtor
}
