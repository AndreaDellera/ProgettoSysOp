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
	@echo "\t- \033[1minstall\033[0m: installa gli eseguibili spostandoli in /usr/bin (NB: NECESSITA DI PERMESSI DI ROOT!)"
	@echo "\t- \033[1muninstall\033[0m: elimina gli eseguibili da /usr/bin (NB: NECESSITA DI PERMESSI DI ROOT!)"
	@echo "\t- \033[1massets\033[0m: genera dei possibili file di input (di prova) dentro “assets”"
	@echo "\t- \033[1mtest\033[0m: genera i binari e gli assets e si lancia l’eseguibile per provare i file di input generati"
	@echo "\t- \033[1mclean\033[0m: elimina eventuali file temporanei, compresi binari e assets generati"
	@echo "\t- \033[1mtestAssets\033[0m: questo target permette di testare il programma con degli input di prova generati dal target assets"
	@echo "\n"
bin: clean
	mkdir bin
	gcc ./src/codecserver.c ./src/functions.c -o codecserver
	gcc ./src/codecclient.c ./src/functions.c -o codecclient
	@echo "\tAll compiled succesfully !"
	mv codecclient ./bin/
	mv codecserver ./bin/
	@echo "\tFiles copied succesfully in /bin/ !"
	@echo "\n"

install: clear bin
	#NB: need root access
	cp codecserver /usr/bin/
	cp codecclient /usr/bin/
	@echo "\tFiles copied succesfully in /usr/bin/ !"
	@echo "\n"

uninstall:	
	#NB: need root access
	rm -rf /usr/bin/codecserver
	rm -rf /usr/bin/codecclient
	@echo "\tPrograms uninstalled succesfully !"
	@echo "\n"

assets: clean bin 
	mkdir assets
	echo TestoDelMessaggio > assets1.txt
	echo TestoDiProvaDiClientEDelServer > assets2.txt
	cp assets1.txt ./bin
	cp assets2.txt ./bin
	mv assets1.txt ./assets
	mv assets2.txt ./assets

testAssets: bin 
	cd bin && ./codecserver -n testServer -m 1 -M 15 -t 100 &
	cd bin && ./codecclient -n testServer -k ciao -f assets1.txt -e -o assets1_encoded.txt
	cd bin && ./codecclient -n testServer -k ciao -f assets2.txt -e -o assets2_encoded.txt
	cd bin && cat assets1_encoded.txt
	cd bin && cat assets2_encoded.txt

test: bin
	cd bin && ./codecserver -n testServer -m 1 -M 15 -t 100 &
	cd bin && ./codecclient -n testServer -k ciao -m TestoDelMessaggio -e -o text_encoded.txt
	cd bin && cat text_encoded.txt

clean:
	rm -rf ./bin/
	rm -rf ./assets/ 
	@echo "\tClean succesfully !"
	@echo "\n"
