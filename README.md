# bitcoder
Task from 02.05.2019

Шифровщик / дешифровщик текстовых файлов.
Использование: input output e/d key, где
  e - шифровка
  d - дешифровка
  key - ключ, должен быть пятисимвольным

Как работает шифратор:

Первый байт шифруется в последующие семь, занимая пространство в первых нулях символов 
(01101010 -> 1... 1... 0... 1... 0... 1... 0...).
Если нехватает символов (<8), остаток остаётся без изменений.
На каждый символ накладывается XOR'ом ключ-маска.

deshu.cpp - дешифровщик.
Создаётся буфер, запоминающий первые семь байтов.
В переменную encoded идут первые биты символов.
Каким бы ни был первым бит, он заменяется на ноль.
В файл выводится encoded и буфер, обнуление, и по новой.
Далее дочитываются несжатые символы, и XOR с ключом.
