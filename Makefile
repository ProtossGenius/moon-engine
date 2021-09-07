##Tail
prebuild:
	python3 ./format
	smdcatalog	

debug:

qrun:
	cp -r ./res ./build/
	cd build && cmake .. && make -j16 && ./moon-engine
test:

install:

clean:

