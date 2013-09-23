# Non-volatile memory simulator
# Pre-release version, r131

target := nvsim

# define tool chain
CXX := g++
RM := rm -f

# define build options
# compile options
CXXFLAGS := -Wall
# link options
LDFLAGS :=
# link librarires
LDLIBS :=

# construct list of .cpp and their corresponding .o and .d files
SRC := $(wildcard *.cpp)
INC := 
DBG :=
OBJ := $(SRC:.cpp=.o)
DEP := Makefile.dep

# file disambiguity is achieved via the .PHONY directive
.PHONY : all clean dbg

all : $(target)

dbg: DBG += -ggdb -g
dbg: $(target)

$(target) : $(OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean :
	$(RM) $(target) $(dep_file) $(OBJ)

.cpp.o :
	$(CXX) $(CXXFLAGS) $(DBG) $(INC) -c $< -o $@

depend $(DEP):
	@echo Makefile - creating dependencies for: $(SRC)
	@$(RM) $(DEP)
	@$(CXX) -E -MM $(INC) $(SRC) >> $(DEP)

ifeq (,$(findstring clean,$(MAKECMDGOALS)))
-include $(DEP)
endif
