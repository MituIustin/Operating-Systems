# Ex 1 

Compilati un kernel nou.


Pentru a se compila un kernel nou se executa urmatoarele comenzi:

```ssh-session
cd /sys/arch/$(machine)/compile/GENERIC.MP

make obj

make config

make

make install

reboot
```

# Ex 2

Adaugati o functie de sistem noua simpla care sa afiseze ceva pe ecran si
demonstrati ca merge apeland-o dintr-un program. Exemplu apel
syscall(id_functie, "world"). 
Atentie, trebuie sa recompilati kernelul si sa reporniti sistemul de operare cu kernelul nou!


## pas 1: Declararea

modificam fisierul /sys/kern/syscalls.master adaugand :

```c
331   STD      { int sys_khello(const char *msg); }
```

apoi apelam comanda :

```ssh_session
cd/sys/kern && make syscalls
```
pentru a regenera fisierele aferente 

  - /sys/kern/syscalls.c
  - /sys/sys/syscallargs.h
  - /sys/sys/syscall.h

## pas 2 : Definirea 

modificam fisierul /sys/kern/sys_generic.c adaugand :

```c
int sys_khello(struct proc *p, void *v, register_t *retval)
{
    struct sys_khello *uap = v;
    char *kermessage = (char*) malloc(100, M_TEMP, M_WAITOK);
    copyinstr(SCARG(uap, msg), kermessage, 100, NULL);
    printf("%s\n", kermessage);
    free(kermessage, M_TEMP, 100);
    return 0;
}
```

## pas 3 : Recompilam kernelul 

pentru acest pas se vor executa comenzile de la ex. 1

## pas 4 : Scriem un program ca sa apeleze functia

de exemplu : 

ex2.c 

![Alt text](https://raw.githubusercontent.com/MituIustin/Operating-Systems/main/Lab%203/ex2.PNG)

## pas 5 : Generam executabilul

```ssh-session
cc ex2.c -o ex2
```

## pas 6 : Apelam executabilul

```ssh-session
./ex2
```



# Ex 3

Modificati functia de sistem de mai devreme sa copieze un numar dat de
bytes dintr-un buffer sursa intr-altul destinatie. La iesire, functia va scrie
numarul de bytes copiat efectiv. Verificati intrarile primite si semnalati
eventualele erori.




## pas 1: Declararea

modificam fisierul /sys/kern/syscalls.master adaugand :

```c
332   STD      { ssize_t sys_copy(const void *src, void *dst, const size_t n); }
```

apoi apelam comanda :

```ssh_session
cd/sys/kern && make syscalls
```
pentru a regenera fisierele aferente 

  - /sys/kern/syscalls.c
  - /sys/sys/syscallargs.h
  - /sys/sys/syscall.h

## pas 2 : Definirea 

modificam fisierul /sys/kern/sys_generic.c adaugand :

![Alt text](https://raw.githubusercontent.com/MituIustin/Operating-Systems/main/Lab%203/img2.PNG)
![Alt text](https://raw.githubusercontent.com/MituIustin/Operating-Systems/main/Lab%203/img3.PNG)

## pas 3 : Recompilam kernelul 

pentru acest pas se vor executa comenzile de la ex. 1

## pas 4 : Scriem un program ca sa apeleze functia

de exemplu : 

ex3.c 

![Alt text](https://raw.githubusercontent.com/MituIustin/Operating-Systems/main/Lab%203/ex3.PNG)

## pas 5 : Generam executabilul

```ssh-session
cc ex3.c -o ex3
```

## pas 6 : Apelam executabilul

```ssh-session
./ex3
```












