all:
	@echo "\n"
	@echo "Sistema client/server per codifica­ e decodifica di testo tramite traslitterazione sull’alfabeto inglese"
	@echo "\n"
	@echo "Targets possibili:"
	@echo "\t- \033[1mbin\033[0m: genera i binari compilati eseguibili dentro “bin” che contiene i soli file oggetto eseguibili"
	@echo "\t- \033[1massets\033[0m: genera dei possibili file di input (di prova) dentro “assets”"
	@echo "\t- \033[1mtest\033[0m: genera i binari e gli assets e si lancia l’eseguibile per provare i file di input generati"
	@echo "\t- \033[1mclean\033[0m: elimina eventuali file temporanei, compresi binari e assets generati"
	@echo "\n"
bin:
	#con un target “bin” (make bin) si devono generare i binari compilati eseguibili 
	#dentro una cartella da crearsi automaticamente denominata “bin” che conterrà i 
	#soli file oggetto eseguibili

assets:
	#con un target “assets” (make assets) si devono poter generare dei possibili file di 
	#input (di prova) dentro una cartella da crearsi automaticamente denominata 
	#“assets” (cioè se il progetto può lavorare su dei file di input, questa direttiva ne 
	#genera un set utilizzabile)  

test:
	#con un target “test” (make test) si generano i binari e gli assets e si lancia 
	#l’eseguibile utile a provare i file di input generati 

clean:
	#con un target “clean” si eliminano eventuali file temporanei, binari e assets 
	#generati (questa regola deve essere sempre richiamata automaticamente dalle 
	#altre)