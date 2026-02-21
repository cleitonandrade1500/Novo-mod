Target      = RDR2_Assalto_GoldHEN
OBJS        = main.o

# Flags do OpenOrbis (C++17)
CFLAGS      = -O3 -std=c++17 -fPIC -I$(OO_PS4_TOOLCHAIN)/include
LDFLAGS     = -shared -L$(OO_PS4_TOOLCHAIN)/lib -lSceLibKernel -lScePad -lc++

all: $(Target).prx

$(Target).prx: $(OBJS)
	orbis-clang++ $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	orbis-clang++ $(CFLAGS) -c -o $@ $<
