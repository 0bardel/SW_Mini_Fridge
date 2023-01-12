# Sterowanie ogniwem Peltiera

Celem projektu jest wykonanie małej lodówki opartej na ogniwie Peltiera.
Lodówka będzie sterowana poprzez mikro-kontroler STM32F401, którego zadaniem będzie:
* Sterowanie ogniwa poprzez sygnał PWM dochodzący do MOSFETa.
* Odczytywanie temperatury radiatora chłodnej strony ogniwa Peltiera, poprzez użycie termometru wspierającego protokół 1 wire.
* Wyświetlenie na ekranie oledowym I2C aktualnej i wybranej temperatury radiatora.
* Obsługa enkodera, oraz dwóch przycisków.
* Sterowanie wentylatorami przymocowanymi do radiatorów ogniwa.

## Użyte materiały:

* https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf
* https://github.com/afiskon/stm32-ssd1306
* https://www.st.com/en/development-tools/stm32cubemx.html
* https://www.st.com/resource/en/reference_manual/dm00096844-stm32f401xb-c-and-stm32f401xd-e-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf
* https://github.com/MaJerle/lwow


