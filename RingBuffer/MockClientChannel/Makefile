-include ../Makefile.config

################################################################
# Local Config
################################################################
INCLUDE += -I./include -I../Framework/include

OS := $(shell uname)

################################################################
# Target Section
################################################################
.PHONY : all clean
all : debug
debug : MockClientChannelServerD
release : MockClientChannelServer

SRCS := $(shell find src -name '*.cpp')
DEPS := $(SRCS:.cpp=.d)
DEBUG_OBJECTS := $(SRCS:.cpp=.d.o)
RELEASE_OBJECTS := $(SRCS:.cpp=.r.o)

ifeq ($(OS), Linux)
DEBUG_LIBS := -pthread -L.
RELEASE_LIBS := -pthread -L.
#DEBUG_LIBS := -pthread -lFrameworkD -L.
#RELEASE_LIBS := -pthread -lFramework -L.
endif

ifeq ($(OS), Darwin)
DEBUG_LIBS := -L.
RELEASE_LIBS := -L.
#DEBUG_LIBS := -lFrameworkD -L.
#RELEASE_LIBS := -lFramework -L.
endif

MockClientChannelServerD : $(DEBUG_OBJECTS)
	@$(CXX) $(CXXFLAGS) -O0 -g -o $@ $^ $(DEBUG_LIBS)

MockClientChannelServer : $(RELEASE_OBJECTS)
	@$(CXX) $(CXXFLAGS) -O3 -o $@ $^ $(RELEASE_LIBS)

clean :
	-$(RM) MockClientChannelServerD MockClientChannelServer
	-$(RM) $(shell find src -name '*.o')
	-$(RM) $(shell find src -name '*.gcno')
	-$(RM) $(shell find src -name '*.gcda')
	-$(RM) $(shell find src -name '*.d')

-include $(DEPS)

