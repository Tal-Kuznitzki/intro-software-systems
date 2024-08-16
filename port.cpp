//
// Created by talkk on 03/08/2024.
//


/**
 *
 *
 * template of packet to keep in Mind:
 *
 * src-ip=XXX.XXX.XXX.XXX,dst-ip=YYY.YYY.YYY.YYY,src-port=PRT,dst-port=PRT
    rule example ” dst-port =  3-12

 */
#include "string.h"
#include "port.h"
#define NUM_OF_FIELDS 4




//private:
   // String type_of_port; //should be "src-port" || "dest-port"
  //  short lowRangeNumber;
 //   short highRangeNumber;
//public:
    //constructor
Port::Port(String type_of_port, int lowRangeNumber,int highRangeNumber){
        this->type_of_port = type_of_port;
        this->highRangeNumber = highRangeNumber;
        this->lowRangeNumber = lowRangeNumber;
    }
    //copy constructor
Port::Port(const Port &other_port){
        this->type_of_port =  other_port.type_of_port;
        this->lowRangeNumber =  other_port.lowRangeNumber;
        this->highRangeNumber =  other_port.highRangeNumber;
    }
    //match overloading
bool Port::match(const GenericString &packet) const {
        bool retVal = false ;
        //TODO: test if needed to trim the packet
       // packet->as_string().trim();
        StringArray packet_divided = packet.split(",");

        for (int i = 0; i < packet_divided.get_size(); ++i) {
            StringArray field_divided = (packet_divided[i])->as_string().split("=");
            // "  src-ip =    XXX.XXX.XXX.XXX ,      dst-ip = YYY.YYY.YYY.YYY , src-port  = PRT,dst-port=PRT         "
            field_divided[0]->as_string().trim().as_string();
            if ( field_divided[0]->as_string()==type_of_port ){
                //   field_divided[1] is the port of the packet
                (field_divided[1])->as_string().trim().as_string();
                int packet_port_integer = field_divided[1]->as_string().to_integer(); //just for testing it is decoupled;
                int packet_port = packet_port_integer;
                if (  ( this->lowRangeNumber <= packet_port   )&& ( packet_port <= this->highRangeNumber )  ){
                    retVal=true;
                    break;
                }
            }
        }

        return retVal;


    }
Port::~Port(){}









//destructor



