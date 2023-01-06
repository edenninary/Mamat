CXX    = g++
CCLINK = $(CXX)
CXXFLAGS = -Wall -g -std=c++11
OBJS   = ip.o string.o port.o
EXEC   = firewall.exe

$(EXEC): libfirewall.so main.o
	 $(CCLINK) $(CXXFLAGS) main.o -o $(EXEC) -lfirewall -linput -L.

libfirewall.so: $(OBJS)
	$(CCLINK) -shared $(OBJS) -o libfirewall.so

ip.o: ip.h generic-field.h ip.cpp string.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp

string.o: string.cpp string.h
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp

port.o: port.cpp string.h generic-field.h port.h
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp

main.o: main.cpp string.h generic-field.h ip.h port.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f libfirewall.so *.o

