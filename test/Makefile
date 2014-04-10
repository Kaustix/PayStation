## the test directory shoul dreally only contain one .cc file (the main.cc)
## so I decided to keep everything here

CC = g++
LN = g++
LIBS = -lcppunit -ldl -lpaystation
PRODUCTIONDIR = ../obj
THEOBJECTS = main.o
HEADERDIRS = ../include
OBJDIR = .
CCFLAGS = -I $(HEADERDIRS) -std=c++0x
LNFLAGS = -L$(PRODUCTIONDIR)/paystation/
OBJS = $(addprefix $(OBJDIR)/, $(THEOBJECTS))



$(OBJDIR)/testcases: $(OBJS) $(PRODUCTIONDIR)/paystation/libpaystation.a
	$(LN) $(LNFLAGS) -o $@ $(OBJS) $(LIBS)

$(OBJDIR)/%.o : %.cc
	$(CC) $(CCFLAGS) -c -o $@ $<

.PHONY : clean
clean :
	rm -f $(OBJDIR)/*.o *~ 

## generate the prerequistes and append to the desired file 
.prereq : $(THEOBJECTS:.o=.cc) $(wildcard $(HEADERDIRS)/*.h) $(wildcard *h) Makefile
	rm -f .prereq 
	$(CC) $(CCFLAGS) -MM $(THEOBJECTS:.o=.cc) >> ./.prereq
## include the generated prerequisite file 
include .prereq