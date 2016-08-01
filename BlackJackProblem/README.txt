#############################################################
Informationen zum Sequenzenerzeuger
by Jens Wöhrle;		01.08.2016
#############################################################
1. Allgemeines
2. Die einzelnen Klassen
3. Konfiguration
4. Anmerkungen
#############################################################

1. Allgemeines:
Das Programm wurde in Zusammenhang mit der Bachelorarbeit "Kartenkombinationen" im Blackjack entwickelt
und kann Kartenkombinationen berechnen mit denen die Bank gegen alle Spieler gewinnt. Hierbei ist das Programm sehr flexibel anpassbar.
Die zehn verschiedenen Werte der Karten werden als Integer von 1 bis 10 dargestellt. Das Ass wird durch eine "1" abgebildet.
Für eine erfolgreiche Vernwedung und Konfiguration des Programms, wird das Wissen aus der Bachelorarbeit vorausgesetzt.

___________________________________________________________________________________________________

2. Die einzelnen Klassen
Es exisiteren die beiden Klassen "FillUp", sowie "SequenzCreator"
	SequenzCreator(n):
	Die Klasse erzeugt die in der Arbeit beschriebenen Sequenzen S.
	Der Parameter "n" ist der Wert der Summenfolge, der ab jedem Einstiegspunkt erreicht wird.
	Es werden alle Karten in S - also auch einen der Teil der Karten in B - gesetzt.
	Alle Sequenzen werden in Dateien "SolutionSequenz" in das Verzeichnis PATH geschrieben.
	**** Parameter:
		* n - Wert, den die Summen erreichen. Falls es so konfiguriert ist, dass die Bank ein Ass bekommt, 
		* so können die Summen auch den Wert (n+10) erreichen

	FillUp(sc, n):
	Diese Klasse nimmt die Sequenzen des Sequenzenerzeugers und füllt die freien Karten F auf. 
	Davor werden auch noch die verbleibenden Karten in B gesetzt.
	Falls das Erfüllen erfolgreich war, so werden die Lösungen in eine Datei "SolutionFinal" im Verzeichnis PATH geschrieben
	**** Parameter:
		* sc - Pointer zum SequnezenCreator zur Übergabe der gefunden Sequenzen
		* n - Werte der Summenfolge, sodass die Bank (21-n) als Startpunktzahl bekommen muss

___________________________________________________________________________________________________

3. Konfiguration
	Um eigene Szenarien selbst konfigurieren zu können, sind Änderungen in 
		Config.h
		Fullup.cpp
	notwendig.
	Die Karten wurden hier von 0 bis NumCards-1 in ihrer entsprechenden Position nach ihrer Zahl benannt.

	Config.h
		Die meisten Einstellungen werden in der Datei Config.h vorgenommen. 
		Für jedes Szenario ist zunächst ein Szenarioname zu definieren, beziehungsweise der aktuell definierte Name bestimmt die Konfiguration.
		Es darf nie mehr als ein Szenarioname definiert sein.
		Bereits entwickelte Szenarien sind "T_4567", "T_567", "T_467" und "T_67". Das Szenario gibt an, gegen welche Anzahl an Spielern die Konfiguration gültig sein soll.
		Für jedes Szenario müssen nun unter der Bedingung, dass das entsprechende Szenario definiert wurde(#ifdef), einzelne Paramter definiert werden:
			* F - Die Anzahl an freien Karten (F geschnitten nicht B)
			* Bank1, Bank2, Bank3 - Die Karten in der Sequenz und in B (S geschnitten B). Sollten weniger als 3 Karten in dieser Menge sein, 
				so muss den Variablen der gleiche Wert zugewiesen werden.
			* Manual1, Manual2 - Die beiden Karten, die in B, aber nicht in F sind.
			* SeqStart - Die erste Karte, ab welcher die Sequenz S erzeugt werden soll.

		Darüner hinaus gibt es ein paar allgemeine Paramter, die nicht vom Szenario abhängig sind:
			* NumCards - Länge der zu erzeugenden Lösung. Die Sequenz S hat entsprechend die Länge NumCards - SeqStart
			* Ass - falls 1, dann besitzt die Bank garantiert ein Ass, fall 0 nicht
			* MEASURE - falls 1 werden ein paar statistische Informationen zur Ausführung des Algorithmus gesammelt, falls 0 nicht
			* PATH - Pfad in dem die Ergebnisse gespeichert werden sollen

	FillUp.cpp
		Darüber hinaus ist es notwendig an zwei Stellen für das neue Szenario Code einzufügen. 
		*	An der ersten Stelle muss eine Abbildung erzeugt werden, die die Zahlen [0,F-1] auf die F Positionen der freien Karten in der Lösung abbildet. 
			Im Fall von N={4,5,6,7} wäre dies: 0 -> 0; 1 -> 1; 2 -> 2; 3 -> 3; 4 -> 8
		*	An der zweiten Stelle muss spezifiziert werden, für welche n die Kombination überprüft werden muss. 

	Wurden diese Einstellungen getroffen, so muss das Programm lediglich erstellt und ausgeführt werden.


___________________________________________________________________________________________________

4. Anmerkungen:
* 	Es wurde hier die umständlichere Variante über Makros verwendet, da dadurch die Konfiguration bereits in der Compilezeit und nicht erst in der Laufzeit definiert wird, wodurch weniger Sprünge im Code entstehen. Dies kann sich positiv auf die Laufzeit auswirken.
*	Das Programm wurde nicht parallelsiert und läuft lediglich auf einem Prozessor. Es ist zu wichtig zu wissen, dass die Anzahl an Kernen nicht der Anzahl an logischen Prozessoren entspricht. In der Regel teilen die aktuellen Betriebssystem jeden Kern in zwei logische Prozessoren auf. Das bedeutet, dass bei einem Prozessor mit 4 Kernen diese in 8 logische Prozessoren vom Betriebssystem aufgeteilt werden und das Programm nur auf einen dieser läuft. Die aktuellen Betriebssysteme versuchen jedoch eigene Paralleliserungsverfahren anzuwenden, sodass die CPU-Auslastung auch etwas (ca. +5%)über 12,5% ansteigen kann. 










