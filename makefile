ifndef OO_PS4_TOOLCHAIN
    $(error OO_PS4_TOOLCHAIN is not set)
endif

target := ps4_plugin
# Nome do arquivo final que você vai baixar
NAME := JohnBodyguard
OUTDIR := $(shell pwd)
ID     := RDR2_JOHN_MOD
CONTENT_ID := UP4139-CUSA03041_00-0000000000000000

# Bibliotecas de sistema necessárias
libraries := -lSceLibKernel -lSceNet -lScePad

# Flags de compilação para C++
CFLAGS += -O2 -std=c++11 -Wno-unused-variable
CXXFLAGS += -O2 -std=c++11

include $(OO_PS4_TOOLCHAIN)/scripts/ext.mk

# Regra para converter o ELF gerado em PRX
$(NAME).prx: $(NAME).elf
	$(ORBIS_OBJCOPY) --strip-unneeded -O binary $< $@

include $(OO_PS4_TOOLCHAIN)/scripts/target.mk
