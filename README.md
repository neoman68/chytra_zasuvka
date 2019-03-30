# Chytrá zásuvka

Systém slouží k zapínání elektrických spotřebičů v závislosti na momentálním tarifu odebírané elektrické energie. 
Tento tarif (nízký nebo vysoký, lidově řečeno "denní proud" nebo "noční proud") určuje dodavatel a to v závislosti 
na konkrétní sazbě na smlouvě o odběru. Standardně jsou spotřebiče (např. bojler nebo přímotop) připojeny přes 
stykač, který je ovládán dálkově distributorem elektrické energie pomocí kódovaných povelů, přenášených po el. síti. 

Zařízení je jednoduché. Vysílač je připojen prostřednictvím optočlenu ke stykači nebo rovnou k bojleru a hlídá,
kdy bude spotřebič sepnut, tj. kdy je možné odebírat el. energii za nízký tarif. Tuto kontrolu provádí každých
10 sekund a na základě kontroly odesílá řetězec znaků prostřednictvím RF modulu na kmitočtu 433Mhz.

Chytrá zásuvka je obvod, který využívá vlastnosti většiny praček a myček nádobí, kdy pokud během provádění programu
praní nebo mytí nádobí "vypadne" elektrický proud, tak po "náběhu" el. produ pokračuje pračka nebo myčka v programu
přesně v tom místě, kde byl v okamžiku výpadku. 

Použití je jednoduché: Standardně je chytrá zásuvka vložena mezi spotřenbič a zásuvku ve zdi. Pokud není spuštěn proces 
čekání na noční proud, je relé v klidovém stavu a chytrá zásuvka je průchozí. Program jen načítá informace od vysílače
a hlídá případný stisk tlačítka. Pokud je vysoký tarif, LED dioda jednou za cca. 10 sec. krátce blikne jako potvrzení
o přijetí dat z vysílače. V případě nízkého tarifu svítí trvale, obojí v zelené barvě (klidový stav).

Stačí tedy jen zapnout pračku nebo myčku, spustit u ní příslušný program a poté stisknout tlačítko na chytré zásuvce.

Po stisku tlačítka se rozsvítí červená LED, relé sepne, tím odpojí spotřebič od el. sítě a buzzer 3x krátce pípne. Tím 
je zařízení v tzv. čekacím stavu. Dále pravidelně načítá informace od vysílače a pokud přijatý kód obsahuje informaci 
o změně tarifu na "noční proud", relé se vypne, spotřebič se připojí k el. síti a rozsvítí se zelená LED. 

Stisk tlačítka v době, kdy běží noční proud, nemá žádný vliv, pouze buzzer 5x krátce pípne. 

Stiskem tlačítka v době, kdy je zařízení v čekacím režimu, je čekací režim zrušen a zařízení se uvede do klidového stavu.

Pro RF komunikaci byla použita tato knihovna  http://mchr3k.github.com/arduino-libs-manchester/ , kterou přikládám a RF
moduly STX882 a SRX882, které mě svým výkonem a citlivostí mile překvapily.

Vzhledem k jednoduchosti programového kódu je program komaptibilní s každým Arduinem, se kterým je komaptibilní výše uvedená 
knihovna pro RF komunuikaci. 
