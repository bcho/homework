(defn problem-2 [upper-limit checker]
  (loop [a 1 b 1 fib-num 1 sum 0]
    (if (> fib-num upper-limit)
      sum
      (recur b (+ b a) b (+ sum (if (checker fib-num) fib-num 0))))))


(println (problem-2 4000000 even?))
