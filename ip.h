//
// Created by talkk on 03/08/2024.
//

#ifndef IP_H
#define IP_H



class Ip : public GenericField {
private:
    String type_of_ip; //should be "src-ip" || "dest-ip"
    String ip;
public:
    Ip(String type_of_ip,String);
    Ip(const Ip &other_ip); //copy
    int ipToIntAndMask(String ipAddress,unsigned int mask);
    bool match(const GenericString &packet);
    ~Ip();



};
#endif //IP_H