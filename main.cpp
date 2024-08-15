//
// Created by talkk on 03/08/2024.
//



/**
*
 * in herer we first parse the rule,
 * then call for the needed class and then iterate on the entries in the .txt file
*/

#include "ip.h"
#include "port.h"
#include "string.h"
#include <iostream>
#include "generic-field.h"
#include "generic-string.h"
#include "input.h"
#include "string-array.h"

//old main
/**
int main(int argc,char **argv) {

const char* port_str = "port";
const char* ip_str = "ip";


String input_rule =  argv[1];
String input_rule = std::in  ;

String::trim(input_rule);
String rule = new String; //TODO: find another way not on the heap

rule = input_rule;
StringArray rule_divided=String::split('=');

//for example will be  "dst-port"
String category = rule_divided[0]; //TODO: match implementation of StringArray
StringArray category_divided=category.split('-');
String RouteType = category_divided[0]; //will be src/dst NOT NEEDED ?
String componentType = category_divided[1]; //will be "port/ip"
        //will be the range "22-22"
String limits=rules_divided[1]; //TODO: match implementation of StringArray
StringArray limits_divided=limits.split('-');
String lowerLimStr=limits_divided[0];// getting the lower limit
String upperLimStr=limits_divided[1]; //getting the higher limit


int lowerLim = (int) lowerLim.to_integer;
int upperLim=(int) upperLimStr.to_integer;
//TODO check for error in conversion int? to int

//right now we have the limits, the kind and now we should pass over the packets
// in the .txt file
// and for each one test for the rule


genericField obj;

if ( componentType == port_str ){

    //another way
    obj = new Port(category,lowerLim,upperLim)


     //* old way
    //port portObj(RouteType,lowerLim,upperLim);
    //parse_input(&portObj);

}
else if ( componentType == ip_str ){ //TODO: rework IP

    //another way
    obj = new Ip(category,lowerLim,upperLim)


   //  * old way
   // ip ipObj(RouteType,lowerLim,upperLim);
    //parse_input(&ipObj);

}
parse_input(obj);

delete obj
delete rule;


}
**/


int main(int argc,char **argv) {
    const char* port_str = "port";
    const char* ip_str = "ip";
    if (argc<2){
        //well that shouldn't happen
    }
    else {
    String rule = argv[1];
    // rule = *(rule.trim()); // ?
    rule.trim();
    StringArray rules_divided=rule.split("=");

//for example will be  "dst-port"
        if(!rules_divided[1]) ;//std::cout << "\n\nrules_divided\n\n" << std::endl;
        String category = rules_divided[0]->as_string(); //TODO: match implementation of StringArray
        category.trim();
        StringArray category_divided=category.split("-");
        String RouteType = category_divided[0]->as_string(); //will be src/dst NOT NEEDED ?
        String componentType = category_divided[1]->as_string(); //will be "port/ip"
        //will be the range "22-22"
        String limits=rules_divided[1]->as_string(); //TODO: match implementation of StringArray
        limits.trim();

        

//TODO check for error in conversion int? to int

//right now we have the limits, the type and now we should pass over the packets
// in the .txt file
// and for each one test for the rule


        //genericField obj;

        if ( componentType == port_str ){
            //another way
          //  obj = new Port(category,lowerLim,upperLim);
            StringArray limits_divided=limits.split("-");
            if(!limits_divided[1]);// std::cout << "\n\nlimits_divided\n\n" << std::endl;
            String lowerLimStr=limits_divided[0]->as_string();// getting the lower limit
            String upperLimStr=limits_divided[1]->as_string(); //getting the higher limit
            lowerLimStr.trim();
            upperLimStr.trim();
            int lowerLim =  lowerLimStr.to_integer();
            int upperLim =  upperLimStr.to_integer();

            Port portObj(category,lowerLim,upperLim);
            parse_input(portObj);
        }
        else if ( componentType == ip_str ){
            //another way
            //obj = new Ip(category,lowerLim,upperLim);

             Ip ipObj(category,rule);
            parse_input(ipObj);
        }
      //  parse_input(obj);
      //  delete obj;
    }
}