######################################################
# You should set program name and some settings here

EXECUTABLE := ./access

ifeq ($(shell uname ),Linux)
################################
CC := g++ -o
#LIBS := -lpthread -lstdc++ -ldl -lnsl  -ladiapi -lnccapi -lvceapi -lswiapi -ladidtm -lcnfapi -lpthread
LIBS := -lpthread -lstdc++ -ldl -lnsl  
#CFLAGS := -W -Wpointer-arith -pipe  -O3 -gstabs+ -fcheck-new -DUNIX_SVR4 -DUNIX -DLINUX -DMULTITHREAD
CFLAGS:=

################################
else
################################
CC := g++ -o
LIBS := -lpthread -lstdc++ -lsocket -ldl -lnsl -lgen -lposix4 -lcta -ladiapi -lnccapi -lvceapi -lswiapi -ladidtm -lcnfapi -lthread
#CFLAGS := -W -Wpointer-arith -pipe  -O3 -gstabs+ -fcheck-new -DUNIX_SVR4 -DUNIX -DLINUX -DMULTITHREAD

CFLAGS :=
endif
################################
PATHS := ../include 

######################################################
CXXFLAGS := -g $(CFLAGS) $(addprefix -I,$(PATHS))
RM-F := rm -rf
######################################################
# You shouldn't need to change anything below this point.

SOURCE := $(wildcard *.c) $(wildcard *.cpp)
OBJS := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE)))
DEPS := $(patsubst %.o,%.d,$(OBJS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)),$(DEPS))
MISSING_DEPS_SOURCES := $(wildcard $(patsubst %.d,%.c,$(MISSING_DEPS)) \
$(patsubst %.d,%.cpp,$(MISSING_DEPS)))
CPPFLAGS +=

.PHONY : everything deps objs clean veryclean rebuild

everything : $(EXECUTABLE)

deps : $(DEPS)

objs : $(OBJS)

clean :
	@$(RM-F) *.o
	@$(RM-F) *.d

veryclean: clean
	@$(RM-F) $(EXECUTABLE)

rebuild: veryclean everything

ifneq ($(MISSING_DEPS),)
$(MISSING_DEPS) :
	@$(RM-F) $(patsubst %.d,%.o,$@)
endif

-include $(DEPS)

$(EXECUTABLE) : $(OBJS)
	$(CC) $(EXECUTABLE) $(OBJS) $(LIBS)
