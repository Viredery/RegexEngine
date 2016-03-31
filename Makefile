RegEn: main.o Judge.o DFA.o NFA.o RE_tree.o
	g++ -o RegEn main.o Judge.o DFA.o NFA.o RE_tree.o
main.o: src/main.cpp
	g++ -c src/main.cpp
Judge.o: src/Judge.cpp src/Judge.h
	g++ -c src/Judge.cpp
DFA.o: src/DFA.cpp src/DFA.h
	g++ -c src/DFA.cpp
NFA.o: src/NFA.cpp src/NFA.h
	g++ -c src/NFA.cpp
RE_tree.o: src/RE_tree.cpp src/RE_tree.h
	g++ -c src/RE_tree.cpp
clean:
	rm -f main.o Judge.o DFA.o NFA.o RE_tree.o
