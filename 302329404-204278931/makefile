all: fs

fs: bin/Commands.o bin/Environment.o bin/Files.o bin/FileSystem.o bin/Main.o
	g++ -o bin/fs bin/Commands.o bin/Environment.o bin/Files.o bin/FileSystem.o bin/Main.o
	@echo 'DONE!!!'

bin/Main.o: src/Main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Main.o src/Main.cpp

bin/Commands.o: src/Commands.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Commands.o src/Commands.cpp

bin/Environment.o: src/Environment.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Environment.o src/Environment.cpp

bin/Files.o: src/Files.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Files.o src/Files.cpp

bin/FileSystem.o: src/FileSystem.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/FileSystem.o src/FileSystem.cpp

clean:
	rm -f bin/*

test1: clean fs
	./bin/fs < output-tests/input1.txt | diff output-tests/output1.txt -
test2: clean fs
	./bin/fs < output-tests/input2.txt | diff output-tests/output2.txt -
test3: clean fs
	./bin/fs < output-tests/input3.txt | diff output-tests/output3.txt -