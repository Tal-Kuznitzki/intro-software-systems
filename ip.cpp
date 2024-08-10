//
// Created by talkk on 03/08/2024.
//


/**
 * template of packet to keep in Mind:
 * src-ip=XXX.XXX.XXX.XXX,dst-ip=YYY.YYY.YYY.YYY,src-port=PRT,dst-port=PRT
    rule example ” dst-ip=122.128.68.0/27

 */
#include "string.h"
#include "ip.h"
#define NUM_OF_FIELDS 4
#define NUM_OF_OCTATES 4
#define IP_OCTATE_SIZE 8



//private:
 //   String type_of_ip; //should be "src-ip" || "dest-ip"
 //   String ip;

//protected:
    //constructor

Ip::Ip(String type_of_ip,String ip){
        this->type_of_ip = type_of_ip ; //src-ip || dst-ip
        this->ip = ip ; // EXAMPLE 255.64.1.1/15
    };
    //copy constructor
Ip::Ip(const Ip &other_ip){
        this->type_of_ip =  other_ip.type_of_ip;
        this->ip =  other_ip.ip;
    };
int Ip::ipToIntAndMask(String ipAddress,unsigned int mask){

        ipAddress.trim(); //just in case
        StringArray ipByOctate = ipAddress.split(".");
        int ipAddressINT = 0;
        String octate = "" ;
        int octateINT = 0  ;
        int ShftLftBy = 0  ;
        for (int i = 0; i <NUM_OF_OCTATES ; ++i) {
            octate = ipByOctate[i];
            octateINT = octate.to_integer();
            ShftLftBy =( (3-i)*IP_OCTATE_SIZE ) ;
            ipAddressINT+=( octateINT << ( ShftLftBy ) );
        }
        return (ipAddressINT & mask) ;
    }
    //match overloading
bool Ip:: match(const GenericString &packet){
        bool retVal = false ;
        //firewalled accepted ip-addresses calculations
        StringArray ip_divided  = (this->ip).split("/"); //split  122.0.0.0/15 into  0: 122.0.0.0     1:  15
        String ip_address = ip_divided[0];
        ip_address.trim();

        //generating the subnet-mask:
        String prefix = ip_divided[1];
        prefix.trim();
        int prefix_as_int = prefix.to_integer();
        int suffix = ( 32 - prefix_as_int);
        unsigned int mask = -1U <<  suffix ;// -1 unsigned is 0xFFFFFFFF


        //handling the packet
        packet.trim(packet);
        StringArray packet_divided = packet.split(",");

        for (int i = 0; i < NUM_OF_FIELDS; ++i) {
            //passing over the
            // "  src-ip =    XXX.XXX.XXX.XXX ,      dst-ip = YYY.YYY.YYY.YYY , src-port  = PRT,dst-port=PRT         "

            StringArray field_divided = packet_divided[i].split("=");
            String RouteType = (field_divided[0]).trim();
            String packetIpAddress = (field_divided[1]).trim();
            if ( RouteType==type_of_ip ){ // if field_divided[0] == "src-ip" or "dst-ip" according to "type_of_ip"
                //   field_divided[1] is the ip of the packet
                /**
                 NOW WE HAVE
                field_divided[1] is the ip  :   66.10.6.15 given in the packet
                ip_address is the ip given in the rule 122.0.0.0
                mask is the mask given : "15" - refer to the 15 leftist bits
                 /8 is the first byte
                 /16 is the second byte
                 /24 is the third byte
                 /32 is the fourth byte
                 example:
                say we have the ip the ip 192.168.10.1 as the received packet
                 //in binary
                 11000000.10101000.00001010.00000001
                 mask is 21
                 firewalled ip is 192.168.8.0
                 11000000.10101000.00001000.00000001
                 11111111.11111111.11111000.00000000
                  what to do ?
                  bitwise AND of the Mask and the packet_ip
                  and then check equality to the ip given in the rule
    **/
                int maskedRuleIp = ipToIntAndMask(ip_address,mask);
                int maskedPacketIp = ipToIntAndMask(packetIpAddress,mask);

                if ( maskedRuleIp == maskedPacketIp ){
                    retVal=true;
                    break;
                }
            }
        }




        return retVal;


    }
Ip::~Ip(){}//destructor




