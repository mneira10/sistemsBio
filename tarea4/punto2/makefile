proteins.png rnas.png: t.dat rdat p.dat
	python graph.py

t.dat r.dat p.dat: punto2.x
	./punto2.x
punto2.x: punto2.cpp
	g++ punto2.cpp -o punto2.x

clean:
	rm *.x
	rm *.dat
	rm *.png