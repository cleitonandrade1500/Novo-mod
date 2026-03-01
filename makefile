ifndef OO_PS4_TOOLCHAIN
    $(error OO_PS4_TOOLCHAIN is not set)
endif

target := ps4_plugin
NAME := JohnBodyguard
OUTDIR := $(shell pwd)
ID     := RDR2_JOHN_2026
CONTENT_ID := UP4139-CUSA03041_00-0000000000000000

# Adicionado lstdc++ para evitar erros de compilação de thread/chrono
libraries := -lSceLibKernel -lSceNet -lScePad -lstdc++ -lm

include $(OO_PS4_TOOLCHAIN)/scripts/ext.mk

CFLAGS += -O2 -std=c11
CXXFLAGS += -O2 -std=c++11

$(NAME).prx: $(NAME).elf
	$(ORBIS_OBJCOPY) --strip-unneeded -O binary $< $@

include $(OO_PS4_TOOLCHAIN)/scripts/target.mk
