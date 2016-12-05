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
debug : FrameworkTestD
release : FrameworkTest

SRCS := $(shell find src -name '*.cpp')
DEPS := $(SRCS:.cpp=.d)
DEBUG_OBJECTS := $(SRCS:.cpp=.d.o)
RELEASE_OBJECTS := $(SRCS:.cpp=.r.o)

ifeq ($(OS), Linux)
DEBUG_LIBS := -pthread -L. -lgtestLinux
RELEASE_LIBS := -pthread -L. -lgtestLinux
#DEBUG_LIBS := -pthread -lFrameworkD -L. -lgtestLinux
#RELEASE_LIBS := -pthread -lFramework -L. -lgtestLinux
endif

ifeq ($(OS), Darwin)
DEBUG_LIBS := -L. -lgtestOSX
RELEASE_LIBS := -L. -lgtestOSX
#DEBUG_LIBS := -lFrameworkD -L. -lgtestOSX
#RELEASE_LIBS := -lFramework -L. -lgtestOSX
endif

FrameworkTestD : $(DEBUG_OBJECTS)
	@$(CXX) $(CXXFLAGS) -O0 -g -o $@ $^ $(DEBUG_LIBS)

FrameworkTest : $(RELEASE_OBJECTS)
	@$(CXX) $(CXXFLAGS) -O3 -o $@ $^ $(RELEASE_LIBS)

clean :
	-$(RM) FrameworkTestD FrameworkTest
	-$(RM) $(shell find src -name '*.o')
	-$(RM) $(shell find src -name '*.gcno')
	-$(RM) $(shell find src -name '*.gcda')
	-$(RM) $(shell find src -name '*.d')

-include $(DEPS)

