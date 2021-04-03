FILE = ../bin2c.cpp

APPNAME=bin2c
APPBUNDLE=$(APPNAME).app
APPBUNDLECONTENTS=$(APPBUNDLE)/Contents
APPBUNDLEMACOS=$(APPBUNDLECONTENTS)/MacOS
APPBUNDLERESOURCES=$(APPBUNDLECONTENTS)/Resources

appbundle: $(APPNAME)
	rm -rf $(APPBUNDLE)
	mkdir $(APPBUNDLE)
	mkdir $(APPBUNDLECONTENTS)
	mkdir $(APPBUNDLEMACOS)
	mkdir $(APPBUNDLERESOURCES)
	cp Info.plist $(APPBUNDLECONTENTS)/
	cp PkgInfo $(APPBUNDLECONTENTS)/
	cp ../icons/MAC/$(APPNAME).icns $(APPBUNDLERESOURCES)/
	cp wrapper $(APPBUNDLEMACOS)/
	cp $(APPNAME) $(APPBUNDLEMACOS)/
	chmod +x $(APPBUNDLEMACOS)/wrapper
	rm -f $(APPNAME)

$(APPNAME):
	$(CXX) -O3 -std=c++17 $(STDLIB) $(FILE) -o $(APPNAME)
test:
	rm -f ../tests/VP.hpp
	rm -f ./VP.jpg
	$(APPNAME) /custvar "IMAGE_VP" /nohead /infile "../tests/VP.jpg" /outfile "../tests/VP.hpp"
	$(CXX) -O3 -std=c++14 ../tests/VP.cpp -o ../tests/VP
	../tests/VP

.PHONY: clean
clean:
	rm -f ../tests/VP.hpp
	rm -f ../tests/VP
	rm -f ./VP.jpg
	rm -f $(APPNAME)
	rm -rf $(APPBUNDLE)

install: appbundle
	cp -R $(APPBUNDLE) /Applications/$(APPBUNDLE)
	ln -sv /Applications/$(APPBUNDLEMACOS)/$(APPNAME) /usr/local/bin/$(APPNAME)

uninstall:
	rm -rf /Applications/$(APPBUNDLE)
	rm -f /usr/local/bin/$(APPNAME)

symlink:
	rm -f ./$(APPNAME)
	ln -sv $(APPBUNDLEMACOS)/$(APPNAME) $(APPNAME)

dmgimage:
	mkdir dmgtmp
	cp ./dmg/install ./dmgtmp/install
	chmod +x ./dmgtmp/install
	cp ./dmg/uninstall ./dmgtmp/uninstall
	chmod +x ./dmgtmp/uninstall
	cp -R $(APPBUNDLE) ./dmgtmp/$(APPBUNDLE)
	hdiutil create ./tmp.dmg -ov -volname "$(APPNAME)" -fs HFS+ -srcfolder "./dmgtmp/"
	hdiutil convert ./tmp.dmg -format UDZO -o "./$(APPNAME) Install $(CXX).dmg"
	rm -f ./tmp.dmg
	rm -rf ./dmgtmp
