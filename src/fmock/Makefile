CC ?= gcc
AR ?= ar

FMOCKOBJS = fmockimpl_call.o fmockimpl_calllog.o fmockimpl_checker.o fmockimpl_data.o fmockimpl_expect.o fmockimpl_funcrunsum.o fmockimpl_funcspec.o fmockimpl_list.o fmockimpl_result.o fmockimpl_return.o fmockimpl_test.o

$(FMOCKLIB): $(FMOCKOBJS)
	$(AR) -r $(FMOCKLIB) $(FMOCKOBJS)

DEPFILE=make.d
DEPFILE_EXIST=$(shell test -f $(DEPFILE) && echo YES)

ifeq ($(DEPFILE_EXIST),YES)
include $(DEPFILE)
endif

$(FMOCKOBJS) : %.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY : clean

clean:
	rm -f *.a *.o
