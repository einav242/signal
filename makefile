
main: main.o 
	gcc -o main main.o 

main.o: main.c  
	gcc  -c main.c

temp: temp.o 
	gcc -o temp temp.o 

temp.o: temp.c  
	gcc  -c temp.c

.PHONY: clean
	
clean:
	rm -f *.o  main temp 