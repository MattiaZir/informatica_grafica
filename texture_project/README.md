# Progetto di Informatica Grafica

## About
Mattia Zirpoli
Mat. 874950
2023/2024

## Descrizione
Questo progetto riguarda l'applicazione di texture in un contesto di grafica informatica.
L'obiettivo è dimostrare l'uso di Perlin Noise per generare texture procedurali e usare il bump mapping per
dargli profondità.


## Comandi della Tastiera
- **W**: Sposta la luce diffusa verso l'alto
- **S**: Sposta la luce diffusa verso il basso
- **A**: Sposta la luce diffusa verso sinistra
- **D**: Sposta la luce diffusa verso destra
- **Q**: Sposta la luce diffusa indietro
- **E**: Sposta la luce diffusa in avanti
- **F**: Rotea cubo su asse y
- **H**: Rotea cubo su asse y
- **T**: Rotea cubo su asse y
- **G**: Rotea cubo su asse y

- **Spazio**: Reimposta la telecamera

- **1**: Diminuisce l'intensità della luce ambientale
- **2**: Aumenta l'intensità della luce ambientale
- **3**: Diminuisce l'intensità della luce diffusa
- **4**: Aumenta l'intensità della luce diffusa
- **5**: Diminuisce l'intensità della luce speculare
- **6**: Aumenta l'intensità della luce speculare
- **7**: Diminuisce l'esponente della luce speculare
- **8**: Aumenta l'esponente della luce speculare

- **Esc**: Chiude la finestra corrente
- **R**: Genera Perlin Noise
- **O**: Aumenta la risoluzione del Perlin Noise
- **L**: Diminuisce la risoluzione del Perlin Noise
- **I**: Aumenta la dimensione della griglia del Perlin Noise
- **K**: Diminuisce la dimensione della griglia del Perlin Noise
- **Z**: Diminuisce il contrasto del Perlin Noise
- **X**: Aumenta il contrasto del Perlin Noise
- **Page Up**: Aumenta il numero di ottave del Perlin Noise
- **Page Down**: Diminuisce il numero di ottave del Perlin Noise

## File chiave:

**cube.cpp**: All'interno di questo viene generato il perlin noise, oltre che il cubo su cui è applicato.
**14.frag**: Qui viene applicato il bump mapping.