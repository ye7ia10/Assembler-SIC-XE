#ifndef INSTRUCTIONBUILDER_H
#define INSTRUCTIONBUILDER_H
#include<bits/stdc++.h>
#include<InstrucionParser.h>
#include<objectCodeMap.h>
#include<ReadFile.h>

class InstructionBuilder
{
    public:
        InstructionBuilder(std::string path);
        void passOne();
        std::vector<InstrucionParser> getInstructions();
        std::vector < std::pair <int ,std::string> > literals_data;
        std::vector <std::string> literals;
        void setIInvalidLiterals();
    protected:

    private:
        std::vector<std::string>lines;
        void handle_literals(InstrucionParser ins);
        std::vector<InstrucionParser>instrucions;
        objectCodeMap obectCode;
        int pc = 0;
        bool firstStart = true;
        ReadFile f;
        void readd(std::string path);
        bool isHex(std::string s);
        int startInst(InstrucionParser instr, bool firstStart);
        int get_locctr_address(InstrucionParser ins,int loc_ctr);
        bool isInt(std::string s);


};

#endif // INSTRUCTIONBUILDER_H
