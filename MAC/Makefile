TARGET = bin2c
FILE = ../bin2c.cpp

APPNAME=bin2c
APPBUNDLE=$(APPNAME).app
APPBUNDLECONTENTS=$(APPBUNDLE)/Contents
APPBUNDLEMACOS=$(APPBUNDLECONTENTS)/MacOS
APPBUNDLERESOURCES=$(APPBUNDLECONTENTS)/Resources

appbundle: $(APPNAME) ../icons/MAC/$(APPNAME).icns
	rm -rf $(APPBUNDLE)
	mkdir $(APPBUNDLE)
	mkdir $(APPBUNDLECONTENTS)
	mkdir $(APPBUNDLEMACOS)
	mkdir $(APPBUNDLERESOURCES)
	cp Info.plist $(APPBUNDLECONTENTS)/
	cp PkgInfo $(APPBUNDLECONTENTS)/
	cp ../icons/MAC/$(APPNAME).icns $(APPBUNDLERESOURCES)/
	cp $(APPNAME) $(APPBUNDLEMACOS)/
	rm -f $(APPNAME)

$(APPNAME):
	$(CXX) -O3 -std=c++17 $(STDLIB) $(FILE) -o $(APPNAME)
test:
	rm -f ../tests/VP.hpp
	$(APPBUNDLEMACOS)/$(APPNAME) /custvar "IMAGE_VP" /nohead /infile "../tests/VP.jpg" /outfile "../tests/VP.hpp"
	$(CXX) -O3 -std=c++14 ./tests/VP.cpp -o ../tests/VP
	./tests/VP

.PHONY: clean
clean:
	rm -f ../tests/VP.hpp
	rm -f ./bin2c
	rm -rf ./bin2c.app
