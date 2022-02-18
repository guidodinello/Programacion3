#!/bin/bash
str1='crear_personas 10\nleer_lista_muertes .\nleer_lista_convivencias .\nexiste_cronologia\nFin'
str2='1>2>3>4>Hay una cronología consistente.\n5>Fin.'
read name

echo -e $str1 > $name.in
echo -e $str2 > $name.out

#>> conserva lo que habia, > sobreescribe
#-e permite el salto de linea
