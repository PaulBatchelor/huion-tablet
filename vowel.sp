_huion "./huion.so" fl
'test' _huion fe
_huion fc

# o a e i - male
'f1' '350 600 400 250' gen_vals
'f2' '600 1040 1620 1750' gen_vals
'f3' '2400 2250 2400 2600' gen_vals

'g1' '1 1 1 1' gen_vals
'g2' '0.1 0.4468 0.251 0.031' gen_vals
'g3' '0.0251 0.354 0.354 0.1584' gen_vals

'bw1' '40 60 40 60' gen_vals
'bw2' '80 70 80 90' gen_vals
'bw3' '100 110 100 100' gen_vals

# # o a e i - alto
# 'f1' '450 800 400 350' gen_vals
# 'f2' '800 1150 1600 1700' gen_vals
# 'f3' '2830 2800 2700 2700' gen_vals
# 
# 'g1' '1 1 1 1' gen_vals
# 'g2' '0.354 0.631 0.063 0.1' gen_vals
# 'g3' '0.224 0.1 0.03 0.031' gen_vals
# 
# 'bw1' '70 50 60 50' gen_vals
# 'bw2' '80 60 80 100' gen_vals
# 'bw3' '100 170 120 120' gen_vals

# 0 2 0.1 1 sine 2 10 biscale randi 0 pset

1 'test' tget 0 3 scale 0 pset
#0 'test' tget 24.5 60.5 scale mtof 1 pset
0 'test' tget 62 74 scale 0.003 port mtof 1 pset


# 110 200 0.8 1 sine 2 8 biscale randi 3 20 30 jitter  
# 1 p 0.5 0.1 square

1 p 0.3 4 0 0.9 gbuzz

4 'test' tget swap 0.5 2 thresh tog 0.8 noise swap branch 

dup
0 p 0 0 0 'g1' tabread *
0 p 0 0 0 'f1' tabread
0 p 0 0 0 'bw1' tabread
butbp
swap dup
0 p 0 0 0 'g2' tabread *
0 p 0 0 0 'f2' tabread
0 p 0 0 0 'bw2' tabread
butbp
swap
0 p 0 0 0 'g3' tabread *
0 p 0 0 0 'f3' tabread
0 p 0 0 0 'bw3' tabread
butbp
+ +
3 'test' tget 0.01 port *
dup
60 500 3.0 5.0 6000
315 6
2000 0
0.2 2 zitarev drop
