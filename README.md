#Sterowanie ogniwem Peltiera

Celem projektu jest wykonanie małej lodówki opartej na ogniwie Peltiera.
Lodówka będzie sterowana poprzez mikro-kontroler, którego zdaniem będzie:

    *Sterowanie ogniwa poprzez sygnał PWM dochodzący do MOSFETa.
    *Odczytywanie temperatury radiatora chłodnej strony ogniwa Peltiera, poprzez użycie termometru wspierającego protokół 1 wire.
    *Wyświetlenie na ekranie oledowym I2C aktualnej i wybranej temperatury radiatora.
    *Obsługa enkodera, oraz dwóch przycisków.
    *Sterowanie wentylatorami przymocowanymi do radiatorów ogniwa.
