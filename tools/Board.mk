CFLAGS+=-isystem $(TOPDIR)/include
CFLAGS+=-I../include
CFLAGS+=-I$(TOPDIR)/arch/$(CONFIG_ARCH)/include
CFLAGS+=-I$(TOPDIR)/arch/$(CONFIG_ARCH)/$(CONFIG_ARCH_CHIP_FAMILY)

install: $(OBJS) $(MAINOBJ) 
	$(AR) rcs $(TOPDIR)/libboard.a $(OBJS)

clean:
	$(RM) $(OBJS)

