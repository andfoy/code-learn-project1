# Proyecto 1
## Objetivo
Ocultar un texto dentro de una imagen sin causar cambios aparentes en la misma.

## Ejemplo
La imagen original es de un gato 

![Gato](./cat.bmp)

Los pixeles de esta imagen van a ser modificados de tal forma que el mensaje "Example string" sean codificados dentro de la misma.
Tras realizar el procedimiento, es posible observar que la imagen no tiene cambio aparente alguno.

![Gato modificado](./example.bmp)

## Instrucciones
El procedimiento a realizar consiste en tomar los bits de cada uno de los carácteres de la cadena ejemplo e ir poniéndolos en el primer bit de cada uno de los pixeles de la imagen por componente. Por favor tener en cuenta la **Nota importante** en la sección de desplazamiento de bits.

### Glosario
* bit: un único valor 0/1
* byte: 8 bits

### Representación de una imagen
Una imagen cuenta con `HxWxC` entradas, dónde `H` es la altura, `W` el ancho y `C` el número de canales (normalmente 3, correspondientes a Rojo, Azul y Verde). Normalmente, cada pixel (por canal) se encuentra representado por un byte (`unsigned char`), cuyo valor varía entre 0 y 255. En memoria, la representación se vería de la siguiente forma:

```
                                                                                                                      
    ┌────┌────┐────┌────┌────┌────┌───┌────┌────┌────┌───┌────────┌────────┌────────┌───┌────────┌────────┌────────┐  
    │R[0]│G[0]│B[0]│R[1]│G[1]│B[1]│...│R[W]│G[W]│B[W]│...│R[2 * W]│G[2 * W]│B[2 * W]│...│R[H * W]│G[H * W]│B[H * W]│  
    └─┬──└────┘────└────└────└────└───└────└────└────└───└────────└────────└────────└───└────────└────────└────────┘  
      │                                                                                                               
      │                                                                                                               
      │                                                                                                               
  ┌───▼────┐                                                                                                          
  │01010111│                                                                                                          
  └────────┘                                                                                                          
                                                                                                                                                                                                                     
```

Dónde cada casilla ocupa 8 bits exactamente.

### Representación del texto
Recordemos que una cadena de texto es una secuencia de carácteres, dónde cada carácter se encuentra codificado usando un byte (`char`) de acuerdo a la codificación [ASCII](https://www.asciitable.com/). Por ejemplo, la cadena "Hola" se vería así en memoria:

```
                         
      H   o   l  a       
     ┌──┌───┌───┌──┌──┐  
     │72│111│108│97│0 │  
     └┬─└───└───└──└──┘  
      │                  
 ┌────▼─────┐            
 │ 01001000 │            
 └──────────┘            
                         
```

### Procedimiento
Por cada carácter en la cadena de entrada, "Hola" para este ejemplo, se van a tomar cada uno de los bits de cada uno de los carácteres y se van a introducir en el primer bit de los pixeles de la imagen. De forma gráfica:

```
       H   o   l  a
      ┌──┬───┬───┬──┬─┐     ┌────┬────┬────┬────┬────┬────┬───┬────┐
      │72│111│108│97│0│     │R[0]│G[0]│B[0]│R[1]│G[1]│B[1]│...│R[W]│
      └┬─┴───┴───┴──┴─┘     └──┬─┴────┴────┴────┴────┴────┴───┴────┘
       │                       │
       │                   ┌───▼────┐
       │                   │01010111│
   ┌───▼────┐              └───────▲┘
   │01001000│                      │
   └───────┼┘                      │
           └───────────────────────┘                                                                   
```

A continuación se procede a "limpiar" el primer bit del componente del pixel actual (`R[0]` en este caso), nótese que el valor cambia de 1 a 0.

```

       H   o   l  a
      ┌──┬───┬───┬──┬─┐     ┌────┬────┬────┬────┬────┬────┬───┬────┐
      │72│111│108│97│0│     │R[0]│G[0]│B[0]│R[1]│G[1]│B[1]│...│R[W]│
      └┬─┴───┴───┴──┴─┘     └──┬─┴────┴────┴────┴────┴────┴───┴────┘
       │                       │
       │                   ┌───▼────┐
       │                   │01010110│ Clear bit
   ┌───▼────┐              └───────▲┘
   │01001000│                      │
   └───────┼┘                      │
           └───────────────────────┘                                                                   
```

Luego se procede a copiar el valor del bit actual en la cadena en el primer bit del componente. Debido a que el valor es 0, no se nota un cambio aparente.

```

      H   o   l  a
     ┌──┬───┬───┬──┬─┐     ┌────┬────┬────┬────┬────┬────┬───┬────┐
     │72│111│108│97│0│     │R[0]│G[0]│B[0]│R[1]│G[1]│B[1]│...│R[W]│
     └┬─┴───┴───┴──┴─┘     └──┬─┴────┴────┴────┴────┴────┴───┴────┘
      │                       │
      │                   ┌───▼────┐
      │                   │01010110│ Set bit
  ┌───▼────┐              └───────▲┘
  │01001000│                      │
  └───────┼┘                      │
          └───────────────────────┘
```

Luego el procedimiento avanza al siguiente bit en la cadena y al siguiente componente del pixel, repitiendo las mismas instrucciones anteriormente descritas.

```

                             Move to next pixel component
       H   o   l  a
      ┌──┬───┬───┬──┬─┐     ┌────┬────┬────┬────┬────┬────┬───┬────┐
      │72│111│108│97│0│     │R[0]│G[0]│B[0]│R[1]│G[1]│B[1]│...│R[W]│
      └┬─┴───┴───┴──┴─┘     └────┴──┬─┴────┴────┴────┴────┴───┴────┘
       │                            │
       │                        ┌───▼────┐
       │                        │01111111│
   ┌───▼────┐                   └───────▲┘
   │01001000│                           │
   └──────┼─┘                           │
          └─────────────────────────────┘

    Move to next bit
```

Comparemos el procedimiento de escritura cuándo el valor a escribir es un 1:

```

                              Move to next pixel component
        H   o   l  a
       ┌──┬───┬───┬──┬─┐     ┌────┬────┬────┬────┬────┬────┬───┬────┐
       │72│111│108│97│0│     │R[0]│G[0]│B[0]│R[1]│G[1]│B[1]│...│R[W]│
       └┬─┴───┴───┴──┴─┘     └────┴────┴────┴──┬─┴────┴────┴───┴────┘
        │                                      │
        │                                  ┌───▼────┐
        │                                  │10101110│
    ┌───▼────┐                             └───────▲┘
    │01001000│                                     │
    └────┼───┘                                     │
         └─────────────────────────────────────────┘

     Move to next bit
```

Se procede a limpiar el bit del componente. No hay cambio aparente debido a que el valor es 0:

```

      H   o   l  a
     ┌──┬───┬───┬──┬─┐     ┌────┬────┬────┬────┬────┬────┬───┬────┐
     │72│111│108│97│0│     │R[0]│G[0]│B[0]│R[1]│G[1]│B[1]│...│R[W]│
     └┬─┴───┴───┴──┴─┘     └────┴────┴────┴──┬─┴────┴────┴───┴────┘
      │                                      │
      │                                  ┌───▼────┐
      │                                  │10101110│ Clear bit
  ┌───▼────┐                             └───────▲┘
  │01001000│                                     │
  └────┼───┘                                     │
       └─────────────────────────────────────────┘
```

Luego se procede a escribir el valor del bit actual en la cadena:

```

      H   o   l  a
     ┌──┬───┬───┬──┬─┐     ┌────┬────┬────┬────┬────┬────┬───┬────┐
     │72│111│108│97│0│     │R[0]│G[0]│B[0]│R[1]│G[1]│B[1]│...│R[W]│
     └┬─┴───┴───┴──┴─┘     └────┴────┴────┴──┬─┴────┴────┴───┴────┘
      │                                      │
      │                                  ┌───▼────┐
      │                                  │10101111│ Set bit
  ┌───▼────┐                             └───────▲┘
  │01001000│                                     │
  └────┼───┘                                     │
       └─────────────────────────────────────────┘
```

Cuándo el total de bits del caracter actual es procesado por completo, el procedimiento se mueve al siguiente carácter, iniciando en el primer bit nuevamente (nótese que el índice del pixel actual es 8 ahora):

```

                           Repeat procedure for next char
     H   o   l  a
    ┌──┬───┬───┬──┬─┐     ┌────┬────┬────┬────┬────┬────┬───┬────┐
    │72│111│108│97│0│     │... │R[8]│G[8]│B[8]│R[9]│G[9]│...│R[W]│
    └──┴─┬─┴───┴──┴─┘     └────┴──┬─┴────┴────┴────┴────┴───┴────┘
         │                        │
         │                    ┌───▼────┐
         │                    │11101001│
     ┌───▼────┐               └───────▲┘
     │01101111│                       │
     └───────┼┘                       │
             └────────────────────────┘
```

A continuación se presenta una animación parcial del procedimiento a realizar:

https://github.com/user-attachments/assets/98c4ad43-ca76-48f9-9f55-b6226f1b0904


### Recap de operaciones a nivel de bits
Un pequeño recordatorio acerca de como realizar la operación de extacción de bits, "limpiar" un bit dado y finalmente, escribir un bit.

#### ¿Cómo leer un bit en una posición en particular?
Recordemos la tabla de verdad para el operador AND (`a & b`):

| `a` | `b` | `a & b` |
|:---:|:----|:-------:|
| 0   |  0  |    0    |
| 0   |  1  |    0    |
| 1   |  0  |    0    |
| 1   |  1  |    1    |

Cómo es posible observar, la operación AND es verdadera solo si ambas entradas son verdaderas, en los demás casos siembre es falso.

A continuación definamos una máscara binaria como una secuencia de bits que contiene un único 1 en una posición específica y el resto de valores en cero. Las máscaras binarias se pueden emplear para leer un bit en una posición en particular de la siguiente forma. Supongamos que se quiere leer el 3 bit del número 111 (`0x6f`, `01101111`), con este fin, se emplea la máscara binaria 4 (`0x4`, `00000100`)

```
0x6f →       01101111
0x04 →       00000100
0x6f & 0x4 → 00000100 
```

#### ¿Cómo escribir un bit en una posición en particular?
Recordemos nuevamente la tabla de verdad para el operador OR (`a | b`)

| `a` | `b` | `a \| b` |
|:---:|:----|:-------:|
| 0   |  0  |    0    |
| 0   |  1  |    1    |
| 1   |  0  |    1    |
| 1   |  1  |    1    |

Cómo es posible observar, el operador OR es verdadero siempre y cuándo alguno de sus argumentos sea verdadero. Solo es falso si ambas entradas son falsas.

El operador OR se puede emplear para escribir bits en una posición determinada, siempre y cuándo la posición a escribir sea 0. Por ejemplo, a continuación se emplea la máscara binaria 16 (`0x10`, `00010000`) para escribir un 1 en el número 111 (`0x6f`, `01101111`):

```
0x6f →        01101111
0x10 →        00010000
0x6f & 0x10 → 01111111
```

#### ¿Cómo limpiar un bit en una posición en específico?
Finalmente recordemos la tabla de verdad para la negación NOT (`~a`)

| `a` | `~a` |
|:---:|:----|
| 0   |  1  |
| 1   |  0  |

La negación toma cualquier booleano y lo convierte en su contrario, es decir, lo verdadero se vuelve falso y lo falso en verdadero. Empleemos el NOT junto al AND para limpiar un bit en una posición en particular, nuevamente usando el número 111 como ejemplo y la máscara binaria 8 (`0x8`, `00001000`):

```
 0x08 →        00001000
~0x08 →        11110111
 0x6f →        01101111
~0x08 & 0x6f → 01100111 
```

#### Corrimiento de bits
Debido a que el proyecto implica escribir el **n-ésimo** (`n = 0, 1, 2, ..., 7`) bit del caracter actual de la cadena, en la **primera** posición del componente del pixel actual, hay que realizar un corrimiento de bits previo a escribir en tal posición. Continuando con nuestro ejemplo del AND en la sección de lectura:

```
0x6f →       01101111
0x04 →       00000100
0x6f & 0x4 → 00000100
```

El bit a escribir se encuentra en la tercera posición, pero debe ser escrito en la primera posición. Para resolver esto, empleamos el operador de corrimiento de bits a la derecha (`>>`), con el argumento 2 (`>> 2`):

```
0x6f →              01101111
0x04 →              00000100
0x6f & 0x4 →        00000100
(0x6f & 0x4) >> 2 → 00000001
```

Para leer la siguiente posición, la máscara binaria debe incrementar en una posición. Para este fin, se emplea el operador de corrimiento de bits a la izquierda (`<<`), con el argumento 1 (`<< 1`):

```
0x04 →      00000100
0x04 << 1 → 00001000
```

Nótese que cada vez que la máscara binaria incrementa, el número de veces que se tiene que desplazar el bit a escribir también incrementa.

**Nota importante:** También se puede leer en orden descendente, iniciando con una máscara binaria con un uno en la última posición, moviendo el bit a la derecha y disminuyendo el número del desplazamiento para mover el bit a la primera posición. Esta es la versión que se tiene que implementar en el proyecto. 

## Ejecución del proyecto.
1. Crear una cuenta en github.com
2. Ir a la página principal del proyecto https://github.com/andfoy/code-learn-project1
3. Hacer click en el botón verde que dice "<> Code":
    <img width="1430" height="860" alt="image" src="https://github.com/user-attachments/assets/46530147-7d89-4099-884a-d7f66c5a3e6a" />
4. Luego hacer click en la pestaña "Codespaces", y luego el botón +
   <img width="1430" height="860" alt="image" src="https://github.com/user-attachments/assets/9e87f2ac-974f-4250-8d7b-1591342f98f7" />
5. Una ventana similar a esta debería aparecer:
   <img width="3247" height="1929" alt="image" src="https://github.com/user-attachments/assets/bfbe1241-2e59-4591-94f2-4ed4ca256bfb" />
6. En la parte inferior, aparece la terminal del entorno de desarrollo:
   <img width="2547" height="699" alt="image" src="https://github.com/user-attachments/assets/11b4cf59-ed61-489c-93c5-35df4df8ef36" />
7. Escribir `mkdir build && cd build`, seguido de Enter (`mkdir` crea una nueva carpeta y `cd` hace que la consola se mueva a esa carpeta):
8. Escribir `cmake ..`, seguido de Enter, la salida debería ser similar a esta
    <img width="2547" height="600" alt="image" src="https://github.com/user-attachments/assets/c65ada2c-4988-4749-bc75-0cd4cfd14b0b" />
9. Escribir `make`, seguido de Enter, debería salir un texto largo que al final dice `[100%]`
11. Para ejecutar el proyecto, `./project1`:
    <img width="2547" height="600" alt="image" src="https://github.com/user-attachments/assets/040ee382-faef-4458-93dd-81b335655436" />
12. Para verificar la correcta ejecución del proyecto: `./decode`, la ejecución correcta debería verse así
    <img width="2547" height="262" alt="image" src="https://github.com/user-attachments/assets/5283d387-1f32-4aea-9730-fb9f9f4fb483" />
13. Si se hace click en el panel izquierdo en la carpeta `src` y luego en el archivo `main.c`, se podrá acceder al editor de texto
14. Los cambios deben ser realizados debajo de la sección comentada que inicia con la nota `TAREA`:
    <img width="2558" height="707" alt="image" src="https://github.com/user-attachments/assets/72c919c6-8b99-486e-940f-7ecb10cabcd3" />

**Importante!** Cada vez que se realicen cambios en los archivos, siempre toca volver a invocar el comando `make`


   



