CXX = g++
CXXFLAGS = -Wall -L. -g 
OBJS = string.cpp field.cpp ip.cpp port.cpp
EXEC = firewall.exe
RM = rm -rf

make all:$(EXEC)

firewall:
	$(CXX) $(CXXFLAGS) -fPIC -shared $(OBJS) -o libfirewall.so


$(EXEC): firewall 
	$(CXX) $(CXXFLAGS) main.cpp -o $(EXEC) -linput -lfirewall


clean:
	-$(RM) firewall $(EXEC)