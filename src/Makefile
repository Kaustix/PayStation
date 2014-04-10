## right now there is no production code apart from the libraries...
## Call recursively on the libraries

CC = g++
LN = g++
LIBS = -lncurses
THEOBJECTS = main.o
HEADERDIRS = ../include
OBJDIR = ../obj
CCFLAGS = -I $(HEADERDIRS) -std=c++0x
LNFLAGS = -L$(OBJDIR)/paystation/
OBJS = $(addprefix $(OBJDIR)/, $(THEOBJECTS))

.PHONY: all 
all: lib ../ps 

lib:
	$(MAKE) -C paystation
# generate the production code by linking here ...

../ps: main.cc $(OBJDIR)/paystation/libpaystation.a
	$(CC) $(CCFLAGS) $(LNFLAGS) -o $@ $^ $(LIBS)


$(OBJDIR)/%.o : %.cc
	$(CC) $(CCFLAGS) -c -o $@ $<

.PHONY : clean
clean :
	rm -f $(OBJDIR)/*.o *~
	$(MAKE) -C paystation clean

## generate the prerequistes and append to the desired file 
.prereq : $(THEOBJECTS:.o=.cc) $(wildcard $(HEADERDIRS)/*.h) Makefile
	rm -f .prereq 
	$(CC) $(CCFLAGS) -MM $(THEOBJECTS:.o=.cc) >> ./.prereq
## include the generated prerequisite file 
include .prereq