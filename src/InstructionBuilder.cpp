#include "InstructionBuilder.h"
#include "parser.h"
#include "InstrucionParser.h"
std::string HexFromDecimal(int num){
    int temp = num;
    int i = 0 , j , r ;
    std::string hex = "";
    while (temp != 0){
        r = temp % 16;
        if (r < 10){
            hex += r + 48;
        } else {
            hex += r + 55;
        }
        temp = temp / 16 ;
    }
    reverse(hex.begin(), hex.end());
    return hex;
}

InstructionBuilder::InstructionBuilder(std::string path) {
    obectCode.setTheMap();
    readd(path);
    passOne();
    setIInvalidLiterals();
}
std::vector<InstrucionParser> InstructionBuilder::getInstructions() {
    return instrucions;
}
void InstructionBuilder::passOne() {

    int ssize = lines.size();
    for(int i = 0; i < ssize; i++) {
        InstrucionParser instr = parse(lines[i]);//get instrucion from parser
        std::cout<<instr.getLabel()<<" "<<instr.getOperaion()<<" "<<instr.getOperand()<<"   LLLLL\n";
        instr.setAddress(pc);
        std::string op = instr.getOperaion();
        transform(op.begin(), op.end(), op.begin(), ::tolower);
        if(instr.isComment())continue;
        if(op == "start") {

            pc += startInst(instr, firstStart);
            instrucions.push_back(instr);
            continue;
        }
        firstStart = false;
        int format = obectCode.getTheFormat(op);//+ format get format from y7ya
        if(format == -1) {
            int pc2 = get_locctr_address(instr, pc);// get address from 7kma
            instr.setFormat(pc2 - pc);
            pc = pc2;
        } else {
            pc += format;
            instr.setFormat(format);
        }
        handle_literals(instr);
        instrucions.push_back(instr);
    }
}
void InstructionBuilder::readd(std::string path) {
    lines = f.read(path);
}

bool InstructionBuilder::isInt(std::string s) {
    int ssize = s.size();
    for(int i = 0 ; i < ssize ; i++) {
        if(!(s[i] >= '0' && s[i] <= '9')) {
            return false;
        }
    }
    return true;
}

void InstructionBuilder::handle_literals(InstrucionParser ins ) {
    std::string operand = ins.getOperand();
    std::string operation = ins.getOperaion();
    transform(operation.begin(), operation.end(), operation.begin(), ::tolower);
    bool found = false;
    if (ins.getFormat() == 1 || ins.getFormat() == 2){return;}
    int ssize = literals.size();
    for (int i = 0; i < ssize; i++){
        if (literals[i] == operation){
            found = true;
            break;
        }
    }
    if (!found) {
        if(operand[0] == '=') {
            std::string str = operand.substr(3, operand.size() -4);
            if((operand[1] == 'x' || operand[1] == 'X' )&& (operand[2] == '\'' && operand[operand.size()-1] == '\'')) {
                if(str.size()% 2 == 0 &&  str.size() > 0 && str.size() <= 6 && isHex(str)) {
                    if(operation == "ldch" ) {
                        if(str.size() == 2 ) {
                            literals_data.push_back(make_pair(1,str));
                        } else {
                            ins.setErrorFlag(true);
                            ins.setErrorMsg("incorrect length of literal");
                        }
                    } else {
                        literals_data.push_back(make_pair(3,str));
                    }
                } else {
                    ins.setErrorFlag(true);
                    ins.setErrorMsg("incorrect length of literal");
                }
            } else if((operand[1] == 'c' || operand[1] == 'C') && (operand[2] == '\'' && operand[operand.size()-1] == '\'')) {
                if(str.size() == 1 || str.size() == 3) {
                    if(operation == "ldch" && str.size() == 1 ) {
                        int x = str[0];
                        literals_data.push_back(make_pair(1,HexFromDecimal(x)));
                    } else {
                        std::string ssss = "";
                        for(int i = 0 ; i < str.size() ;i++){
                            int x = str[i];
                            ssss += HexFromDecimal(x);
                        }
                        literals_data.push_back(make_pair(3,ssss));
                    }
                } else {
                    ins.setErrorFlag(true);
                    ins.setErrorMsg("incorrect length of literal");
                }
            } else { //invalid literal
                ins.setErrorFlag(true);
                ins.setErrorMsg("invalid literal");
            }

        } else { // not a literal
            return;
        }
    }

}
int InstructionBuilder::get_locctr_address(InstrucionParser ins,int loc_ctr) {
    std::string op = ins.getOperaion();
    std::string operand = ins.getOperand();
    transform(op.begin(), op.end(),op.begin(), ::tolower);
    if(op == "byte") {
        if((operand[0] == 'x' || operand[0] == 'X' )&& (operand[1] == '\'' && operand[operand.size()-1] == '\'')) {
            std::string str = operand.substr(2, operand.size() - 3 );
            if(str.size()%2 != 0) {
                ins.setErrorFlag(true);
                ins.setErrorMsg("odd number of half bytes");
                return loc_ctr;
            }
            loc_ctr += str.size() /2;
        } else if ((operand[0] == 'c' || operand[0] == 'C') && (operand[1] == '\'' && operand[operand.size()-1] == '\'')) {
            std::string str = operand.substr(2, operand.size() - 3);
            loc_ctr += str.size() ;
            return loc_ctr;

        } else {
            ins.setErrorFlag(true);
            ins.setErrorMsg("incomplete assembly");
            return loc_ctr;
        }
    } else if(op == "resb") { //done
        if(!isInt(operand)) {
            ins.setErrorFlag(true);
            ins.setErrorMsg("error size must be number");
            return loc_ctr;
        }
        loc_ctr +=   std::stoi(ins.getOperand());
    } else if(op == "word") { // done
        loc_ctr += 3;
    } else if(op == "resw") { //done
        if(!isInt(operand)) {
            ins.setErrorFlag(true);
            ins.setErrorMsg("error size must be number");
            return loc_ctr;
        }
        loc_ctr +=   std::stoi(ins.getOperand() )*3;
    }
    return loc_ctr;
}
int InstructionBuilder::startInst(InstrucionParser instr, bool firstStart) {
    if(!firstStart) {
        instr.setErrorFlag(true);
        instr.setErrorMsg("Start in wrong position");
    } else {
        std::string s = instr.getOperaion();
        if(s.size() == 0) {
            instr.setErrorFlag(true);
            instr.setErrorMsg("missing or misplaced operand field ");
        } else if(isHex(s) && s.size() <= 4) {
            return std::stoi(s, 0, 16);
        }
    }
    return 0;
}

bool InstructionBuilder::isHex(std::string s) {
    for(char c : s) {
        if((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') ) {
            continue;
        }
        return false;
    }
    return true;
}

void InstructionBuilder::setIInvalidLiterals(){
    literals.push_back("sta");
    literals.push_back("stb");
    literals.push_back("stf");
    literals.push_back("sti");
    literals.push_back("stl");
    literals.push_back("stx");
    literals.push_back("stt");
    literals.push_back("sts");
    literals.push_back("stch");
    literals.push_back("rsub");
    literals.push_back("ssk");
    literals.push_back("j");
    literals.push_back("jsub");
    literals.push_back("jeq");
    literals.push_back("jlt");
    literals.push_back("jgt");
}

