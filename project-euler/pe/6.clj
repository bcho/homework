(defn square [n] (* n n))
(defn sum [numbers]
  (reduce (fn [a b] (+ a b)) numbers))

(defn problem-6 [n]
  (let [numbers (range 1 (+ n 1))]
    (-
     (square (sum numbers))
     (sum (map square numbers)))))

(println (problem-6 100))
