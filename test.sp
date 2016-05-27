_huion "./huion.so" fl

'test' _huion fe

0 'test' tget 100 1000 scale 
1 1 'test' tget - 0.0 0.4 scale 
1
1
2 'test' tget 0.005 port 0.0 3 scale 
fm

3 'test' tget 0.01 port *

dup 0.4 0.5 delay 0.1 * 500 butlp + 

dup dup 4 4 1000 zrev drop 0.2 * + 

_huion fc
