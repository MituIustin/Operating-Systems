

# Pentru rulare:

```sh-session
gcc hello.c -o hello
```

```sh-session
./hello
```

# Comenzi de baza in terminalul Linux:
	
	man command 	-	manualul de utilizare
	pwd		- 	directorul curent
	ls 		-	continutul directorului curent
	cp src tgt	- 	copiere fisiere
	mv src tgt	- 	mutare fisiere
	rm item 	- 	stergere fisiere
	mkdir dir 	-	creare director
	rmdir dir 	-	stergere director gol
	echo str 	-	repetare string
	cd path 	-	schimba directorul curent


	. 		-	directorul curent
	.. 		-	directorul parinte
	cmd > file 	-	redirectionare iesire catre fisier


	strace (strace ./hello)		- 	ne arata functiile de sistem (syscalls)
						necesare pentru a se executa executabilul
						(ktrace + kdump)
				
	ldd (ldd ./hello)		-	ne arata ce biblioteci sunt necesare pentru a executa
						fisierul executabil
						
	nm (nm ./hello)			-	simbolurile folosite de hello.c
	
	
# Pentru GDB
	
```sh_session
gcc -g -O0 hello.c -o hello
```


```sh-session	
gdb ./hello
```
	
	
	b symbol 	-	oprirea executiei la simbol
	p var 		-	tipareste valoarea variabilei
	n 		-	urmatoarea instructiune
	c 		-	continuarea executiei
	q 		-	iesire

	
			
	
