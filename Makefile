
MAKE = make
PRJDIR = $(PWD)

PRJ_INCDIR = $(PRJDIR)/include
PRJ_SRCDIR = $(PRJDIR)/src
PRJ_LIBDIR = $(PRJDIR)/lib

CFLAGS += -I$(PRJ_INCDIR)
CFLAGS += -g -rdynamic

export CFLAGS

FMOCK_SRCDIR = $(PRJ_SRCDIR)/fmock

FMOCKLIB = fmock.a

export FMOCKLIB

FMOCK:
	@echo building fmock lib
	$(MAKE) -C $(FMOCK_SRCDIR) -f Make.dep ; \
	$(MAKE) -C $(FMOCK_SRCDIR) ; \
	ln -s $(FMOCK_SRCDIR)/$(FMOCKLIB) $(PRJ_LIBDIR)/$(FMOCKLIB)

.PHONY: clean
clean:
	@echo clean up
	cd $(FMOCK_SRCDIR); $(MAKE) clean; $(MAKE) clean -f Make.dep; \
	rm -f $(PRJ_LIBDIR)/$(FMOCKLIB)
