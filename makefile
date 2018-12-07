plagiarismChecker: plagiarismChecker.o
	g++ -o plagiarismChecker plagiarismChecker.o

plagiarismChecker.o: plagiarismChecker.cpp
	g++ -c plagiarismChecker.cpp

