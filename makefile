Target      = Havana_RDR2_Mod
OBJS        = main.o

LIBS        = -lSceLibKernel -lScePad
CFLAGS      = -O3 -std=c++17 -fPIC -I$(OO_PS4_TOOLCHAIN)/include
LDFLAGS     = -shared -L$(OO_PS4_TOOLCHAIN)/lib $(LIBS)

all: $(Target).prx

$(Target).prx: $(OBJS)
	orbis-clang++ $(CFLAGS) $(LDFLAGS) -o $@ $^
