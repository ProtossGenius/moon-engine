##Tail
prebuild:
	python3 ./format
	smdcatalog	

debug:

qrun:
	cd build && cmake .. && make -j16 && gdb moon-engine
test:

install:

clean:

