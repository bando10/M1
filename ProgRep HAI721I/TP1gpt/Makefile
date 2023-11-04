########################################
#~ définitions
########################################

# Executables à générer
BIN=bin/Pi  bin/Pconfig  bin/pi bin/pcon

# liste des fichiers sources 
SRCS0=Pi.c
SRCS1=Pconfig.c
SRCS2=pi.c
SRCS3=pcon.c

default: $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.c
	gcc -Wall -Iinclude -c $< -o $@

bin/Pi: $(SRCS0:%.c=obj/%.o)
	gcc -o $@ $+

bin/Pconfig: $(SRCS1:%.c=obj/%.o)
	gcc -o $@ $+

bin/pi: $(SRCS2:%.c=obj/%.o)
	gcc -o $@ $+

bin/pcon: $(SRCS3:%.c=obj/%.o)
	gcc -o $@ $+

clean:
	rm -f $(BIN) obj/*.o *~
