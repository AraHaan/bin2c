FSFLAG = -lstdc++fs
TARGET = bin2c
FILE = bin2c.cpp

$(TARGET):
	$(CXX) -O3 -std=c++14 $(FILE) $(FSFLAG) -o $(TARGET)
test:
	rm -f ./tests/VP.hpp
	./bin2c /custvar "IMAGE_VP" /nohead /infile "./tests/VP.jpg" /outfile "./tests/VP.hpp"
	$(CXX) -O3 -std=c++14 ./tests/VP.cpp -o ./tests/VP
	./tests/VP

.PHONY: clean
clean:
	rm -f ./tests/VP.hpp
	rm -f ./bin2c
