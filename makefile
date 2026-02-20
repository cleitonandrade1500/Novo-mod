Target      = RDR2_BankMod
OBJS        = main.o
CC          = orbis-clang++

CFLAGS      = -O3 -std=c++17 -fPIC -I$(OO_PS4_TOOLCHAIN)/include
LDFLAGS     = -shared -L$(OO_PS4_TOOLCHAIN)/lib -lSceLibKernel -lScePad -lc++

all: $(Target).prx

$(Target).prx: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
