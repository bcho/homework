fun validate (d:int, m:string) = (m = "Jan" andalso d > 1 andalso d < 31) orelse
  (m = "Feb" andalso d > 1 andalso d < 28) orelse
  (m = "Mar" andalso d > 1 andalso d < 31) orelse
  (m = "Apr" andalso d > 1 andalso d < 30) orelse
  (m = "May" andalso d > 1 andalso d < 31) orelse
  (m = "Jun" andalso d > 1 andalso d < 30) orelse
  (m = "Jul" andalso d > 1 andalso d < 31) orelse
  (m = "Aug" andalso d > 1 andalso d < 31) orelse
  (m = "Sep" andalso d > 1 andalso d < 30) orelse
  (m = "Oct" andalso d > 1 andalso d < 31) orelse
  (m = "Nov" andalso d > 1 andalso d < 30) orelse
  (m = "Dec" andalso d > 1 andalso d < 31); 
