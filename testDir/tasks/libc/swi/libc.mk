# @file libc.mk
#
# @ Authors: Sara Roy <slroy@andrew.cmu.edu>
# @          Samantha Klonaris <sklonari@andrew.cmu.edu>
# @	      Derek Miller <damiller@andrew.cmu.edu>
# @ Date: 11/4/12

# Added swi_handler object
TLIBC_SWI_OBJS := swi_handler.o exit.o read.o write.o time.o sleep.o

TLIBC_SWI_OBJS := $(TLIBC_SWI_OBJS:%=$(TLIBCDIR)/swi/%)
TLIBC_OBJS += $(TLIBC_SWI_OBJS)
