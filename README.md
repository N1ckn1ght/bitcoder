# bitcoder
Task from 04.05.2019

shu.cpp - шифровщик текстовых файлов.
Первый байт шифруется в последующие семь, занимая пространство в первых нулях символов. 
(01101010 -> 1... 1... 0... 1... 0... 1... 0...)
Если нехватает символов (<8), остаток остаётся без изменений.

deshu.cpp - дешифровщик.
Создаётся буфер, запоминающий первые семь битов.
В переменную encoded идут первые биты символов.
Каким бы ни был первым бит, он заменяется на ноль.
В файл выводится encoded и буффер, обнуление, и по новой.