# Andrea Dellera 158365
# Gianluca Bortoli 159993
# 
# Progetto 1
# Anno accademico 2013/2014

all:
	@echo "\n"
	@echo "Sistema client/server per codifica­ e decodifica di testo tramite traslitterazione sull’alfabeto inglese"
	@echo "\n"
	@echo "Targets possibili:"
	@echo "\t- \033[1mbin\033[0m: genera i binari compilati eseguibili dentro “bin” che contiene i soli file oggetto eseguibili" #il \033[1m "some_text" \033[0m mette in bold il testo
	@echo "\t- \033[1massets\033[0m: genera dei possibili file di input (di prova) dentro “assets”"
	@echo "\t- \033[1mtest\033[0m: genera i binari e gli assets e si lancia l’eseguibile per provare i file di input generati"
	@echo "\t- \033[1mclean\033[0m: elimina eventuali file temporanei, compresi binari e assets generati"
	@echo "\n"
bin: clean
	mkdir bin
	gcc ./src/codecserver.c ./src/functions.c -o codecserver
	gcc ./src/server.c ./src/functions.c -o server
	gcc ./src/codecclient.c -o codecclient
	gcc ./src/client.c -o client
	@echo "\tAll compiled succesfully !"

install: clear bin
	cp codecserver /usr/bin/
	cp codecclient /usr/bin/
	cp server /usr/bin/
	cp client /usr/bin/
	@echo "\tFile copied succesfully in /usr/bin/ !"
	@echo "\n"

assets:
	#con un target “assets” (make assets) si devono poter generare dei possibili file di 
	#input (di prova) dentro una cartella da crearsi automaticamente denominata 
	#“assets” (cioè se il progetto può lavorare su dei file di input, questa direttiva ne 
	#genera un set utilizzabile)  

test:
	#con un target “test” (make test) si generano i binari e gli assets e si lancia 
	#l’eseguibile utile a provare i file di input generati 

clean:
	rm -rf ./bin/
	@echo "\tClean succesfully !"
	@echo "\n"