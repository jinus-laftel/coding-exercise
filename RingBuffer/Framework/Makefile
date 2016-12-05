-include ../Makefile.config

################################################################
# Local Config
################################################################
INCLUDE += -I./include

################################################################
# Target Section
################################################################
.PHONY : all clean
all : debug
debug : libFrameworkD.a
release : libFramework.a

SRCS := $(shell find src -name '*.cpp')
DEPS := $(SRCS:.cpp=.d)
DEBUG_OBJECTS := $(SRCS:.cpp=.d.o)
RELEASE_OBJECTS := $(SRCS:.cpp=.r.o)

libFrameworkD.a : $(DEBUG_OBJECTS)
	@$(AR) $(ARFLAGS) $@ $^

libFramework.a : $(RELEASE_OBJECTS)
	@$(AR) $(ARFLAGS) $@ $^

clean :
	-$(RM) libFrameworkD.a libFramework.a
	-$(RM) $(shell find src -name '*.o')
	-$(RM) $(shell find src -name '*.gcno')
	-$(RM) $(shell find src -name '*.gcda')
	-$(RM) $(shell find src -name '*.d')

-include $(DEPS)

