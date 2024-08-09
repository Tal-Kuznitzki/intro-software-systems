//
// Created by talkk on 03/08/2024.
//

#ifndef PORT_H
#define PORT_H



class Port : public GenericField{
private:
    String type_of_port; //should be "src-port" || "dest-port"
    short lowRangeNumber;
    short highRangeNumber;
public:
    Port(String type_of_port, short lowRangeNumber,short highRangeNumber);
    Port(const Port &other_port); //copy
    bool match(const GenericString &packet);
    ~Port();



};
#endif //PORT_H