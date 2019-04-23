#ifndef INSTRUCIONPARSER_H
#define INSTRUCIONPARSER_H
#include<bits/stdc++.h>
class InstrucionParser
{
    private:
        int address;
        bool errorFlag = false; //true if error exist
        bool commetFlag = false;
        std::string errorMsg; //error message
        //get from Op code
        int opCode;
        int format;
        //the instrucion component
        std::string label;
        std::string operation;
        std::string operand;
        std::string comment;
    public:
        InstrucionParser(std::string l, std::string op, std::string oper);
        virtual ~InstrucionParser();
        int getAddress();

        void setAddress(int add);
        bool isWrong();
        void setErrorFlag(bool f);
        std::string getErrorMsg();
        void setErrorMsg(std::string error);
        std::string getLabel();
        std::string getOperaion();
        std::string getOperand();
        int getFormat();
        void setFormat(int f);
        std::string getComment();
        bool isComment();
        void setCommentflag(bool f);
        void setCommentMsg(std::string str);
    protected:

};

#endif // INSTRUCIONPARSER_H
