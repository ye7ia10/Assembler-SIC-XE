/*
#include <iostream>
#include <InstrucionParser.h>
#include "objectCodeMap.h"
#include <ReadFile.h>
#include "Ob.h"
#include<bits/stdc++.h>
using namespace std;
bool isHex(string s);
bool isInt(string s){
    for(int i = 0 ; i < s.size() ;i++){
        if(!(s[i] >= '0' && s[i] <= '9')){
            return false;
        }
    }
    return true;
}
int get_locctr_address(InstrucionParser ins,int loc_ctr){
    string op = ins.getOperaion();
    string operand = ins.getOperand();
    transform(op.begin() , op.end() ,op.begin() , ::tolower);
    if(op == "byte"){
        if((operand[0] == 'x' || operand[0] == 'X' )&& (operand[1] == '\'' && operand[operand.size()-1] == '\'')){
           cout<<operand<<"\n";
           string str = operand.substr(2 , operand.size() - 3 );
           cout<<str<<"   enter\n";
            if(str.size()%2 != 0){
                ins.setErrorFlag(true);
                ins.setErrorMsg("odd number of half bytes");
                return loc_ctr;
            }
            loc_ctr += str.size() /2;
        }else if ((operand[0] == 'c' || operand[0] == 'C') && (operand[1] == '\'' && operand[operand.size()-1] == '\'')){
            string str = operand.substr(2 , operand.size() - 3);
            loc_ctr += str.size() ;
            return loc_ctr;

        }else{
            ins.setErrorFlag(true);
            ins.setErrorMsg("incomplete assembly");
            return loc_ctr;
        }
    }else if(op == "resb"){ //done
        if(!isInt(operand)){
            ins.setErrorFlag(true);
            ins.setErrorMsg("error size must be number");
            return loc_ctr;
        }
        loc_ctr +=   std::stoi(ins.getOperand());
    }else if(op == "word"){ // done
        loc_ctr += 3;
    }else if(op == "resw"){ //done
        if(!isInt(operand)){
            ins.setErrorFlag(true);
            ins.setErrorMsg("error size must be number");
            return loc_ctr;
        }
        loc_ctr +=   std::stoi(ins.getOperand() )*3;
    }
    return loc_ctr;
}
int startInst(InstrucionParser instr, bool firstStart){
    if(!firstStart){
                instr.setErrorFlag(true);
                instr.setErrorMsg("Start in wrong position");
    }else{
        string s = instr.getOperaion();
        if(s.size() == 0){
            instr.setErrorFlag(true);
            instr.setErrorMsg("missing or misplaced operand field ");
        }
        else if(isHex(s) && s.size() <= 4){
            return std::stoi(s, 0, 16);
        }
    }
    return 0;
}
bool isHex(string s){
    for(char c : s){
        if((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') ){
            continue;
        }
        return false;
    }
    return true;
}
int main()
{
    ReadFile f;
    vector<string> v = f.read("input.txt");
    /*
    vector<string>lines;
    vector<InstrucionParser>instrucions;
    objectCodeMap obectCode;
    obectCode.setTheMap();
    int pc = 0;
    bool firstStart = true;
    string a[8][3];
    a[0][1] = "start";
    a[0][2] = "0";

    a[1][0] = "BGN";
    a[1][1] = "LDA";
    a[1][2] = "#0";

    a[2][0] = "DEVF3";
    a[2][1] = "BYTE";
    a[2][2] = "c'fssghs'";

    a[3][0] = "DEV04";
    a[3][1] = "BYTE";
    a[3][2] = "X'0434c62'";

    cout<<a[2][2]<<"\n";

    for(int i = 0; i < lines.size(); i++){
        cout<<pc<<"   pc\n";
        InstrucionParser instr(a[i][0],a[i][1],a[i][2]);//get instrucion from parser
        instr.setAddress(pc);
        string op = instr.getOperaion();
        transform(op.begin(), op.end(), op.begin(), ::tolower);
        if(instr.isComment())continue;
        if(op == "start"){
            pc += startInst(instr, firstStart);
            continue;
        }
        firstStart = false;
        int format = obectCode.getTheFormat(op);//+ format get format from y7ya
        if(format == -1){
            int pc2 = get_locctr_address(instr, pc);// get address from 7kma
            instr.setFormat(pc2 - pc);
            pc = pc2;
        }
        else{
            pc += format;
            instr.setFormat(format);
        }
    }
    cout<<pc<<"    pc\n";
    */
    /*
    return 0;
}
*/
