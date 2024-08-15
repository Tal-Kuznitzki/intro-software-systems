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
#include <iostream>
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
int Ip::ipToIntAndMask(String ipAddress,unsigned int mask) const {

        ipAddress.trim().as_string(); //just in case
        StringArray ipByOctate = ipAddress.split(".");
        int ipAddressINT = 0;
        int octateINT ;
        int ShftLftBy ;
        for (int i = 0; i <ipByOctate.get_size() ; i++) {
          //  if(ipByOctate[i]){
                octateINT = ipByOctate[i]->as_string().to_integer();
                printf("OCTATATE NUMBER %d is %d\n",i,octateINT);
                ShftLftBy =( (3-i)*IP_OCTATE_SIZE ) ;
                ipAddressINT+=( octateINT << ( ShftLftBy ) );
         //   }
        }
        printf("DONE");
        return (ipAddressINT & mask) ;
    }
    //match overloading
bool Ip:: match(const GenericString &packet) const{
        bool retVal = false ;
        //firewalled accepted ip-addresses calculations
        String copy_ip = this->ip;
        StringArray ip_divided  = (copy_ip).split("/"); //split  122.0.0.0/15 into  0: 122.0.0.0     1:  15
       // if(!ip_divided[0]) ;//std::cout << "\n\n ip_devided 0 \n\n" << std::endl;
        String ip_address = (ip_divided[0])->as_string().trim().as_string();


        //generating the subnet-mask:
     //   if(!ip_divided[1]) ;//std::cout << "\n\nip_devided 1 \n\n" << std::endl;
        String prefix = (ip_divided[1])->as_string().trim().as_string();
        prefix.trim().as_string();
        int prefix_as_int = prefix.to_integer();
        printf("PREFIX: %d\n",prefix_as_int);
        int suffix = ( 32 - prefix_as_int);
        printf("SUFFIX: %d\n",suffix);
        unsigned int mask = -1U <<  suffix ;// -1 unsigned is 0xFFFFFFFF
    

        //handling the packet
        //TODO: maybe trimming is needed
        //  (packet.as_string()).trim();
        StringArray packet_divided = packet.split(",");
        
        for (int i = 0; i < packet_divided.get_size(); ++i) {
            //passing over the
            // "  src-ip =    XXX.XXX.XXX.XXX ,      dst-ip = YYY.YYY.YYY.YYY , src-port  = PRT,dst-port=PRT         "

            StringArray field_divided = packet_divided[i]->as_string().trim().as_string().split("=");
            // if(!ip_divided[0] || !ip_divided[1]) std::cout << "\n\nmatch for\n\n" << std::endl;
            String RouteType = (field_divided[0])->as_string().trim().as_string();

            if ( RouteType==this->type_of_ip ){ // if field_divided[0] == "src-ip" or "dst-ip" according to "type_of_ip"
                //   field_divided[1] is the ip of the packet
                /**
                 * 
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
                printf("the route is correct");
                String packetIpWithMask = field_divided[1]->as_string().trim().as_string();
                StringArray packetIpFull = (packetIpWithMask.split("/"));
                String packetIpWithoutMask =(packetIpFull)[0]->as_string().trim().as_string();
               // String packetIpAddress = (field_divided[1])->as_string().split("/").as_string().trim().as_string();
                int maskedRuleIp = ipToIntAndMask(ip_address,mask);
                int maskedPacketIp = ipToIntAndMask(packetIpWithoutMask,mask);
                printf("mask; %u\n", mask);
                printf("maskedRuleIp: %d\n",maskedRuleIp);
                printf("maskedPacketIp: %d\n",maskedPacketIp);
                if ( maskedRuleIp == maskedPacketIp ){
                    retVal=true;
                    break;
                }
            }
        }




        return retVal;


    }
Ip::~Ip(){}//destructor




