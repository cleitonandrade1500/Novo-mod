Target      = RDR2_Mod_2026
OBJS        = main.o
LIBS        = -lSceLibKernel -lScePad -lc++

CFLAGS      = -O3 -std=c++17 -fPIC -I$(OO_PS4_TOOLCHAIN)/include
LDFLAGS     = -shared -L$(OO_PS4_TOOLCHAIN)/lib $(LIBS)

all: $(Target).prx

$(Target).prx: $(OBJS)
	orbis-clang++ $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	orbis-clang++ $(CFLAGS) -c -o $@ $<
