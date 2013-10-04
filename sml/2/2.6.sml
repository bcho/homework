type vec = int * int * string;

fun get_hour (hour:int, minute:int, moment:string) = hour;
fun get_minute (hour:int, minute:int, moment:string) = minute;
fun get_moment (hour:int, minute:int, moment:string) = moment;

fun check_time (a:vec, b:vec) =
  if get_moment a = "PM" andalso get_moment b = "AM" then false
  else if get_moment a = "AM" andalso get_moment b = "PM" then true
  else if get_hour a > get_hour b then false
  else if get_hour a < get_hour b then true
  else if get_minute a > get_minute b then false
  else true;
