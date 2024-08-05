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
#include "port.h"
#define NUM_OF_FIELDS 4

//constructor
Port::Port(String type_of_port, short lowRangeNumber,short highRangeNumber){
        this->type_of_port = type_of_port;
        this->highRangeNumber = highRangeNumber;
        this->lowRangeNumber = lowRangeNumber;
    };

//copy constructor
Port::Port(const Port& other_port){
    this->type_of_port =  other_port.type_of_port;
    this->lowRangeNumber =  other_port.lowRangeNumber;
    this->highRangeNumber =  other_port.highRangeNumber;
}

//match overloading
bool Port::match(const GenericString &packet){
        bool retVal = false ;
        packet.trim();
        StringArray packet_divided = packet.split(",");

        for (int i = 0; i < NUM_OF_FIELDS; ++i) {
            StringArray field_divided = (packet_divided[i]).split("=");
            // "  src-ip =    XXX.XXX.XXX.XXX ,      dst-ip = YYY.YYY.YYY.YYY , src-port  = PRT,dst-port=PRT         "
            field_divided[0].trim();
            if ( field_divided[0]==type_of_port ){
              //   field_divided[1] is the port of the packet
                (field_divided[1]).trim()
                   int packet_port_integer = field_divided[1].to_integer(); //just for testing it is decoupled;
                   short packet_port = (short)packet_port_integer;
                if (  ( this->lowRangeNumber <= packet_port   )&& ( packet_port <= this->highRangeNumber )  ){
                    retVal=true;
                    break;
                }
            }
        }

        return retVal;


    };

//destructor
Port::~Port(){};


