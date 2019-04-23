#include "parser.h"
#include <regex>
InstrucionParser parse(std::string in){
    std::cout<<in<<"    String n\n";
    std::regex r ("([a-zA-Z][a-zA-Z0-9]*)?( +((\\+)?[a-zA-Z]{1,5}))( +([-=\\+\\,a-zA-Z0-9#\'\\*]+))?( +(.*))? *");
    std::smatch m;
    if(std::regex_match(in,r)){
        if(regex_search(in, m, r) == true){
            InstrucionParser i(m.str(1), m.str(3), m.str(6));
            if(m.str(8).length() > 0){
                i.setCommentflag(true);
                i.setCommentMsg(m.str(8));
            } else {
                i.setCommentflag(false);
            }
            return i;
        }
        else {
            InstrucionParser i("", "", "");
            i.setErrorFlag(true);
            i.setErrorMsg("Uncomplete Assemble!!");
            return i;
        }
    } else {
        InstrucionParser i("", "", "");
        i.setErrorFlag(true);
        i.setErrorMsg("Uncomplete Assemble!!");
        return i;
    }
}
