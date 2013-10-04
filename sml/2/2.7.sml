type money = int * int * int;

fun adjustpence (x:int, y:int, z:int) =
  if z >= 0 then
    (x, y, z)
  else
    adjustpence (x, y - 1, z + 12);

fun adjustshillings (x:int, y:int, z:int) =
  if y >= 0 then
    (x, y, z)
  else
    adjustshillings (x - 1, y + 20, z);

fun addmoney ((x1:int, y1:int, z1:int), (x2:int, y2:int, z2:int)) = 
  (x1 + x2, y1 + y2, z1 + z2);

fun negmoney (x:int, y:int, z:int) =
  (~x, ~y, ~z);

fun submoney (a:money, b:money) =
  adjustshillings(adjustpence(addmoney (a, negmoney b)));
