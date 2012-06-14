SHELL    = /bin/sh

TOPDIR  := $(shell pwd)/..

TARGETS_DIR  = \
		$(TOPDIR)/src \

all::
	@-mkdir $(TOPDIR)/include
	@-mkdir $(TOPDIR)/bin
	@-mkdir $(TOPDIR)/lib
	@for tsubdir in $(TARGETS_DIR); \
	do \
		echo "making $${tsubdir}"; \
		( cd $${tsubdir} && $(MAKE) ) || exit 1; \
	done

clean::
	@for tsubdir in $(TARGETS_DIR); \
	do \
		echo "clean $${tsubdir}"; \
		( cd $${tsubdir} && $(MAKE) clean ) || exit 1; \
	done
