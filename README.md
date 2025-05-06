# STM32 Nucleo-L073RZ su DHT11 ir SSD1306

Šis projektas skirtas STM32 Nucleo-L073RZ plokštei. Jame naudojami:

- 2x **DHT11**  drėgmės jutikliai
- 1x **SSD1306** OLED ekranas (I2C)
  
## Prijungimo schema

| Komponentas     | Prijungimo taškai     |
|-----------------|------------------------|
| DHT11 #1        | PA6                    |
| DHT11 #2        | PA7                    |
| SSD1306 (I2C)   | PB8 (SCL), PB9 (SDA)   |

> Pastaba: Jutikliai naudoja 3.3V arba 5V maitinimą (priklausomai nuo versijos). Prijunk GND ir VCC atitinkamai.

## Funkcionalumas

- Nuskaityti duomenis iš **dviejų DHT11** jutiklių
- Atvaizduoti **drėgmę** OLED ekrane
- Išvestis atnaujinama periodiškai kas 10s
- Duomenys perduodami į kompiuterį per UART
## Naudojamos bibliotekos

- CubeMX sugeneruotas kodas
- SSD1306 biblioteka STM32 mikrokontroleriams
- DHT11 biblioteka STM32 mikrokontroleriams


