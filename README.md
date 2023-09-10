# V2.0-vektorius
Objektinio programavimo laboratorinis darbas - 2-oji užduotis.

Programa, skirta studentų galutinio balo skaičiavimui.




### std::vector ir class Vector konteinerių pildymo spartos lentelė: <br>
|                             **Konteinerio dydis** | **10.000** | **100.000** | **1.000.000** | **10.000.000** | **100.000.000** |
|--------------------------------------------------:|------------|-------------|---------------|----------------|-----------------|
| _std::vector (laikas, s)_                         | 0.001      | 0.001       | 0.004         | 0.052          | 0.523           |
| _class Vector (laikas, s)_                        | 0.000      | 0.001       | 0.004         | 0.031          | 0.302           |

### Atminties perskirstymai užpildant 100.000.000 elementų: <br>
|                                 | **Atminties perskirstymai** |
|--------------------------------:|-----------------------------|
| std::vector                   | 28                          |
| class Vector                  | 9                           |

### Programos veikimo spartos lentelė naudojant *std::vector*: <br>

|                               **Studentų kiekis** | **100.000** | **1.000.000** | **10.000.000** |
|--------------------------------------------------:|-------------|---------------|----------------|
| _Skaitymas iš failo (laikas, s)_                  | 0.213       | 2.124         | 21.566         |
| _Studentų rūšiavimas į dvi grupes (laikas, s)_    | 0.010       | 0.053         | 0.529          |
| _Studentų rūšiavimas didėjimo tvarka (laikas, s)_ | 0.064       | 0.809         | 9.734          |
| _Visas programos darbas (laikas, s)_ 	            | 0.388       | 3.894         | 40.939         |

### Programos veikimo spartos lentelė naudojant *class Vector*: <br>

|                               **Studentų kiekis** | **100.000** | **1.000.000** | **10.000.000** |
|--------------------------------------------------:|-------------|---------------|----------------|
| _Skaitymas iš failo (laikas, s)_                  | 0.186       | 1.885         | 18.611         |
| _Studentų rūšiavimas į dvi grupes (laikas, s)_    | 0.020       | 0.151         | 1.526          |
| _Studentų rūšiavimas didėjimo tvarka (laikas, s)_ | 0.047       | 0.576         | 6.912          |
| _Visas programos darbas (laikas, s)_ 	            | 0.356       | 3.528         | 36.462         |
