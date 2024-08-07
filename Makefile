CXX=g++
CXXFLAGS=-g -Wall 
OBJS=ip.o port.o string.o
EXEC=firewall.exe
RM=rm -rf

#library
libfirewall.so: $(OBJS)
	$(CXX) -shared $(OBJS) -o libfirewall.so 

#excutable
firewall.exe: firewall.o libfirewall.so libinput.so 
	$(CXX)  $(CXXFLAGS) firewall.o -o firewall.exe   -lfirewall   -linput  -L.

#object files
firewall.o: main.cpp
	$(CXX)  $(CXXFLAGS) -c -fpic main.cpp -o firewall.o
#port
port.o: port.cpp port.h
	$(CXX)  $(CXXFLAGS) -c -fpic port.cpp -o port.o
#ip
ip.o: ip.cpp ip.h
	$(CXX)  $(CXXFLAGS) -c -fpic ip.cpp -o ip.o
#string
string.o: string.cpp string.h
	$(CXX)  $(CXXFLAGS) -c -fpic string.cpp -o string.o



#cleanup
clean:
	$(RM) *.o *.so $(EXEC) 
