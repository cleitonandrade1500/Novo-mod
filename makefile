# Nome do arquivo final
Target      = Havana_RDR2_Mod
OBJS        = main.o

# O compilador (o GitHub Actions vai achar o binário no PATH)
CC          = orbis-clang++

# Configurações de busca de arquivos
CFLAGS      = -O3 -std=c++17 -fPIC -I$(OO_PS4_TOOLCHAIN)/include
LDFLAGS     = -shared -L$(OO_PS4_TOOLCHAIN)/lib -lSceLibKernel -lScePad -lc++

all: $(Target).prx

$(Target).prx: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Regra de compilação do objeto
main.o: main.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(Target).prx $(OBJS)
