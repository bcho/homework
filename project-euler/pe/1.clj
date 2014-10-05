(defn problem-1 [upper-limit checker]
  (loop [n (dec upper-limit) sum 0]
    (if (= n 0)
      sum
      (recur (dec n) (+ sum (if (checker n) n 0))))))


(defn checker [n]
  (or (= (mod n 5) 0)
      (= (mod n 3) 0)))


(println (problem-1 1000 checker))
