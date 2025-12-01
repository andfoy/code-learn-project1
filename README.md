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
El procedimiento a realizar consiste en tomar los bits de cada uno de los carácteres de la cadena ejemplo e ir poniéndolos en el primer bit de cada uno de los pixeles de la imagen por componente.

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
     ┌──┌───┌───┌──┌──┐    ┌────┌────┐────┌────┌────┌────┌───┌──── 
     │72│111│108│97│0 │    │R[0]│G[0]│B[0]│R[1]│G[1]│B[1]│...│R[W] 
     └┬─└───└───└──└──┘    └─┬──└────┘────└────└────└────└───└──── 
      │                      │                                     
 ┌────▼─────┐                │                                     
 │ 01001000 │                │                                     
 └────────▼─┘            ┌───▼────┐                                
          │              │01010110│                                
          │              └───────▲┘                                
          │                      │                                 
          └──────────────────────┘                                 
                                                                   
```