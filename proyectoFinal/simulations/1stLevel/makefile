1stLevel.png: 1stLevel.dat
	python graph.py

1stLevel.dat: simulate.x
	./simulate.x

simulate.x:	
	g++ simulate.cpp -o simulate.x

clean: 
	rm *.x
	rm *.dat
	rm *.pdf