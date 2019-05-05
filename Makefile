PACKAGE_NAME?=zigmann-sorin_lecteur-redacteur

BASEDIR=$(shell pwd)
SRCDIR=$(BASEDIR)/src
DISTDIR=$(BASEDIR)/dist
PUBDIR=$(BASEDIR)/pub

PROGS=fifo prio_l prio_r
.PHONY: all clean pub dist pub_clean dist_clean fifo priority_lecteur priority_redacteur


all: $(PROGS)

clean: dist_clean pub_clean
	@cd src ;\
	make clean ;\
	cd ..

pub: clean
	@mkdir -p $(PUBDIR)/$(PACKAGE_NAME) ;\
	echo "Copying files to $(PUBDIR)/$(PACKAGE_NAME)" ;\
	cp -r src Makefile docs/cr.pdf $(PUBDIR)/$(PACKAGE_NAME) ;\
	cd $(PUBDIR) ;\
	echo "Creating archive $(PACKAGE_NAME).tar.gz" ;\
	tar -czf $(PACKAGE_NAME).tar.gz $(PACKAGE_NAME) ;\
	cd ..

pub_clean:
	rm -rf $(PUBDIR)

dist: 
	@mkdir -p $(DISTDIR) ;\
	cd src ;\
	mkdir -p dist ;\
	make dist ;\
	echo "Copying files to $(DISTDIR)" ;\
	cp dist/* $(DISTDIR) ;\
	cd .. ;

dist_clean:
	rm -rf $(DISTDIR)

fifo:
	@cd src ;\
	make fifo ;\
	cd ..
prio_r:
	@cd src ;\
	make  prio_r ;\
	cd ..
prio_l:
	@cd src ;\
	make  prio_l ;\
	cd ..
