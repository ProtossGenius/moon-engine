##Tail
prebuild:
	smist -exts ".cpp,.c,.h,.hpp,.cc"
	python3 ./format
	smdcatalog	

debug:

qrun:
	cp -r ./res ./build/
	cd build && cmake .. && make -j$(nproc) && ./moon-engine
test:

install:

clean:

