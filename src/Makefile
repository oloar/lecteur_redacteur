.PHONY: all clean dist prio_l prio_r fifo prio_l_clean prio_r_clean fifo_clean prio_l_dist prio_r_dist fifo_dist dist_clean
all: prio_l prio_r fifo

clean: prio_l_clean prio_r_clean fifo_clean dist_clean

dist: prio_l_dist prio_r_dist fifo_dist

prio_l_dist:
	@cd priorite_lecteur ;\
	make dist ;\
	cd ..

prio_r_dist:
	@cd priorite_redacteur ;\
	make dist ;\
	cd ..

fifo_dist:
	@cd fifo ;\
	make dist ;\
	cd ..

prio_l:
	@cd priorite_lecteur ;\
	make ;\
	cd ..

prio_r:
	@cd priorite_redacteur ;\
	make ;\
	cd ..

fifo:
	@cd fifo ;\
	make ;\
	cd ..

prio_l_clean:
	@cd priorite_lecteur ;\
	make clean ;\
	cd ..

prio_r_clean:
	@cd priorite_redacteur ;\
	make clean ;\
	cd ..

fifo_clean:
	@cd fifo ;\
	make clean ;\
	cd ..

dist_clean:
	rm -rf dist
