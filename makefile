# Nome do arquivo final
Target      = Havana_RDR2_Mod
OBJS        = main.o

# O compilador que o GitHub acabou de baixar
CC          = orbis-clang++

# Configurações de busca de arquivos (Headers e Libs)
CFLAGS      = -O3 -std=c++17 -fPIC -I$(OO_PS4_TOOLCHAIN)/include
LDFLAGS     = -shared -L$(OO_PS4_TOOLCHAIN)/lib -lSceLibKernel -lScePad -lc++

all: $(Target).prx

$(Target).prx: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(Target).prx $(OBJS)
